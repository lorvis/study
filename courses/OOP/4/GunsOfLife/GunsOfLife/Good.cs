using System;
using System.Collections.Generic;
using System.Xml.Serialization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GunsOfLife
{
    public interface IGood : IComparable
    {
        [XmlAttribute]
        string Name { get; }
        [XmlAttribute]
        int Cost { get; }
    }

    public static class GoodExtensions
    {

    }
}
