using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GunsOfLife
{
    #region hitargs
    public class HitArgs
    {
        weaponsDmgTypes damageType;
        double power;

        public HitArgs(weaponsDmgTypes damageType, double power)
        {
            this.power = power;
            this.damageType = damageType;
        }

        public weaponsDmgTypes DamageType
        {
            get { return damageType; }
        }

        public double Power
        {
            get { return power; }
        }
    }
    #endregion

    #region target
    public class Target: IDisposable
    {
        private Dictionary<byte, double> resistances;
        private string name;
        private double durability;
        private List<Warrior> attackers = new List<Warrior>();
        bool disposed = false;

        public Target(string name, double durability)
        {
            //Setting default resistances to 10
            var dmgTypesArr = Enum.GetValues(typeof(weaponsDmgTypes));
            resistances = new Dictionary<byte, double>();
            foreach (int resType in dmgTypesArr)
            {
                resistances.Add((byte)resType, 10);
            }

            this.name = name;
            this.durability = durability;
        }

        public void hit(Warrior attacker, HitArgs args)
        {
            attackers.Add(attacker);
            weaponsDmgTypes dmgType = args.DamageType;
            double power = args.Power;
            if (!resistances.ContainsKey((byte)dmgType))
                dmgType = (byte)weaponsDmgTypes.UNKNOWN;

            double damage = power / resistances[(byte)dmgType];


            if(durability == 0)
            {
                Console.WriteLine("\n" + attacker.Name + " with ' " + attacker.GetWeapon.Name + " ' --->  ' " + name + " ': target is already destroyed, it would take " + damage + " damage if it was unbroken \n");
                attacker.unreadyOne(hit);
                return;
            }

            Console.WriteLine(attacker.Name + " with ' " + attacker.GetWeapon.Name + " ' ---> ' " + name + " ' : target has been damaged for " + damage + " durability points");

            if(damage >= durability)
            {
                durability = 0;
                Console.WriteLine("\n|---Target ' " + name + " ' has been destroyed by " + attacker.Name + " with ' " + attacker.GetWeapon.Name + " ' ---|\n");
                attacker.unreadyOne(hit);
            }
            else
            {
                durability -= damage;
            }
            return;

        }

        public void destroy()
        {
            durability = 0;
        }

        public double getDur(bool cout)
        {
            if (cout)
            {
                Console.WriteLine("Target '" + name + "' has "+durability+" durability");
            }
            return durability;
        }

        public void Dispose()
        {
            if (disposed) return;

            foreach(Warrior attacker in attackers)
            {
                attacker.unreadyOne(hit);
            }
            disposed = true;
            //GC.SuppressFinalize(this);
        }

        public bool isAlive { get { return durability != 0; } }
    }
    #endregion
}
