using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GunsOfLife
{

    class WarriorBaseInfo
    {
        private string name;
        private string surname;
        private double mastery;
        private double strength;
        private double agility;

        public WarriorBaseInfo(string name, string surname, double mastery, double strength, double agility)
        {
            this.name = name;
            this.surname = surname;
            this.mastery = mastery;
            this.strength = strength;
            this.agility = agility;
        }

        public WarriorBaseInfo(Warrior w)
        {
            name = w.Name;
            surname = w.Surname;
            mastery = w.Mastery;
            strength = w.Strength;
            agility = w.Agility;
        }

        public string Name { get { return name; } }
        public string Surname { get { return surname; } }
        public double Mastery { get { return mastery; } }
        public double Strength { get { return strength; } }
        public double Agility { get { return agility; } }
    }

    class WarriorException : Exception
    {
        public WarriorBaseInfo wInfo = null;

        public WarriorException()
        {

        }

        public WarriorException(string message) : base(message)
        {

        }

        public WarriorException(string message, Exception inner) : base(message, inner)
        {

        }

        public WarriorException(string message, WarriorBaseInfo wInfo) : base(message)
        {
            this.wInfo = wInfo;
        }
    }
}
