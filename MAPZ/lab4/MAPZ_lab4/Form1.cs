using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MAPZ_lab4
{
    public partial class Form1 : Form
    {
        private static Form1 instance;
        public static Form1 GetInstance()
        {
            if (instance == null)
                instance = new Form1();
            return instance;
        }
        public Form1()
        {
            InitializeComponent();
            main_menu.BringToFront();
        }

        private void button_main_menu_Click(object sender, EventArgs e)
        {
            PauseMenu.GetInstance().GoToMainMenu();
        }

        private void button_start_Click(object sender, EventArgs e)
        {
            MainMenu.GetInstance().Start();
            GameFacade.GetInstance().NewGame();
            timer3.Enabled = true;
            timer1.Enabled = true;
        }

        private void button_exit_Click(object sender, EventArgs e)
        {
            MainMenu.GetInstance().Exit();
        }

        public void CallMessage(string mes, string name)
        {
            MessageBox.Show(mes, name);
        }

        public void ClosePauseMenu()
        {
            panel_pause.SendToBack();
            timer3.Enabled = true;
            timer1.Enabled = true;
        }
        public void OpenPauseMenu()
        {
            panel_pause.BringToFront();
            timer3.Enabled = false;
            timer1.Enabled = false;
        }
        public void OpenMainMenu()
        {
            main_menu.BringToFront();
        }
        public void OpenGames()
        {
            panel_games.BringToFront();
        }

        public void OpenTable()
        {
            panel_game_tables.BringToFront();
        }

        private void button_resume_Click(object sender, EventArgs e)
        {
            PauseMenu.GetInstance().Resume();
        }

        private void button_exit_2_Click(object sender, EventArgs e)
        {
            MainMenu.GetInstance().Exit();
        }

        private void button_pause_Click(object sender, EventArgs e)
        {
            panel_pause.BringToFront();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            GameFacade.GetInstance().Casino.PassDay();
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            label_balance.Text = GameFacade.GetInstance().Casino.Balance.ToString() + '$';
            SetProfit(GameFacade.GetInstance().Casino.Profit);

            int croupierCount = 0;
            foreach(var table in GameFacade.GetInstance().Casino.tables)
            {
                if (table.HasCroupier)
                {
                    croupierCount++;
                }
            }
            label_croupier_count.Text = croupierCount.ToString();
            label_croupier_hire.Text = (700 + croupierCount * 200).ToString() + '$';

            int guardCount = 0;
            foreach (var table in GameFacade.GetInstance().Casino.tables)
            {
                if (table.HasGuard)
                {
                    guardCount++;
                }
            }
            label_guards_count.Text = guardCount.ToString();
            label_guard_hire.Text = (500 + guardCount * 100).ToString() + '$';

            if (spinBox_table.Value == 0)
            {
                return;
            }
            if (GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].HasGuard)
            {
                label_guard_lvl_image.Visible = true;
                label_guard_image.Visible = true;
                pictureBox_guard.Visible = true;
                guard_lvl.Text = GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Guard.Level.ToString();
                label_guard_lvl_image.Text = GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Guard.Level.ToString();
                label_improve_guard_price.Text = GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Guard.ImprovePrice().ToString();
            }
            else
            {
                guard_lvl.Text = "None";
                label_improve_guard_price.Text = "";
                label_guard_lvl_image.Visible = false;
                label_guard_image.Visible = false;
                pictureBox_guard.Visible = false;
            }

            if (GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].HasCroupier)
            {
                label_croupier_lvl_image.Visible = true;
                label_croupier_image.Visible = true;
                pictureBox_croupier.Visible = true;
                croupier_lvl.Text = GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Croupier.Level.ToString();
                label_croupier_lvl_image.Text = GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Croupier.Level.ToString();
                label_improve_croupier_price.Text = GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Croupier.ImprovePrice().ToString();
            }
            else
            {
                croupier_lvl.Text = "None";
                label_improve_croupier_price.Text = "";
                label_croupier_lvl_image.Visible = false;
                label_croupier_image.Visible = false;
                pictureBox_croupier.Visible = false;
            }

            if (GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Player.IsSwindler())
            {
                label_swindler_image.Text = "Swindler lvl";
            }
            else
            {
                label_swindler_image.Text = "Player lvl";
            }
            label_swindler_lvl_image.Text = GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Player.GetLevel().ToString();
            label_swindler.Text = GameFacade.GetInstance().Casino.CaughtSwindlers.ToString();
            building_lvl.Text = GameFacade.GetInstance().Casino.Building.Level.ToString();
            label_improve_building_price.Text = Casino.GetInstance().Building.ImprovePrice().ToString() + '$';
            label_space_price.Text = GameFacade.GetInstance().Casino.Building.SpacePrice().ToString() + '$';
            label_table_price.Text = GameFacade.GetInstance().Casino.Building.tablePrice().ToString() + '$';
            label_tables_count.Text = GameFacade.GetInstance().Casino.Building.Tables.ToString();
            button_hire_croupier.Enabled = CanHireCroupier();
            button_hire_guard.Enabled = CanHireGuard();
            button_buy_table.Enabled = CanBuyTable();
            button_buy_space.Enabled = CanBuySpace();
            button_improve_building.Enabled = CanImproveBuilding();
            button_improve_croupier.Enabled = CanImproveCroupier();
            button_improve_guard.Enabled = CanImproveGuard();
            label_day.Text = GameFacade.GetInstance().Casino.Day.ToString();
        }

        private void SetProfit(int profit)
        {
            label_profit.Text = profit.ToString() + '$';
            if (profit >= 0)
            {
                label_profit.Text = "+" + label_profit.Text;
                label_profit.ForeColor = Color.Lime;
            }
            else
            {
                label_profit.ForeColor = Color.Red;
            }
        }

        private bool CanHireCroupier()
        {
            if ((int)spinBox_table.Value == 0)
            {
                return false;
            }
            if (GameFacade.GetInstance().Casino.tables.Count == 0)
            {
                return false;
            }
            if (GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].HasCroupier)
            {
                return false;
            }
            if (GameFacade.GetInstance().Casino.Balance < (700 + GameFacade.GetInstance().Casino.tables.Count * 200))
            {
                return false;
            }
            return true;
        }
        private bool CanHireGuard()
        {
            if ((int)spinBox_table.Value == 0)
            {
                return false;
            }
            if (GameFacade.GetInstance().Casino.tables.Count == 0)
            {
                return false;
            }
            if (GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].HasGuard)
            {
                return false;
            }
            if (GameFacade.GetInstance().Casino.Balance < (500 + GameFacade.GetInstance().Casino.tables.Count * 100))
            {
                return false;
            }
            return true;
        }
        private bool CanBuyTable()
        {
            if (GameFacade.GetInstance().Casino.Balance < GameFacade.GetInstance().Casino.Building.tablePrice() || !GameFacade.GetInstance().Casino.Building.CanBuyTable())
            {
                return false;
            }
            return true;
        }
        private bool CanBuySpace()
        {
            if (GameFacade.GetInstance().Casino.Balance < GameFacade.GetInstance().Casino.Building.SpacePrice())
            {
                return false;
            }
            return true;
        }
        private bool CanImproveCroupier()
        {
            if ((int)spinBox_table.Value == 0)
            {
                return false;
            }
            if(!GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].HasCroupier)
            {
                return false;
            }
            if (GameFacade.GetInstance().Casino.Balance < GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Croupier.ImprovePrice())
            {
                return false;
            }
            return true;
        }
        private bool CanImproveGuard()
        {
            if ((int)spinBox_table.Value == 0)
            {
                return false;
            }
            if (!GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].HasGuard)
            {
                return false;
            }
            if (GameFacade.GetInstance().Casino.Balance < GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Guard.ImprovePrice())
            {
                return false;
            }
            return true;
        }
        private bool CanImproveBuilding()
        {
            if ((int)spinBox_table.Value == 0)
            {
                return false;
            }
            if (GameFacade.GetInstance().Casino.Balance < GameFacade.GetInstance().Casino.Building.ImprovePrice())
            {
                return false;
            }
            return true;
        }

        private void button_improve_croupier_Click(object sender, EventArgs e)
        {
            timer2.Interval = 70 + (GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Croupier.Level * 30);
            timer1.Enabled = false;
            timer2.Enabled = true;
            progressBar_improve.Visible = true;
            label_casino_work.Visible = true;
            label_improve_explain.Visible = true;
            label_improve_explain.Text = "we are training our croupier";
            button_improve_croupier.Enabled = false;
            button_improve_building.Enabled = false;
            button_improve_guard.Enabled = false;
        }

        private void button_improve_guard_Click(object sender, EventArgs e)
        {
            timer2.Interval = 70 + (GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Guard.Level * 30);
            timer1.Enabled = false;
            timer2.Enabled = true;
            progressBar_improve.Visible = true;
            label_casino_work.Visible = true;
            label_improve_explain.Visible = true;
            label_improve_explain.Text = "we are training our guard";
            button_improve_croupier.Enabled = false;
            button_improve_building.Enabled = false;
            button_improve_guard.Enabled = false;
        }

        private void button_improve_building_Click(object sender, EventArgs e)
        {
            timer2.Interval = 280 + ((GameFacade.GetInstance().Casino.Building.Level + GameFacade.GetInstance().Casino.Building.Space) * 30);
            timer1.Enabled = false;
            timer2.Enabled = true;
            progressBar_improve.Visible = true;
            label_casino_work.Visible = true;
            label_improve_explain.Visible = true;
            label_improve_explain.Text = "we are on reconstracting";
            button_improve_croupier.Enabled = false;
            button_improve_building.Enabled = false;
            button_improve_guard.Enabled = false;
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            if(progressBar_improve.Value >= 104)
            {
                timer2.Enabled = false;
                timer1.Enabled = true;
                if (label_improve_explain.Text == "we are training our croupier")
                {
                    GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Croupier.Improve();
                }
                else if (label_improve_explain.Text == "we are training our guard")
                {
                    GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Guard.Improve();
                }
                else if (label_improve_explain.Text == "we are on reconstracting")
                {
                    GameFacade.GetInstance().Casino.Building.Upgrade();
                }
                progressBar_improve.Visible = false;
                label_casino_work.Visible = false;
                label_improve_explain.Visible = false;
                label_improve_explain.Text = "";
                progressBar_improve.Value = 0;
                button_improve_croupier.Enabled = true;
                button_improve_building.Enabled = true;
                button_improve_guard.Enabled = true;
            }
            else
            {
                progressBar_improve.Value += 1;
            }
        }

        private void button_hire_croupier_Click(object sender, EventArgs e)
        {
            GameFacade.GetInstance().Casino.Balance -= (700 + Casino.GetInstance().tables.Count * 200);
            GameFacade.GetInstance().HireNewCroupier((int)spinBox_table.Value - 1);
        }

        private void button_hire_guard_Click(object sender, EventArgs e)
        {
            GameFacade.GetInstance().Casino.Balance -= (500 + Casino.GetInstance().tables.Count * 100);
            GameFacade.GetInstance().HireNewGuard((int)spinBox_table.Value - 1);
        }

        private void button_buy_table_Click(object sender, EventArgs e)
        {
            GameFacade.GetInstance().Casino.Building.BuyTable();
            GameFacade.GetInstance().Casino.tables.Add(new Table());
            if (GameFacade.GetInstance().Casino.Building.Tables == 1)
            {
                spinBox_table.Maximum = 1;
                spinBox_table.Minimum = 1;
                spinBox_table.Value = 1;
            }
            spinBox_table.Maximum = GameFacade.GetInstance().Casino.Building.Tables;
        }

        private void button_buy_space_Click(object sender, EventArgs e)
        {
            GameFacade.GetInstance().Casino.Building.BuySpace();
        }

        private void pictureBox9_Click(object sender, EventArgs e)
        {
            panel_game_tables.SendToBack();
        }

        private void spinBox_table_ValueChanged(object sender, EventArgs e)
        {
            if (spinBox_table.Value == 0)
            {
                return;
            }
            if(GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].HasGuard)
            {
                label_guard_lvl_image.Visible = true;
                label_guard_image.Visible = true;
                pictureBox_guard.Visible = true;
                guard_lvl.Text = GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Guard.Level.ToString();
                label_guard_lvl_image.Text = GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Guard.Level.ToString();
                label_improve_guard_price.Text = GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Guard.ImprovePrice().ToString();
            }
            else
            {
                guard_lvl.Text = "None";
                label_improve_guard_price.Text = "";
                label_guard_lvl_image.Visible = false;
                label_guard_image.Visible = false;
                pictureBox_guard.Visible = false;
            }

            if (GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].HasCroupier)
            {
                label_croupier_lvl_image.Visible = true;
                label_croupier_image.Visible = true;
                pictureBox_croupier.Visible = true;
                croupier_lvl.Text = GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Croupier.Level.ToString();
                label_croupier_lvl_image.Text = GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Croupier.Level.ToString();
                label_improve_croupier_price.Text = GameFacade.GetInstance().Casino.tables[(int)spinBox_table.Value - 1].Croupier.ImprovePrice().ToString();
            }
            else
            {
                croupier_lvl.Text = "None";
                label_improve_croupier_price.Text = "";
                label_croupier_lvl_image.Visible = false;
                label_croupier_image.Visible = false;
                pictureBox_croupier.Visible = false;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(spinBox_table.Value != 0)
            {
                OpenTable();
            }
        }
    }
}
