using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    class PauseMenu
    {
        private static PauseMenu instance;
        public static PauseMenu GetInstance()
        {
            if (instance == null)
                instance = new PauseMenu();
            return instance;
        }
        public void GoToMainMenu()
        {
            Form1.GetInstance().OpenMainMenu();
        }
        public void Resume()
        {
            Form1.GetInstance().ClosePauseMenu();
        }
    }
}
