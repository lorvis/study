using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GunsOfLife
{
    #region enums
    public enum weaponsDmgTypes { UNKNOWN, PIERCING, CUTTING, IGNITING, EXPLODING, SCOURCHING, FROZING, BLUNT, ACRID }
    public enum meleeDmgTypes { PIERCING = weaponsDmgTypes.PIERCING, CUTTING = weaponsDmgTypes.CUTTING, BLUNT = weaponsDmgTypes.BLUNT }
    public enum firearmDmgTypes { PIERCING = weaponsDmgTypes.PIERCING, IGNITING = weaponsDmgTypes.IGNITING, EXPLODING = weaponsDmgTypes.EXPLODING, BLUNT = weaponsDmgTypes.BLUNT }
    public enum firearmFireModes { SINGLE = 0, BURST = 1, AUTO = 2 }
    public enum artilleryShellTypes { AP, HE, HEAP, APDS }

    #endregion

    #region  dealer TODO?????
    //todo
    //public static class WeaponDealer
    //{
    //    list<weapon> arsenal = new list<weapon>();
    //}

    // Creating static class attempt
    #endregion

    #region events stuff

    public delegate void HitDelegate(Warrior attacker, HitArgs args);
    #endregion

    #region human
    interface IHuman
    {
        string Name { get; }
        string Surname { get; }
    }
    
    public class Human : IHuman
    {
        protected string name;
        protected string surname;

        public Human(string name, string surname)
        {
            this.name = name;
            this.surname = surname;
        }

        public string Name { get { return name; } }
        public string Surname { get { return surname; } }
    }
    #endregion

    #region commander


    public class Commander : Human, IHuman
    {
        List<Warrior> subordinatesList = new List<Warrior>();

        public Commander(string name, string surname):base(name,surname)
        {

        }

        public void addSubordinate(Warrior subordinate)
        {
            subordinatesList.Add(subordinate);
        }

        public void removeSubordinate(Warrior subordinate)
        {
            subordinatesList.Remove(subordinate);
        }

        public void target(Target[] targets)
        {
            foreach(Warrior w in subordinatesList)
            {
                foreach(Target t in targets)
                {
                    if(t.isAlive)
                    {
                        w.addTarget(t);
                    }
                }
            }
        }

        public void commandAttack()
        {
            foreach (Warrior w in subordinatesList)
            {
                w.readyAll();
                w.attack();
            }
        }
    }
    #endregion

    #region warrior interfaces

    interface IWarrior : IHuman
    {
        void addTarget(Target target);
        void readyAll();
        void readyOne();
        void unreadyOne(HitDelegate hitdeleg);
  
        Weapon GetWeapon { get; }
        double Mastery { get; }
        double Strength { get; }
        double Agility { get; }
    }

    #endregion

    #region warrior
    public abstract class Warrior : Human, IWarrior
    {
        protected double mastery;
        protected double strength;
        protected double agility;
        protected Weapon weapon;
        public Stack<Target> targets = new Stack<Target>();

        public double Mastery { get { return mastery; } }
        public double Strength { get { return strength; } }
        public double Agility { get { return agility; } }
        public Weapon GetWeapon { get { return weapon; } }


        public Warrior(string name, string surname, double mastery, double strength, double agility, Weapon weapon):base(name,surname)
        {
            this.name = name;
            this.surname = surname;
            this.mastery = mastery;
            this.strength = strength;
            this.agility = agility;

            if (weapon == null)
            {
                WarriorBaseInfo wInfo = new WarriorBaseInfo(name, surname, mastery, strength, agility);
                WarriorException e = new WarriorException("Weapon is null",wInfo);
                throw e;
            }

            this.weapon = weapon;
            this.weapon.Holder = this;
        }

        public void addTarget(Target target)
        {
            targets.Push(target);
        }

        public virtual void readyOne()
        {
            if (targets.Count != 0)
            {
                weapon.HitEvent += targets.Pop().hit;
            }
        }

        public virtual void unreadyOne(HitDelegate hitdeleg)
        {
                weapon.unready(hitdeleg);
        }

        public virtual void readyAll()
        {
            int size = targets.Count;
            for (int i = 0; i < size; i++)
            {
                Target target = targets.Pop();
                weapon.ready(new HitDelegate(target.hit));
            }
        }

         public virtual void attack()
        {

        }
    }

    public class Gunner : Warrior, IWarrior
    {
        protected Firearm gun;
        public Gunner(string name, string surname, double mastery, double strength, double agility, Firearm weapon) :base(name, surname, mastery, strength, agility, weapon)
        {
            this.weapon = weapon;
            gun = weapon;
        }

        public override void readyAll()
        {
            int size = targets.Count;
            for (int i = 0; i < size; i++)
            {
                Target target = targets.Pop();
                gun.ready(new HitDelegate(target.hit));
            }
        }

        public override void readyOne()
        {
            if (targets.Count != 0)
            {
                gun.HitEvent += targets.Pop().hit;
            }
        }

        public override void unreadyOne(HitDelegate hitdeleg)
        {
            gun.unready(hitdeleg);
        }

        public override void attack()
        {
            gun.fire();
        }
    }

    public class MeleeWarrior : Warrior, IWarrior
    {
        MeleeWeapon meleeWep;
        public MeleeWarrior(string name, string surname, double mastery, double strength, double agility, MeleeWeapon weapon) : base(name, surname, mastery, strength, agility, weapon)
        {
            this.weapon = weapon;
            meleeWep = weapon;
        }

        public override void readyAll()
        {
            int size = targets.Count;
            for (int i = 0; i < size; i++)
            {
                Target target = targets.Pop();
                meleeWep.ready(new HitDelegate(target.hit));
            }
        }

        public override void readyOne()
        {
            if (targets.Count != 0)
            {
                meleeWep.HitEvent += targets.Pop().hit;
            }
        }

        public override void unreadyOne(HitDelegate hitdeleg)
        {
            meleeWep.unready(hitdeleg);
        }

        public override void attack()
        {
            meleeWep.attack();
        }
    }

    public class Rifleman : Gunner, IWarrior
    {
        AutoRifle rifle;

        public Rifleman(string name, string surname, double mastery, double strength, double agility, AutoRifle rifle) :base(name, surname, mastery, strength, agility, rifle)
        {
            weapon = rifle;
            gun = rifle;
            this.rifle = rifle;
        }

        public override void readyAll()
        {
            int size = targets.Count;
            for (int i = 0; i < size; i++)
            {
                Target target = targets.Pop();
                rifle.ready(new HitDelegate(target.hit));
            }
        }

        public override void readyOne()
        {
            if (targets.Count != 0)
            {
                rifle.HitEvent += targets.Pop().hit;
            }
        }

        public override void unreadyOne(HitDelegate hitdeleg)
        {
            rifle.unready(hitdeleg);
        }

        public override void attack()
        {
            rifle.fire();
        }
    }
    #endregion

    #region weapon interfaces

    public interface IGood
    {
        string Name { get; }
        int Cost { get; }
    }

    public interface IWeapon
    {
        string Name { get; }
        weaponsDmgTypes DamageType { get; }
        void ready(HitDelegate eventHandler);
    }

    public interface IMelee : IWeapon
    {
        double DmgMultMastery { get; }
        double DmgMultStr { get; }

        void attack();
    }

    public interface IFirearm : IWeapon
    {
        void fire();
        void reload();
        double DmgMultAccuracy { get; }
        int MaxAmmo { get; }
        int LoadedAmmo { get; }
    }

    public interface IAutoRifle : IFirearm
    {
        byte FireMode { get; }
    }




    #endregion

    #region weapon

    public abstract class Weapon : IGood, IWeapon
    {
        protected weaponsDmgTypes damageType;
        protected string name;
        protected int cost;

        protected Warrior holder;

        public Warrior Holder { get { return holder; } set { holder = value;  } }

        protected Weapon() : this(weaponsDmgTypes.UNKNOWN, "Unnamed", 0)
        {

        }

        protected Weapon(weaponsDmgTypes dmgType, string name, int cost)
        {
            damageType = dmgType;
            this.name = name;
            this.cost = cost;
            holder = null;
        }

        public event HitDelegate HitEvent;

        public virtual void ready(HitDelegate eventHandler)
        {
            HitEvent += eventHandler;
        }

        public virtual void unready(HitDelegate eventHandler)
        {
            HitEvent -= eventHandler;
        }

        public string Name
        {
            get { return name; }
        }

        public int Cost
        {
            get { return cost; }
        }

        public weaponsDmgTypes DamageType
        {
            get { return damageType; }
        }

        protected void attack(weaponsDmgTypes dmgtype, double power)
        {
            HitEvent(holder, new HitArgs(dmgtype, power));
        }
    }

    public class MeleeWeapon : Weapon, IMelee, IGood
    {
        static double dmgMultMastery;
        static double dmgMultStr;
        new meleeDmgTypes damageType;
        new public event HitDelegate HitEvent;

        public MeleeWeapon(meleeDmgTypes dmgtype, string name, int cost, double masteryMult, double strMult) : base((weaponsDmgTypes)dmgtype, name, cost)
        {
            dmgMultMastery = masteryMult;
            dmgMultStr = strMult;
            damageType = dmgtype;
        }

        public double DmgMultMastery
        {
            get { return dmgMultMastery; }
        }

        public double DmgMultStr
        {
            get { return dmgMultStr; }
        }

        public override void ready(HitDelegate eventHandler)
        {
            ((MeleeWeapon)this).HitEvent += eventHandler;
        }

        public override void unready(HitDelegate eventHandler)
        {
            ((MeleeWeapon)this).HitEvent -= eventHandler;
        }

        public void attack()
        {
            if (HitEvent != null)
            {
                double hitpower = dmgMultMastery * holder.Mastery * dmgMultStr * holder.Strength;
                HitEvent(holder, new HitArgs((weaponsDmgTypes)damageType, hitpower));
            }
        }
    }

    public abstract class Firearm:Weapon, IFirearm, IGood
    {
        protected static double dmgMultAccuracy;
        protected static int maxAmmo;
        protected int loadedAmmo;
        new firearmDmgTypes damageType;
        new public event HitDelegate HitEvent;

        public Firearm(firearmDmgTypes dmgtype, string name, int cost, double accuracyMult, int ammoCap) : base((weaponsDmgTypes)dmgtype, name, cost)
        {
            damageType = dmgtype;
            dmgMultAccuracy = accuracyMult;
            maxAmmo = ammoCap;
            reload();
        }

        public override void ready(HitDelegate eventHandler)
        {
            ((Firearm)this).HitEvent += eventHandler;
        }

        public override void unready(HitDelegate eventHandler)
        {
            ((Firearm)this).HitEvent -= eventHandler;
        }

        //maybe it's a mistake to let this class fire
        virtual public void fire()
        {
            if (loadedAmmo > 0)
            {
                if (HitEvent != null)
                {
                    double hitpower = holder.Agility * holder.Mastery;
                    HitEvent(holder, new HitArgs((weaponsDmgTypes)damageType, hitpower));
                }
            }
            else
            {
                reload();
                Console.WriteLine("No ammo loaded, reloading");
            }
        }

        public void reload()
        {
            loadedAmmo = maxAmmo;
        }

        public double DmgMultAccuracy
        {
            get { return dmgMultAccuracy; }
        }

        public int MaxAmmo
        {
            get { return maxAmmo; }
        }

        public int LoadedAmmo
        {
            get { return loadedAmmo; }
        }

        public bool Empty
        {
            get { return loadedAmmo == 0; }
        }
    }

    public class AutoRifle:Firearm, IAutoRifle
    {
        new public event HitDelegate HitEvent;
        byte fireMode;

        public AutoRifle(firearmDmgTypes dmgtype, string name, int cost, double accuracyMult, int maxAmmo, firearmFireModes fireMode) :base(dmgtype,name,cost,accuracyMult,maxAmmo)
        {
            this.fireMode = (byte)fireMode;
        }

        public byte FireMode
        {
            get { return fireMode; }
        }

        public override void ready(HitDelegate eventHandler)
        {
            ((AutoRifle)this).HitEvent += eventHandler;
        }

        public override void unready(HitDelegate eventHandler)
        {
            ((AutoRifle)this).HitEvent -= eventHandler;
        }

        protected void singleFire()
        {
            if (loadedAmmo > 0)
            {
                if (HitEvent != null)
                {
                    double hitpower = holder.Agility * holder.Mastery;
                    HitEvent(holder, new HitArgs((weaponsDmgTypes)damageType, hitpower));
                }
            }
            else
            {
                reload();
                Console.WriteLine("No ammo loaded, reloading");
            }
        }

        public override void fire() { 

            // for memory efficiency here is few bools in one byte "firemode" so i use bit logic operators
            if ((fireMode & ((byte)firearmFireModes.SINGLE | (byte)firearmFireModes.AUTO )) != 0 )
            singleFire();
            else
                for (int i = 0; i < 3; i++)
                    singleFire();
        }

    }
    // attempt to make a private constructor
    public class Artillery:Firearm, IFirearm, IGood
    {

        new public event HitDelegate HitEvent;

        static Artillery create()
        {
            return new Artillery();
        }

        private Artillery():base(firearmDmgTypes.EXPLODING,"Some artillery",5000,6000,5)
        {

        }
    }

    #endregion


}