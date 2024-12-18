using System;
using HtmlAgilityPack;
using System.IO;
using System.Globalization;

namespace WebScraper
{
    class Program
    {
        static void Main(string[] args)
        {
            Scrape();
        }

        static void Scrape()
        {
            var url = "https://www.proshop.dk/Spillekonsol/Microsoft-Xbox-Series-X-1-TB-Black/2839638"; 
            var web = new HtmlWeb();
            var doc = web.Load(url);

            var productNameNode = doc.DocumentNode.SelectSingleNode("//h1[@data-type='product']");

            var salePriceNode = doc.DocumentNode.SelectSingleNode("//div[@class='site-currency-attention site-currency-campaign']");

            var priceNode = salePriceNode ?? doc.DocumentNode.SelectSingleNode("//span[@class='site-currency-attention']");

            string filePath = "prices.csv";

            if (productNameNode != null && priceNode != null)
            {
                string productName = productNameNode.InnerText.Trim();

                string priceString = priceNode.InnerText.Trim().Replace(" kr.", "").Replace(".", "").Replace(",", ".");

                if (double.TryParse(priceString, NumberStyles.Any, CultureInfo.InvariantCulture, out double price))
                {
                    using (var writer = new StreamWriter(filePath, append: true))
                    {
                        if (new FileInfo(filePath).Length == 0)
                        {
                            writer.WriteLine("Product Name, Price");
                        }

                        writer.WriteLine($"\"{productName}\", \"{price}\"");

                        Console.WriteLine("Product name and price written to CSV.");
                    }
                }
                else
                {
                    Console.WriteLine("Invalid price format.");
                }
            }
            else
            {
                Console.WriteLine("No product name or price found.");
            }
        }
    }
}
