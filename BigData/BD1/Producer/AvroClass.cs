using Avro;
using Avro.Specific;

namespace Producer;

public class AvroClass : ISpecificRecord
{
    public static readonly Schema _SCHEMA =
    Schema.Parse("{\"type\": \"record\", \"name\": \"HusstandeRec\", \"namespace\": \"HustandeGruppeEt\", \"fields\": ["
                + "{\"name\": \"Elmaaler_ID\", \"type\": \"string\"}, "
                + "{\"name\": \"Elforbrug\", \"type\": \"double\"}, "
                + "{\"name\": \"Varmemaaler_ID\", \"type\": \"string\"}, "
                + "{\"name\": \"Varmeforbrug\", \"type\": \"double\"}]}");

    public virtual Schema Schema => _SCHEMA;

    public string? Elmaaler_ID { get; set; }
    public double Elforbrug { get; set; }
    public string? Varmemaaler_ID { get; set; }
    public double Varmeforbrug { get; set; }

    public object Get(int fieldPos)
    {
        return fieldPos switch
        {
            0 => Elmaaler_ID ?? string.Empty,
            1 => Elforbrug,
            2 => Varmemaaler_ID ?? string.Empty,
            3 => Varmeforbrug,
            _ => throw new AvroRuntimeException("Bad index " + fieldPos)
        };
    }

    public void Put(int fieldPos, object fieldValue)
    {
        switch (fieldPos)
        {
            case 0: Elmaaler_ID = (string)fieldValue; break;
            case 1: Elforbrug = (double)fieldValue; break;
            case 2: Varmemaaler_ID = (string)fieldValue; break;
            case 3: Varmeforbrug = (double)fieldValue; break;
            default: throw new AvroRuntimeException("Bad index " + fieldPos);
        }
    }
}
