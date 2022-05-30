using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    public sealed class MainMenu
    {
        private static MainMenu instance;
        public static MainMenu GetInstance()
        {
            if (instance == null)
                instance = new MainMenu();
            return instance;
        }

        public void Start()
        {
            Form1.GetInstance().OpenGames();
        }
        public void Exit()
        {
            Form1.GetInstance().Close();
        }
    }
}
