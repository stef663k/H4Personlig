using Avro;
using Avro.Specific;
using Avro.IO;
using System.IO;
namespace Producer;
public class AvroClass : ISpecificRecord
{
    public static Schema _SCHEMA = Schema.Parse(@"{
        ""type"": ""record"",
        ""name"": ""AvroClass"",
        ""namespace"": ""Producer"",
        ""fields"": [
            { ""name"": ""Field1"", ""type"": ""string"" },
            { ""name"": ""Field2"", ""type"": ""int"" },
        ]
    }");

    public virtual Schema Schema => _SCHEMA;

    public string Field1 { get; set; } = string.Empty;
    public int Field2 { get; set; }
    public string Name { get; set; } = string.Empty; 

    public object Get(int fieldPos)
    {
        return fieldPos switch
        {
            0 => Field1,
            1 => Field2,
            _ => throw new AvroRuntimeException($"Bad index {fieldPos}")
        };
    }

    public void Put(int fieldPos, object fieldValue)
    {
        switch (fieldPos)
        {
            case 0: Field1 = (string)fieldValue; break;
            case 1: Field2 = (int)fieldValue; break;
            default: throw new AvroRuntimeException($"Bad index {fieldPos}");
        }
    }

    public override string ToString()
    {
        return $"Field1 = {Field1}, Field2 = {Field2}";
    }
    public static byte[] SerializeAvroClass(AvroClass avroClass)
    {
        var schema = AvroClass._SCHEMA;
        var serializer = new SpecificDatumWriter<AvroClass>(schema);
        
        using (var stream = new MemoryStream())
        {
            var encoder = new BinaryEncoder(stream);
            serializer.Write(avroClass, encoder);
            return stream.ToArray(); 
        }
    }
}



