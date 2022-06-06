using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    public interface IObserver
    {
        void Update(ISubject subject);
    }
    public interface ISubject
    {
        void Attach(IObserver observer);

        void Detach(IObserver observer);

        void Notify();
    }
    public class DayObserver : IObserver
    {
        private List<string> advices = new List<string>{
            "Track your spending to improve your finances",
            "Create a realistic monthly budget",
            "Build up your savings—even if it takes time",
            "Pay your bills on time every month",
            "Cut back on recurring charges",
            "Save up cash to afford big purchases",
            "Start an investment strategy",
            "Make sure you’re paying the best prices",
            "Save up for big purchases",
            "Contribute to savings regularly",
            "Start investing",
            "Contribute to your retirement",
            "Plan for large expenses",
            "Build an emergency fund",
            "Take a look at your income" };
        public void Update(ISubject subject)
        {
            if ((subject as Casino).Day == 0)
            {
                return;
            }
            if ((subject as Casino).Day % 2 == 0)
            {
                Form1.GetInstance().CallMessage($"Today is your {(subject as Casino).Day} day as casino manager. Some advice:\n{advices[Casino.random.Next(0, advices.Count)]}", "Dayly news!");
            }
            else if((subject as Casino).Day % 2 == 1)
            {
                Form1.GetInstance().CallMessage($"Today is your {(subject as Casino).Day} day as casino manager.", "Dayly news!");
            }
        }
    }

    public class NewGameObserver : IObserver
    {
        public void Update(ISubject subject)
        {
            if ((subject as Casino).tables.Count == 0 && (subject as Casino).Day == 0)
            {
                Form1.GetInstance().CallMessage("You start the new game!", "Welcome!");
            }
        }
    }
}
