using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    public class Building
    {
        public Building()
        {
            Tables = 0;
            Level = 1;
            Space = 0;
        }
        public int Tables { get; set; }
        public int Level { get; set; }
        public int Space { get; set; }
        public int ImprovePrice()
        {
            return 500 + (Level + Space - 1) * 500;
        }
        public int SpacePrice()
        {
            return 10000 + (Space) * 2000;
        }
        public int tablePrice()
        {
            return 3000 + (Tables) * 500;
        }
        public bool CanBuyTable()
        {
            if(Tables < 4 + Space * 4)
            {
                return true;
            }
            return false;
        }
        public void BuyTable()
        {
            Casino.GetInstance().Balance -= tablePrice();
            Tables += 1;
        }
        public void BuySpace()
        {
            Casino.GetInstance().Balance -= SpacePrice();
            Space += 1;
            Level = 1;
        }
        public void Upgrade()
        {
            Casino.GetInstance().Balance -= ImprovePrice();
            Level += 1;
        }
        public int Profit()
        {
            return Tables * 500;
        }
    }
}
