using System;
using System.Threading.Tasks;
using Confluent.Kafka;
using Confluent.SchemaRegistry;
using Confluent.SchemaRegistry.Serdes;
using Avro;
using Avro.Specific;
using System.Runtime.Serialization;
using Confluent.Kafka.SyncOverAsync;
using Avro.IO;
using System.Threading;
using System.IO;

namespace Consumer;

class Program
{

  public static async Task Main(string[] args)
    {
        var config = new ConsumerConfig
        {
            BootstrapServers = "172.16.250.13:9092",
            ClientId = "Stefan",
            SecurityProtocol = SecurityProtocol.Plaintext,
            Acks = Acks.All,
            AutoOffsetReset = AutoOffsetReset.Latest,
            EnableAutoCommit = true,
            GroupId = "Stefan-group",
        };

        var schemaRegistryConfig = new SchemaRegistryConfig
        {
            Url = "172.16.250.15:8081"
        };

        var schemaRegistry = new CachedSchemaRegistryClient(schemaRegistryConfig);

        var consumer = new ConsumerBuilder<Ignore, MySchema>(config)
            .SetValueDeserializer(new AvroDeserializer<MySchema>(schemaRegistry).AsSyncOverAsync())
            .Build();

        var topic = "BB";
        consumer.Subscribe(topic);
        var cancellationToken = new CancellationTokenSource();

        while (!cancellationToken.IsCancellationRequested)
        {
            try
            {
                var result = consumer.Consume(cancellationToken.Token);
                var rawMessageBytes = ConvertToByteArray(result.Message.Value);
                Console.WriteLine($"Raw message: {BitConverter.ToString(rawMessageBytes)}");

                var message = result.Message;

                Console.WriteLine($"Received message at {message.Timestamp.UtcDateTime:O}: Field1={message.Value.Field1}, Field2={message.Value.Field2}");
            }
            catch (ConsumeException e)
            {
                Console.WriteLine($"Error occurred: {e.Error.Reason}");
            }
            catch (Exception e)
            {
                Console.WriteLine($"Unexpected error: {e.Message}");
            }
                
        }

        consumer.Close();
        await Task.CompletedTask;
    }
    private static byte[] ConvertToByteArray(MySchema mySchema)
    {
        using (var stream = new MemoryStream())
        {
            var encoder = new BinaryEncoder(stream);
            var writer = new SpecificDatumWriter<MySchema>(mySchema.Schema);
            writer.Write(mySchema, encoder);
            return stream.ToArray();
        }
    }
}
