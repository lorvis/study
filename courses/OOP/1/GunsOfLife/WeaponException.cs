using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GunsOfLife
{

    class WeaponException : Exception
    {
        Weapon weapon = null;
        public WeaponException()
        {

        }

        public WeaponException(string message) : base(message)
        {

        }

        public WeaponException(string message, Exception inner) : base(message, inner)
        {

        }

        public WeaponException(string message, Exception inner, Weapon weapon) : base(message, inner)
        {
            this.weapon = weapon;
        }
    }
}
