using System;
using System.Collections.Generic;

namespace reducer;

class Program
{
    static void Main(string[] args)
    {
        Dictionary<string, int> words = new Dictionary<string, int>();

        string line;

        while((line = Console.ReadLine()) != null)
        {
            var sArr = line.Split('\t');

            string word = sArr[0];

            int count = Convert.ToInt32(sArr[1]); 

            if(words.ContainsKey(word))
            {
                words[word] += count;

            }
            else
            {
                words.Add(word, count);
            }
        }

        foreach(var word in words)
        {
            Console.WriteLine("{0}\t{1}", word.Key, word.Value);
        }
    }
}