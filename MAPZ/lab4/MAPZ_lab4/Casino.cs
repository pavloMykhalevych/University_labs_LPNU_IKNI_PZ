using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    public class Casino
    {
        private Casino()
        {
            random = new Random();
            Profit = 0;
            Balance = 5000;
            PreviousBalance = Balance;
            CaughtSwindlers = 0;
        }
        public int Profit { set; get; }
        public int Balance { set; get; }
        public int PreviousBalance { set; get; }
        public int CaughtSwindlers { set; get; }
        public int Day { set; get; }

        public IEmployer croupierEmployee = new CroupierEmployer();
        public IEmployer guardEmployee = new GuardEmployer();
        public List<IEmployee> Croupiers = new List<IEmployee>();
        public List<IEmployee> Guards = new List<IEmployee>();
        public SwindlerBuilder swindlerBuilder = new SwindlerBuilder();
        public SwindlerDirector swindlerDirector = new SwindlerDirector();
        public Building Building = new Building();

        public void PassDay()
        {
            int randomnumber = random.Next(0, 100);
            bool swindlerCome = false;
            if (randomnumber > 90)
            {
                swindlerCome = true;
            }
            int income = Building.Profit();
            int cheated = 0;
            int caught = 0;
            foreach (var croupier in Croupiers)
            {
                income += croupier.Income();
            }
            if (swindlerCome)
            {
                randomnumber = random.Next(0, (Building.Tables + 1) * 10);
                int count = 0;
                for (var i = 1; i < Building.Tables + 1; ++i)
                {
                    if (randomnumber - (Building.Tables + 1 - i) * 10 < 0)
                    {
                        count = i-1;
                    }
                }
                var guards = new List<IEmployee>(Guards);
                for (var counter = 0; counter < count; ++counter)
                {
                    int[] weights1 = { 36, 62, 77, 89, 96, 99, 100 };
                    int type = 0;
                    randomnumber = random.Next(0, 100);
                    for (var i = 0; i < weights1.Length; ++i)
                    {
                        if (randomnumber - weights1[i] < 0)
                        {
                            type = i + 1;
                            break;
                        }
                    }
                    var sw = swindlerDirector.BuildSwindler(swindlerBuilder, type);
                    int guardsLevel = 0;
                    bool Robbed = true;
                    foreach (var g in guards)
                    {
                        if(guardsLevel > sw.Level * 2)
                        {
                            Robbed = false;
                            CaughtSwindlers += 1;
                            ++caught;
                            break;
                        }
                        if (g.Level < sw.Level * 2)
                        {
                            guards.Remove(g);
                            guardsLevel += g.Level;
                        }
                        else
                        {
                            Robbed = false;
                            CaughtSwindlers += 1;
                            ++caught;
                            guards.Remove(g);
                            break;
                        }
                    }
                    if (Robbed) { cheated += sw.Robbed(); }
                }
            }
            if(cheated > 0)
            {
                Form1.GetInstance().CallMessage("The swindlers take out of your casino " + cheated.ToString() + "$ today.");
            }
            if (caught > 0)
            {
                if (caught == 1)
                    Form1.GetInstance().CallMessage("Your guards caught " + caught.ToString() + " swindler today.");
                else
                    Form1.GetInstance().CallMessage("Your guards caught " + caught.ToString() + " swindlers today.");
            }
            Profit = income - (PreviousBalance - Balance) - cheated;
            var prof = income - cheated;
            Balance += prof;
            Form1.GetInstance().CallMessage("The swindlers take out of your casino " + 1000.ToString() + "$ today.");
            PreviousBalance = Balance;
            Day += 1;
        }
        public void HireNewCroupier()
        {
            Croupiers.Add(Hire(croupierEmployee));
        }
        public void HireNewGuard()
        {
            Guards.Add(Hire(guardEmployee));
        }
        private IEmployee Hire(IEmployer employer)
        {
            return employer.Hire(random);
        }

        private static Casino instance;
        private static Random random;
        public static Casino GetInstance()
        {
            if (instance == null)
                instance = new Casino();
            return instance;
        }
        public static void NewGame()
        {
            instance = new Casino();
        }
    }
}
