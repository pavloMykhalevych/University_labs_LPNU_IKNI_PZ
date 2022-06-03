using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    public class GameFacade
    {
        public Casino Casino = Casino.GetInstance();

        public IEmployer croupierEmployee = new CroupierEmployer();
        public IEmployer guardEmployee = new GuardEmployer();
        public SwindlerBuilder swindlerBuilder = new SwindlerBuilder();
        public SwindlerDirector swindlerDirector = new SwindlerDirector();
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

        private static GameFacade instance;
        public static GameFacade GetInstance()
        {
            if (instance == null)
                instance = new GameFacade();
            return instance;
        }
    }
}
