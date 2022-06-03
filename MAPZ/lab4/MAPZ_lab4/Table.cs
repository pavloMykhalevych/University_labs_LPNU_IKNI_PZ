using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    public class Table
    {
        public IEmployee Guard;
        public IEmployee Croupier;
        public bool HasGuard = false;
        public bool HasCroupier = false;
        public ProxyPlayer Player = new ProxyPlayer();
        public void AddGuard(IEmployee guard)
        {
            Guard = guard;
            HasGuard = true;
        }
        public void AddCroupier(IEmployee croupier)
        {
            Croupier = croupier;
            HasCroupier = true;
        }
        public void AddSwindler(Swindler swindler)
        {
            Player.SetSwindler(swindler);
        }
        public void RemoveSwindler()
        {
            Player.Clear();
        }
    }
}
