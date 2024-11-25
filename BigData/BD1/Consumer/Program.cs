using System;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Confluent.Kafka;
using Kafka.Public;
using Kafka.Public.Loggers;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

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
            GroupId = "Stefan",

        };

        var consumer = new ConsumerBuilder<Ignore, string>(config)
            .SetLogHandler((_, log) => Console.WriteLine($"[{log.Level}] {log.Message}"))
            .Build();

        var topic = "BB";
        consumer.Subscribe(topic);

        var cancellationToken = new CancellationTokenSource();

        while(!cancellationToken.IsCancellationRequested)
        {
            try
            {

                var result = consumer.Consume(cancellationToken.Token);

                var message = result.Message;
                Console.WriteLine($"Received message at {message.Timestamp.UtcDateTime:O}: {message.Value}");
            }
            catch (ConsumeException e)
            {
                Console.WriteLine($"Error occured: {e.Error.Reason}");
            }
        }

        consumer.Close();
    }
}
