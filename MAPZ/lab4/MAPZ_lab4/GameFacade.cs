using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    public class GameFacade
    {
        public Casino Casino;

        public IEmployer croupierEmployee = new CroupierEmployer();
        public IEmployer guardEmployee = new GuardEmployer();
        public SwindlerBuilder swindlerBuilder = new SwindlerBuilder();
        public SwindlerDirector swindlerDirector = new SwindlerDirector();

        private State state = new StateEasy();
        private IStrategy _complexity = new StrategyEasy();
        public void SetStrategy(IStrategy strategy)
        {
            _complexity = strategy;
            string mes = "";
            if(_complexity is StrategyEasy)
            {
                mes = TransitionTo(new StateEasy());
            }
            else if (_complexity is StrategyHard)
            {
                mes = TransitionTo(new StateHard());
            }
            Form1.GetInstance().CallMessage($"You change game complexity!\n{mes}\n{state.GetMessage()}", "Info");
        }
        public string TransitionTo(State state)
        {
            this.state = state;
            return "You change game state!";
        }
        public Swindler BuildSwindler(int type)
        {
            return swindlerDirector.BuildSwindler(swindlerBuilder, type);
        }
        public void HireNewCroupier(int index)
        {
            Casino.tables[index].AddCroupier(Hire(croupierEmployee));
        }
        public void HireNewGuard(int index)
        {
            Casino.tables[index].AddGuard(Hire(guardEmployee));
        }
        private IEmployee Hire(IEmployer employer)
        {
            return employer.Hire(Casino.random);
        }
        public void NewGame()
        {
            Casino.NewGame();
            Casino = Casino.GetInstance();
        }
        public void PassDay()
        {
            Casino.PassDay(_complexity.ProfitRatio(), _complexity.SwindlerProbability());
        }

        private static GameFacade instance;
        public static GameFacade GetInstance()
        {
            if (instance == null)
                instance = new GameFacade();
            return instance;
        }
    }
}
