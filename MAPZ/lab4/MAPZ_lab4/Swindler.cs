using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    public class SwindlerBuilder
    {
        private Swindler swindler = new Swindler();
        public void SetExperience(int experience)
        {
            swindler.Experience = experience;
        }
        public void SetCheatInBigCasinos()
        {
            swindler.CheatInBigCasinos = true;
        }
        public void SethasTeam()
        {
            swindler.HasTeam = true;
        }
        public void SetKnowMathematics()
        {
            swindler.KnowMathematics = true;
        }
        public void SetWasInOurCasino()
        {
            swindler.WasInOurCasino = true;
        }
        public Swindler ReturnSwindler()
        {
            swindler.CalculateLevel();
            Swindler result = swindler;
            swindler = new Swindler();
            return result;
        }
        public void ResetSwindler()
        {
            swindler = new Swindler();
        }
    }
    public class SwindlerDirector
    {
        public Swindler Newcommer(SwindlerBuilder builder)
        {
            builder.ResetSwindler();
            return builder.ReturnSwindler();
        }
        public Swindler Junior(SwindlerBuilder builder)
        {
            builder.ResetSwindler();
            builder.SetExperience(1);
            return builder.ReturnSwindler();
        }
        public Swindler Middle(SwindlerBuilder builder)
        {
            builder.ResetSwindler();
            builder.SetExperience(2);
            builder.SetKnowMathematics();
            return builder.ReturnSwindler();
        }
        public Swindler Senior(SwindlerBuilder builder)
        {
            builder.ResetSwindler();
            builder.SetExperience(4);
            builder.SetWasInOurCasino();
            builder.SetKnowMathematics();
            return builder.ReturnSwindler();
        }
        public Swindler Principle(SwindlerBuilder builder)
        {
            builder.ResetSwindler();
            builder.SetExperience(6);
            builder.SetWasInOurCasino();
            builder.SetKnowMathematics();
            builder.SetCheatInBigCasinos();
            return builder.ReturnSwindler();
        }
        public Swindler Master(SwindlerBuilder builder)
        {
            builder.ResetSwindler();
            builder.SetExperience(10);
            builder.SetWasInOurCasino();
            builder.SetKnowMathematics();
            builder.SetCheatInBigCasinos();
            builder.SethasTeam();
            return builder.ReturnSwindler();
        }
        public Swindler MasterRandom(SwindlerBuilder builder)
        {
            builder.ResetSwindler();
            Random random = new Random();
            builder.SetExperience(random.Next(10, 40));
            builder.SetWasInOurCasino();
            builder.SetKnowMathematics();
            builder.SetCheatInBigCasinos();
            builder.SethasTeam();
            return builder.ReturnSwindler();
        }
        public Swindler BuildSwindler(SwindlerBuilder builder, int type)
        {
            switch (type)
            {
                case 1:
                    return Newcommer(builder);
                case 2:
                    return Junior(builder);
                case 3:
                    return Middle(builder);
                case 4:
                    return Senior(builder);
                case 5:
                    return Principle(builder);
                case 6:
                    return Master(builder);
                case 7:
                    return MasterRandom(builder);
                default:
                    return Newcommer(builder);
            }
        }
    }
    interface IPlayer
    {
        int Level { set; get; }
        int Profit();
    }
    public class Swindler : IPlayer
    {
        public Swindler()
        {
            Level = 0;
            Experience = 0;
            CheatInBigCasinos = false;
            HasTeam = false;
            KnowMathematics = false;
            WasInOurCasino = false;
        }
        public Swindler(int level)
        {
            Level = level;
        }
        public int Profit()
        {
            int max = Casino.GetInstance().Balance;
            if(max <= 20000)
            {
                max = 20000;
            }
            int sum = Level * 300;
            return Math.Min(sum, max);
        }
        public void CalculateLevel()
        {
            Level = 1 * (Experience + 1);
            if (CheatInBigCasinos)
            {
                Level *= 3;
            }
            if (HasTeam)
            {
                Level *= 2;
            }
            if (KnowMathematics)
            {
                Level += 3;
            }
            if (WasInOurCasino)
            {
                Level += 2;
            }
        }
        public int Level { set; get; }
        public int Experience { set; get; }
        public bool CheatInBigCasinos { set; get; }
        public bool HasTeam { set; get; }
        public bool KnowMathematics { set; get; }
        public bool WasInOurCasino { set; get; }
    }
    public class ProxyPlayer : IPlayer
    {
        public Swindler _swindler = null;
        public int Level { set; get; } = Casino.random.Next(0, 100);
        public int Profit()
        {
            if(_swindler == null)
            {
                return Level;
            }
            else
            {
                return _swindler.Profit();
            }
        }
        public int GetLevel()
        {
            if (_swindler == null)
            {
                return Level;
            }
            else
            {
                return _swindler.Level;
            }
        }
        public bool IsSwindler()
        {
            return _swindler != null;
        }
        public void Clear()
        {
            _swindler = null;
            Level = Casino.random.Next(0, 100);
        }
        public void SetSwindler(Swindler swindler)
        {
            _swindler = swindler;
        }
    }
}
