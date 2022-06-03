using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAPZ_lab4
{
    public abstract class ISwindlerInfo
    {
        public abstract string GetInfo(Swindler swindler, int tableIndex);
    }
    public class SwindlerInfo : ISwindlerInfo
    {
        public override string GetInfo(Swindler swindler, int tableIndex)
        {
            return $"To {tableIndex + 1} table come swindler ";
        }
    }
    public abstract class SwindlerMessageDecorator : ISwindlerInfo
    {
        protected ISwindlerInfo swindlerInfo;
        public void SetPlayer(ISwindlerInfo info)
        {
            swindlerInfo = info;
        }
        public override string GetInfo(Swindler swindler, int tableIndex)
        {
            if (swindlerInfo != null)
            {
                return swindlerInfo.GetInfo(swindler, tableIndex);
            }
            else return string.Empty;
        }
    }
    public class DefaultSwindlerMessageDecorator : SwindlerMessageDecorator
    {
        public override string GetInfo(Swindler swindler, int tableIndex)
        {
            return base.GetInfo(swindler, tableIndex);
        }
    }
    public class LevelSwindlerMessageDecorator : SwindlerMessageDecorator
    {
        public override string GetInfo(Swindler swindler, int tableIndex)
        {
            var str = base.GetInfo(swindler, tableIndex);
            str += $"with lvl {swindler.Level}";
            return str;
        }
    }
    public class AllInfoSwindlerMessageDecorator : SwindlerMessageDecorator
    {
        public override string GetInfo(Swindler swindler, int tableIndex)
        {
            var str = base.GetInfo(swindler, tableIndex);
            str += $"with lvl {swindler.Level}.\n";
            str += $"He has {swindler.Experience} year of experience.\n";
            if (swindler.KnowMathematics)
            {
                str += $"He knows mathematic.\n";
            }
            if (swindler.HasTeam)
            {
                str += $"He has team.\n";
            }
            if (swindler.CheatInBigCasinos)
            {
                str += $"He has already cheated in big casinos.\n";
            }
            if (swindler.WasInOurCasino)
            {
                str += $"And he has already been in our casino.\n";
            }
            return str;
        }
    }
    public class DecoratorHelper
    {
        public static string Message(int type, Swindler player, int tableIndex)
        {
            SwindlerMessageDecorator decorator = new DefaultSwindlerMessageDecorator();
            switch (type)
            {
                case 1:
                    decorator = new LevelSwindlerMessageDecorator();
                    break;
                case 2:
                    decorator = new AllInfoSwindlerMessageDecorator();
                    break;
            }
            decorator.SetPlayer(new SwindlerInfo());
            return decorator.GetInfo(player, tableIndex);
        }
    }
}
