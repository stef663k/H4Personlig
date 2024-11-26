﻿using System;
using System.Threading.Tasks;
using Confluent.Kafka;
using Confluent.SchemaRegistry;
using Confluent.SchemaRegistry.Serdes;
using Avro;
using Avro.Specific;
using System.Runtime.Serialization;

namespace Producer;

class Program
{
    public static async Task Main(string[] args)
    {
        var schemaRegistry = InitializeSchemaRegistry();
        var producer = InitializeProducer(schemaRegistry);

        var topic = "BB";

        try
        {
            await RegisterSchema(schemaRegistry);

            await ProduceMessages(producer, topic);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Unexpected error: {e.Message}");
        }
        finally
        {
            Cleanup(producer);
        }
    }

    private static CachedSchemaRegistryClient InitializeSchemaRegistry()
    {
        var schemaRegistryConfig = new SchemaRegistryConfig
        {
            Url = "172.16.250.15:8081"
        };
        return new CachedSchemaRegistryClient(schemaRegistryConfig);
    }

    private static IProducer<Null, AvroClass> InitializeProducer(CachedSchemaRegistryClient schemaRegistry)
    {
        var config = new ProducerConfig
        {
            BootstrapServers = "172.16.250.13:9092",
            ClientId = "Stefan",
            SecurityProtocol = SecurityProtocol.Plaintext,
            Acks = Acks.All,
            MessageTimeoutMs = 30000,
            BatchNumMessages = 1000,
            LingerMs = 5,
            CompressionType = CompressionType.Gzip,
        };

        var avroSerializerConfig = new AvroSerializerConfig
        {
            BufferBytes = 100
        };

        Console.WriteLine("Initializing producer with Avro serializer...");
        var producer = new ProducerBuilder<Null, AvroClass>(config)
            .SetValueSerializer(new AvroSerializer<AvroClass>(schemaRegistry, avroSerializerConfig))
            .SetLogHandler((_, log) => Console.WriteLine($"[{log.Level}] {log.Message}"))
            .Build();

        Console.WriteLine("Producer initialized.");
        return producer;
    }


    private static async Task RegisterSchema(CachedSchemaRegistryClient schemaRegistry)
    {
        var schemaString = @"{
            ""fields"": [
                { ""name"": ""Field1"", ""type"": ""string"" },
                { ""name"": ""Field2"", ""type"": ""int"" },
            ],
            ""name"": ""AvroClass"",
            ""namespace"": ""Producer"",
            ""type"": ""record""
        }";

        var schema = Avro.Schema.Parse(schemaString);

        var subject = "BB-value";
        try
        {
            var confluentSchema = new Confluent.SchemaRegistry.Schema(schema.ToString(), Confluent.SchemaRegistry.SchemaType.Avro);
            var schemaId = await schemaRegistry.RegisterSchemaAsync(subject, confluentSchema);   
            Console.WriteLine($"Schema registered with ID: {schemaId}");
            Console.WriteLine($"Registered schema: {schema}");

        }
        catch (SchemaRegistryException e)
        {
            Console.WriteLine($"Schema registration failed: {e.Message}");
        }
    }

    private static async Task ProduceMessages(IProducer<Null, AvroClass> producer, string topic)
    {
        for (int i = 0; i < 100; i++)
        {
            var avroClass = new AvroClass
            {
                Field1 = "Hello",
                Field2 = i,
            };


            Console.WriteLine($"Message content: {avroClass}");

            try
            {
                var deliveryResult = await producer.ProduceAsync(topic, new Message<Null, AvroClass> { Value = avroClass });
                Console.WriteLine($"Message produced: {deliveryResult.Value}");
            }
            catch (ProduceException<Null, AvroClass> e)
            {
                Console.WriteLine($"Error producing message: {e.Error.Reason}");
                Console.WriteLine($"Details: {e.ToString()}");
            }
        }
    }


    private static void Cleanup(IProducer<Null, AvroClass> producer)
    {
        try
        {
            producer.Flush(TimeSpan.FromSeconds(10));
            Console.WriteLine("Producer flushed and cleaned up.");
        }
        catch (Exception e)
        {
            Console.WriteLine($"Error during cleanup: {e.Message}");
        }
    }
}

