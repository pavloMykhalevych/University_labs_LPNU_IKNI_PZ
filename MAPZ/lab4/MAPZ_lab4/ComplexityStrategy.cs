using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    public interface IStrategy
    {
        float ProfitRatio();
        int SwindlerProbability();
    }
    public class StrategyEasy : IStrategy
    {
        public float ProfitRatio()
        {
            return 0.3F;
        }
        public int SwindlerProbability()
        {
            return 10;
        }
    }
    public class StrategyHard : IStrategy
    {
        public float ProfitRatio()
        {
            return 1;
        }
        public int SwindlerProbability()
        {
            return 30;
        }
    }
}
