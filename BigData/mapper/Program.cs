using Sysstem;
using System.Text.RegularExpressions;

namespace mapper;

class Program
{
    static void Main(string[] args)
    {
        string line;

        while((line = Console.ReadLine()) != null)
        {
            var onlyText = Regex.Replace(line, @"\.|;|;|,|[0-9]'", "");

            var words = Regex.Matches(onlyText, @"[\w]+");

            foreach(var word in words)
            {
                Console.WriteLine("{0}\t1", word);
            }
        }
    }

}