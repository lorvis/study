using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GunsOfLife
{

    class GoodsList<T> : IEnumerable<T>, IEnumerator<uint> where T : IGood
    {
        object[] arr = new object[0];
        uint current;

        public GoodsList()
        {

        }

        private void extend()
        {
            object[] temp = arr;
            arr = new object[temp.Length];
            temp.CopyTo(arr, 0);
        }

        public void add(T good)
        {
            extend();
            arr[arr.Length - 1] = good;
        }

        public void remove(uint index)
        {
           for(uint i=index+1; i <= arr.Length; i++)
            {
                arr[i - 1] = arr[i];
            }

            object[] temp = arr;
            arr = new object[temp.Length - 1];
            temp.CopyTo(arr, 0);
        }

        public void print()
        {
            if(arr.Length == 0)
                Console.WriteLine("The list is empty");
            else
                foreach(IGood good in arr)
                {
                    Console.WriteLine(good.Name);
                }
        }

        public uint Current
        {
            get
            {
                return current;
            }
        }

        object IEnumerator.Current
        {
            get
            {
                return arr[current];
            }
        }

        public void Dispose()
        {
            arr = null;
        }

        public bool MoveNext()
        {
            if (current + 1 == arr.Length)
            {
                return false;
            }
            return true;
        }

        public void Reset()
        {
            current = 0;
        }

        public IEnumerator<T> GetEnumerator()
        {
            throw new NotImplementedException();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
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
    }
}
