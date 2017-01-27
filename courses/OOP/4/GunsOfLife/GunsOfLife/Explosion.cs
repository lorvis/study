using System;
using System.Collections.Generic;
using System.Xml.Serialization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GunsOfLife
{
    [Serializable]
    public class Explosive
    {
        string name;
        double power;
        double weight;

        [XmlAttribute]
        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        [XmlAttribute]
        public double Power
        {
            get { return power; }
            set { power = value; }
        }

        [XmlAttribute]
        public double Weight
        {
            get { return weight; }
            set { weight = value; }
        }

        public Explosive(string name, double power, double weight)
        {
            this.name = name;
            this.power = power;
            this.weight = weight;
        }

        public Explosive()
        {

        }
    }

    [Serializable]
    public class ExplosivesPack
    {
        [XmlArray("Explosives")]
        [XmlArrayItem("Explosive")]
        public List<Explosive> explosivesList = new List<Explosive>(); //Was "explosives", names shouldn't be almost the same |||||||||||||||| LAB 4 ||||||||||||
        [XmlIgnore]
        public List<WeakReference> explosivesAboutToBoom = new List<WeakReference>();

        public ExplosivesPack()
        {

        }

        public void startDetonation(Explosive explosive)
        {
            if (explosivesList.Contains(explosive))
                explosivesList.Remove(explosive);

            explosivesAboutToBoom.Add(new WeakReference(explosive, true));
        }

        public void scanForBoom()
        {
            foreach(WeakReference explosive in explosivesAboutToBoom)
            {
                if(explosive.Target == null)
                {
                    Console.WriteLine("It seems to be boomed");
                }
                else
                {
                    Console.WriteLine((((Explosive)explosive.Target).Name + " is not boomed"));
                }
            }
        }

        public void boomAll()
        {
            while(explosivesList.Count != 0)
            {
                startDetonation(explosivesList[0]);
            }
        }
    }
}
