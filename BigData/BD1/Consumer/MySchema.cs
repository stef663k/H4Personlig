using Avro;
using Avro.Specific;

namespace Consumer;

public class MySchema : ISpecificRecord
{
    public static readonly Schema _SCHEMA = Schema.Parse(@"
    {
        ""type"": ""record"",
        ""name"": ""AvroClass"",
        ""namespace"": ""Producer"",
        ""fields"": [
            { ""name"": ""Field1"", ""type"": ""string"" },
            { ""name"": ""Field2"", ""type"": ""int"" },
        ]
    }");

    public string Field1 { get; set; }
    public int Field2 { get; set; }

    public MySchema() 
    {
        Field1 = string.Empty; 
    }

    public Schema Schema => _SCHEMA;

    public object Get(int fieldPos)
    {
        return fieldPos switch
        {
            0 => Field1,
            1 => Field2,
            _ => throw new AvroRuntimeException($"Bad index {fieldPos} in Get()")
        };
    }

    public void Put(int fieldPos, object fieldValue)
    {
        switch (fieldPos)
        {
            case 0: Field1 = (string)fieldValue; break;
            case 1: Field2 = (int)fieldValue; break;
            default: throw new AvroRuntimeException($"Bad index {fieldPos} in Put()");
        }
    }
}

