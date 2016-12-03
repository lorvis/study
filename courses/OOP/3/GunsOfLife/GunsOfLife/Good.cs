using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GunsOfLife
{
    public interface IGood : IComparable
    {
        string Name { get; }
        int Cost { get; }
    }

    public static class GoodExtensions
    {
        public static int CompareTo(this IGood good, object obj)
        {
            return good.Cost - ((IGood)obj).Cost;
        }
    }
}
