using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Xml.Serialization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GoingToTheShop
{
    [Serializable]
    public class GoodsList<T> : IEnumerable<T>, IEnumerator<T> where T : Good
    {
        [XmlArray("GoodList")]
        [XmlArrayItem("Good")]
        object[] arr = new object[0];
        int current = -1;

        public GoodsList()
        {

        }

        public int Length
        {
            get { return arr.Length; }
        }

        private void extend()
        {
            object[] temp = arr;
            arr = new object[temp.Length + 1];
            temp.CopyTo(arr, 0);
        }

        public void add(T good)
        {
            extend();
            arr[arr.Length - 1] = good;
        }

        public void remove(int index)
        {
            if (index < 0 || index >= arr.Length)
            {
                throw new IndexOutOfRangeException();
            }
            for (int i = index + 1; i <= arr.Length; i++)
            {
                arr[i - 1] = arr[i];
            }

            object[] temp = arr;
            arr = new object[temp.Length - 1];
            temp.CopyTo(arr, 0);
        }

        public void print()
        {
            if (arr.Length == 0)
                Console.WriteLine("The list is empty");
            else
                for (int i = 0; i < arr.Length; i++)
                {
                    Console.WriteLine(i + ". - \"" + ((Good)arr[i]).Name + "\"");
                }

        }

        public void sort()
        {
            Array.Sort(arr);
        }

        public T Current
        {
            get
            {
                return (T)arr[current];
            }
        }

        object IEnumerator.Current
        {
            get
            {
                return Current;
            }
        }

        public void Dispose()
        {

        }

        public bool MoveNext()
        {
            if (current + 1 == arr.Length)
            {
                return false;
            }
            current++;
            return true;
        }

        public void Reset()
        {
            current = -1;
        }

        public IEnumerator<T> GetEnumerator()
        {
            return this;
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return this;
        }

        public object this[int index]
        {
            get { return arr[index]; }
            set
            {
                if (index < 0 || index >= arr.Length)
                    throw new IndexOutOfRangeException();
                arr[index] = value;
            }
        }
        public object this[string name]
        {
            get
            {
                foreach (Good good in this)
                {
                    if (good.Name == name)
                        return good;
                }
                return null;
            }
        }
    }
}


//public static class GoodListExtensions
//    {
//        public static void printCosts<T> (this GoodsList<T> goods) where T: IGood
//        {
//            foreach(IGood good in goods)
//            {
//                Console.WriteLine(good.Name + " - " + good.Cost);
//            }
//        }
//    }
//}
