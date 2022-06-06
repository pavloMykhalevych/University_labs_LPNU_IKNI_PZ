using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    public abstract class State
    {
        public abstract string GetMessage();
    }
    public class StateEasy : State
    {
        public override string GetMessage()
        {
            return "Now game level is Easy!";
        }
    }

    public class StateHard : State
    {
        public override string GetMessage()
        {
            return "Now game level is Hard!";
        }
    }
}
