using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GunsOfLife
{
    class Program
    {
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
            chief.addSubordinate(strelok);
            chief.addSubordinate(mechnik);
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
            Console.WriteLine("\n\n");
            chief.commandAttack();
            chief.commandAttack();
            Console.WriteLine("\n\n");
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
            Console.ReadKey();
        }
    }
}
