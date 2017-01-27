
using System;
using System.Xml.Serialization;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GunsOfLife
{
    class Program
    {
        delegate void Fooact(Weapon w);
        static void Main(string[] args)
        {
            Commander chief = new Commander("Alex", "Popov");
            AutoRifle ak_47 = new AutoRifle(firearmDmgTypes.PIERCING, "AK-47", 5000, 5, 40,firearmFireModes.AUTO | firearmFireModes.BURST | firearmFireModes.SINGLE);
            Rifleman strelok = new Rifleman("Mecheniy", "Strelok", 80, 150, 70, ak_47);
            MeleeWeapon sword = new MeleeWeapon(meleeDmgTypes.CUTTING, "ZWEIHANDER", 15000, 4, 12);
            MeleeWarrior mechnik;
            try
            {
                new MeleeWarrior("Alexander", "of Macedon", 20, 15, 35, null);
            }
            catch(WarriorException e)
            {
                if(e.wInfo != null)
                {
                    if (e.wInfo.Name == "Alexander" && e.wInfo.Surname == "of Macedon")
                    {
                        Console.WriteLine("\nEXCEPTION CAUGHT, HERE'S YOUR SWORD, MACEDONSKY\n");
                        mechnik = new MeleeWarrior("Alexander", "Makedonsky", 20, 15, 35, sword);
                    }
                    else
                    {
                        Console.WriteLine("YOU ARE NOT MACEDONSKY!");
                        throw e;
                    }
                }
                else
                {
                    Console.WriteLine("WARRIOR'S INFO IS NULL!");
                    throw e;
                }
            }
            catch(Exception e)
            {
                Console.WriteLine(e);
                Environment.Exit(1);
            }
            finally
            {
                mechnik = new MeleeWarrior("Alexander", "Makedonsky", 20, 15, 35, sword);
            }
            // EVENT SUBSCRIPTION HERE ---
            chief.addSubordinate(strelok);
            chief.addSubordinate(mechnik);
            // ---
            Target mountain = new Target("GORA", 10000);
            Target sea = new Target("MORE", 100000);
            Target horse = new Target("LOSHAD'", 100);
            Target[] tseli = { mountain, sea, horse };
            chief.target(tseli);
            //chief.commandAttack();
            strelok.readyAll();
            strelok.attack();
            strelok.attack();
            mechnik.readyAll();
            Console.WriteLine("\n\n");
            mechnik.attack();
            mechnik.attack();
            Console.WriteLine("\n\n-CHIEF COMMANDS-");
            // HERE MUST BE EVENT ---
            chief.commandAttack();
            chief.commandAttack();
            // ---
            Console.WriteLine("SHOTS MADE = " + chief.Reports);
            Console.WriteLine("\n\n---");
            Target earth = new Target("EARTH", 1000000);
            Target river = new Target("RIVER", 50000);
            Target volcano = new Target("VOLCANO", 600000);
            Target[] tseli2 = { earth, river, volcano };
            AutoRifle fort = new AutoRifle(firearmDmgTypes.PIERCING, "FORT", 10000, 50, 80, firearmFireModes.AUTO | firearmFireModes.BURST | firearmFireModes.SINGLE);
            Rifleman soldier = new Rifleman("Ukrainian", "Soldier", 666, 666, 666, fort);
            chief.removeSubordinate(strelok);
            chief.addSubordinate(soldier);
            chief.target(tseli2);
            chief.commandAttack();
            Console.WriteLine("Completed successfully !!");
            GoodsList < Weapon > weps = new GoodsList<Weapon>();
            Weapon gauntlet = new MeleeWeapon(meleeDmgTypes.BLUNT, "GAUNTLET", 5000, 8, 45);
            Weapon claws = new MeleeWeapon(meleeDmgTypes.PIERCING, "CLAWS", 8000, 4, 25);
            Weapon axe = new MeleeWeapon(meleeDmgTypes.CUTTING, "AXE", 1000, 2, 15);
            weps.add(gauntlet);
            weps.add(claws);
            weps.add(axe);
            weps.print();
            weps.printCosts();
            Console.WriteLine("-----------");
            weps.sort();
            weps.print();
            Console.WriteLine("-----------");
            Console.WriteLine("Here go anons");
            Fooact deleg = w => Console.WriteLine("The name is " + w.Name);
            deleg += w => Console.WriteLine("The cost is " + w.Cost);
            deleg(axe);
            Func<Weapon, string> func = w => { return w.Name; };
            Console.WriteLine("Weapon name from Func : " + func(axe));
            Console.WriteLine("-------------XMLSerialization----------------");
            ExplosivesPack pack = new ExplosivesPack();
            pack.explosivesList.Add(new Explosive("Grenade", 100, 3));
            pack.explosivesList.Add(new Explosive("Bomb", 4000, 60));
            pack.explosivesList.Add(new Explosive("Nuke", 1000000, 500));
            XmlSerializer serializer = new XmlSerializer(typeof(ExplosivesPack), new Type[] { typeof(Explosive) });
            string xml;
            Console.WriteLine("PACK Serializated:");
            using (StringWriter sw = new StringWriter())
            {
                serializer.Serialize(sw, pack);
                xml = sw.ToString();
            }
            Console.WriteLine(xml);
            Console.WriteLine("PACK Deserializated:");
            using(StringReader sr = new StringReader(xml))
            {
                ExplosivesPack pack2 = (ExplosivesPack)serializer.Deserialize(sr);
                foreach(Explosive explosive in pack2.explosivesList)
                {
                    Console.WriteLine("Name: "+ explosive.Name);
                }
            }

            //------------
            //----------------LAB4----------
            //------------
            pack.boomAll();
            Console.WriteLine("SCANNING FOR BOOM-----------------------------");
            pack.scanForBoom();
            GC.Collect();
            Console.WriteLine("SCANNING FOR BOOM-----------------------------");
            pack.scanForBoom();

            Target sun = new Target("Sun", 999999);
            Warrior megaman = new Rifleman("Megaman", "Forgot", 1, 1, 1, new AutoRifle(firearmDmgTypes.IGNITING, "BLASTER", 1, 1, 1, firearmFireModes.SINGLE));
            megaman.addTarget(sun);

            Console.WriteLine("Trying to destroy the Sun 1");
            megaman.readyAll();
            megaman.attack();

            sun.Dispose();

            Console.WriteLine("Trying to destroy the Sun 2");
            megaman.attack();
            megaman.attack();
            megaman.attack();
            megaman.attack();
            megaman.attack();
            megaman.attack();
            megaman.attack();
            megaman.attack();
            megaman.attack();
            megaman.attack();
            megaman.attack();

            Console.WriteLine("Trying ended");
            GC.Collect();
            Console.WriteLine("-=-=-=-=-!!!-=-=-=-=-=-END OF TESTS-=-=-=-=-=-!!!-=-=-=-=-");
            Console.ReadKey();
        }

    }
}

