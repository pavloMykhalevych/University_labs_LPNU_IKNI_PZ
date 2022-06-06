using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    public class Casino : ISubject
    {
        private Casino()
        {
            Attach(new NewGameObserver());
            Attach(new DayObserver());
            Notify();
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

        private List<IObserver> _observers = new List<IObserver>();
        public void Attach(IObserver observer)
        {
            _observers.Add(observer);
        }
        public void Detach(IObserver observer)
        {
            _observers.Remove(observer);
        }
        public void Notify()
        {
            foreach (var observer in _observers)
            {
                observer.Update(this);
            }
        }

        public Building Building = new Building();
        public List<Table> tables = new List<Table>();

        public void PassDay(float ratio, int probability)
        {
            int income = Building.Profit();
            foreach (var table in tables)
            {
                if (table.HasCroupier)
                {
                    income += table.Croupier.Income();
                }
            }

            int guardsLevel = 0;
            int cheated = 0;
            int caught = 0;
            foreach (var table in tables)
            {
                if (table.Player.IsSwindler())
                {
                    bool Robbed = true;
                    if (guardsLevel > table.Player.GetLevel() * 2)
                    {
                        Robbed = false;
                        CaughtSwindlers += 1;
                        ++caught;
                        break;
                    }
                    if (table.HasGuard)
                    {
                        if (table.Guard.Level < table.Player.GetLevel() * 2)
                        {
                            guardsLevel += table.Guard.Level;
                        }
                        else
                        {
                            Robbed = false;
                            CaughtSwindlers += 1;
                            ++caught;
                            break;
                        }
                    }
                    if (Robbed) { cheated += table.Player.Profit(); }
                }
            }
            if (cheated > 0)
            {
                Form1.GetInstance().CallMessage("The swindlers take out of your casino " + cheated.ToString() + "$ today.", "Bad news!");
            }
            int players_winnings = 0;
            foreach (var table in tables)
            {
                if (!table.Player.IsSwindler())
                {
                    players_winnings += table.Player.Profit();
                }
            }
            if (caught > 0)
            {
                if (caught == 1)
                    Form1.GetInstance().CallMessage("Your guards caught " + caught.ToString() + " swindler today.", "Cool news!");
                else
                    Form1.GetInstance().CallMessage("Your guards caught " + caught.ToString() + " swindlers today.", "Cool news!");
            }
            Profit = (int)(income / ratio) - (PreviousBalance - Balance) - cheated - players_winnings;
            var prof = income - cheated;
            Balance += prof;
            PreviousBalance = Balance;
            Day += 1;
            foreach (var table in tables)
            {
                table.RemoveSwindler();
            }
            int randomnumber = random.Next(0, 100);
            bool swindlerCome = false;
            if (randomnumber > 100 - probability)
            {
                swindlerCome = true;
            }
            if (swindlerCome)
            {
                randomnumber = random.Next(1, Math.Min(tables.Count, 3) + 1);
                int count = randomnumber;

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
                    var sw = GameFacade.GetInstance().BuildSwindler(type);
                    int tableIdx = random.Next(0, tables.Count);
                    tables[tableIdx].AddSwindler(sw);
                    randomnumber = random.Next(0, 3);
                    Form1.GetInstance().CallMessage(DecoratorHelper.Message(randomnumber, sw, tableIdx), "Bad news!");
                }
            }
            Notify();
        }

        private static Casino instance;
        public static Random random = new Random();
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
