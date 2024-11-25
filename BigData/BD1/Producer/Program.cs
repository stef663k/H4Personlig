﻿using System;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Confluent.Kafka;
using Kafka.Public;
using Kafka.Public.Loggers;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace Producer;

class Program
{
    public static async Task Main(string[] args) // Change void to Task
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

        var producer = new ProducerBuilder<Null, string>(config)
            .SetLogHandler((_, log) => Console.WriteLine($"[{log.Level}] {log.Message}"))
            .Build();

        var topic = "BB";

        for ( int i = 0; i < 100; i++)
        {
            var value = $"Hello world from Stefan! {i}";
            var deliveryReport = await producer.ProduceAsync(topic, new Message<Null, string> { Value = value });
            Console.WriteLine($"Delivered '{deliveryReport.Value}' to '{deliveryReport.TopicPartitionOffset}'");
        }
        producer.Flush();
    }
}
