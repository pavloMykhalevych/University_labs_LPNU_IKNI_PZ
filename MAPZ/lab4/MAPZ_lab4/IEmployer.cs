using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    public interface IEmployee
    {
        int GetWage();
        void Improve();
        int Income();
        int ImprovePrice();
        int Level { set; get; }
    }
    public interface IEmployer
    {
        IEmployee Hire(Random random);
    }
    public class CroupierEmployer : IEmployer {
        public IEmployee Hire(Random random)
        {
            int randomNumber = random.Next(1, 1000000);
            if (randomNumber == 555555)
            {
                randomNumber = 30;
            }
            else if (randomNumber < 900000 && randomNumber > 850000)
            {
                randomNumber = random.Next(8, 15);
            }
            else
            {
                randomNumber = random.Next(1, 3);
            }
            return new Croupier(randomNumber);
        }
    }
    public class GuardEmployer : IEmployer {
        public IEmployee Hire(Random random)
        {
            int randomNumber = random.Next(1, 1000000);
            if (randomNumber == 555555)
            {
                randomNumber = 10;
            }
            else if (randomNumber < 900000 && randomNumber > 850000)
            {
                randomNumber = random.Next(5, 8);
            }
            else
            {
                randomNumber = random.Next(1, 3);
            }
            return new Guard(randomNumber);
        }
    }
    public class Croupier : IEmployee
    {
        public Croupier()
        {
            Level = 1;
        }
        public Croupier(int level)
        {
            Level = level;
        }
        public int Level { set; get; }
        public void Improve()
        {
            Casino.GetInstance().Balance -= ImprovePrice();
            Level += 1;
        }
        public int ImprovePrice()
        {
            return 100 + (Level - 1) * 40;
        }
        public int GetWage()
        {
            return 700 + (Level - 1) * 60;
        }
        public int Income()
        {
            return 5 + 2 * (Level - 1);
        }
    }
    public class Guard : IEmployee
    {
        public Guard()
        {
            Level = 1;
        }
        public Guard(int level)
        {
            Level = level;
        }
        public int Level { set; get; }
        public void Improve()
        {
            Casino.GetInstance().Balance -= ImprovePrice();
            Level += 1;
        }
        public int ImprovePrice()
        {
            return 70 + (Level - 1) * 30;
        }
        public int GetWage()
        {
            return 700 + (Level - 1) * 50;
        }
        public int Income()
        {
            return 0;
        }
    }
}
