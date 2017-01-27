using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GoingToTheShop
{

       public class Good
        {
           public string Name { get; set; }
           public int Cost { get; set; }
           public int ID { get; set; }

        public Good(string Name, int Cost, int ID)
        {
            this.Name = Name;
            this.Cost = Cost;
            this.ID = ID;
        }
    }
    
    public class GoodsModel: ObservableCollection<Good>
    {
        private static object _threadLock = new Object();
        private static GoodsModel current = null;
 
        public static GoodsModel Current {
            get {
                lock (_threadLock)
                if (current == null)
                    current = new GoodsModel();
 
                return current;
            }
        }
 
        private GoodsModel() {

        }
 
        public void AddGood(String Name,
            int Cost, int ID) {
            Good newGood = new Good(Name, Cost, ID);
            Add(newGood);
        }
        public void RemoveGood(int ID)
        {
            Remove((Good)(this.Where(good => good.ID == ID)));
        }
    }
}
