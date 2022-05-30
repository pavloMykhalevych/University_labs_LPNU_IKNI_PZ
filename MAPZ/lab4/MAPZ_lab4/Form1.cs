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
            Casino.NewGame();
            timer3.Enabled = true;
            timer1.Enabled = true;
        }

        private void button_exit_Click(object sender, EventArgs e)
        {
            MainMenu.GetInstance().Exit();
        }

        public void CallMessage(string mes)
        {
            MessageBox.Show(mes, "Cool info!");
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
            Casino.GetInstance().PassDay();
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            label_balance.Text = Casino.GetInstance().Balance.ToString() + '$';
            SetProfit(Casino.GetInstance().Profit);
            label_croupier_count.Text = Casino.GetInstance().Croupiers.Count.ToString();
            label_croupier_hire.Text = (700 + Casino.GetInstance().Croupiers.Count * 200).ToString() + '$';
            spinBox_croupier.Maximum = Casino.GetInstance().Croupiers.Count;
            label_guards_count.Text = Casino.GetInstance().Guards.Count.ToString();
            label_guard_hire.Text = (500 + Casino.GetInstance().Guards.Count * 100).ToString() + '$';
            spinBox_guard.Maximum = Casino.GetInstance().Guards.Count;
            label_swindler.Text = Casino.GetInstance().CaughtSwindlers.ToString();
            building_lvl.Text = Casino.GetInstance().Building.Level.ToString();
            label_improve_building_price.Text = Casino.GetInstance().Building.ImprovePrice().ToString() + '$';
            label_space_price.Text = Casino.GetInstance().Building.SpacePrice().ToString() + '$';
            label_table_price.Text = Casino.GetInstance().Building.tablePrice().ToString() + '$';
            label_tables_count.Text = Casino.GetInstance().Building.Tables.ToString();
            button_hire_croupier.Enabled = CanHireCroupier();
            button_hire_guard.Enabled = CanHireGuard();
            button_buy_table.Enabled = CanBuyTable();
            button_buy_space.Enabled = CanBuySpace();
            button_improve_building.Enabled = CanImproveBuilding();
            button_improve_croupier.Enabled = CanImproveCroupier();
            button_improve_guard.Enabled = CanImproveGuard();
            label_day.Text = Casino.GetInstance().Day.ToString();

            if (spinBox_croupier.Value != 0 && Casino.GetInstance().Croupiers.Count > (int)spinBox_croupier.Value - 1)
            {
                croupier_lvl.Text = Casino.GetInstance().Croupiers[(int)spinBox_croupier.Value - 1].Level.ToString();
                label_improve_croupier_price.Text = Casino.GetInstance().Croupiers[(int)spinBox_croupier.Value - 1].ImprovePrice().ToString();
            }

            if (spinBox_guard.Value != 0 && Casino.GetInstance().Guards.Count > (int)spinBox_guard.Value - 1)
            {
                guard_lvl.Text = Casino.GetInstance().Guards[(int)spinBox_guard.Value - 1].Level.ToString();
                label_improve_guard_price.Text = Casino.GetInstance().Guards[(int)spinBox_guard.Value - 1].ImprovePrice().ToString();
            }
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
            if (Casino.GetInstance().Balance < (700 + Casino.GetInstance().Croupiers.Count * 200))
            {
                return false;
            }
            return true;
        }
        private bool CanHireGuard()
        {
            if (Casino.GetInstance().Balance < (500 + Casino.GetInstance().Guards.Count * 100))
            {
                return false;
            }
            return true;
        }
        private bool CanBuyTable()
        {
            if(Casino.GetInstance().Balance < Casino.GetInstance().Building.tablePrice() || !Casino.GetInstance().Building.CanBuyTable())
            {
                return false;
            }
            return true;
        }
        private bool CanBuySpace()
        {
            if (Casino.GetInstance().Balance < Casino.GetInstance().Building.SpacePrice())
            {
                return false;
            }
            return true;
        }
        private bool CanImproveCroupier()
        {
            if (spinBox_croupier.Value == 0)
            {
                return false;
            }
            if (Casino.GetInstance().Balance < Casino.GetInstance().Croupiers[(int)spinBox_croupier.Value - 1].ImprovePrice())
            {
                return false;
            }
            return true;
        }
        private bool CanImproveGuard()
        {
            if (spinBox_guard.Value == 0)
            {
                return false;
            }
            if (Casino.GetInstance().Balance < Casino.GetInstance().Guards[(int)spinBox_guard.Value - 1].ImprovePrice())
            {
                return false;
            }
            return true;
        }
        private bool CanImproveBuilding()
        {
            if (Casino.GetInstance().Balance < Casino.GetInstance().Building.ImprovePrice())
            {
                return false;
            }
            return true;
        }

        private void spinBox_croupier_ValueChanged(object sender, EventArgs e)
        {
            if(spinBox_croupier.Value == 0)
            {
                return;
            }
            if (Casino.GetInstance().Croupiers.Count > (int)spinBox_croupier.Value - 1)
            {
                croupier_lvl.Text = Casino.GetInstance().Croupiers[(int)spinBox_croupier.Value - 1].Level.ToString();
                label_improve_croupier_price.Text = Casino.GetInstance().Croupiers[(int)spinBox_croupier.Value - 1].ImprovePrice().ToString();
            }
        }

        private void spinBox_guard_ValueChanged(object sender, EventArgs e)
        {
            if (spinBox_guard.Value == 0)
            {
                return;
            }
            if (Casino.GetInstance().Guards.Count > (int)spinBox_guard.Value - 1)
            {
                guard_lvl.Text = Casino.GetInstance().Guards[(int)spinBox_guard.Value - 1].Level.ToString();
                label_improve_guard_price.Text = Casino.GetInstance().Guards[(int)spinBox_guard.Value - 1].ImprovePrice().ToString();
            }
        }

        private void button_improve_croupier_Click(object sender, EventArgs e)
        {
            timer2.Interval = 70 + (Casino.GetInstance().Croupiers[(int)spinBox_croupier.Value - 1].Level * 30);
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
            timer2.Interval = 70 + (Casino.GetInstance().Guards[(int)spinBox_guard.Value - 1].Level * 30);
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
            timer2.Interval = 280 + ((Casino.GetInstance().Building.Level + Casino.GetInstance().Building.Space) * 30);
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
                    Casino.GetInstance().Croupiers[(int)spinBox_croupier.Value - 1].Improve();
                }
                else if (label_improve_explain.Text == "we are training our guard")
                {
                    Casino.GetInstance().Guards[(int)spinBox_guard.Value - 1].Improve();
                }
                else if (label_improve_explain.Text == "we are on reconstracting")
                {
                    Casino.GetInstance().Building.Upgrade();
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
            if (Casino.GetInstance().Croupiers.Count == 0)
            {
                spinBox_croupier.Maximum = 1;
                spinBox_croupier.Minimum = 1;
            }
            Casino.GetInstance().Balance -= (700 + Casino.GetInstance().Croupiers.Count * 200);
            Casino.GetInstance().HireNewCroupier();
        }

        private void button_hire_guard_Click(object sender, EventArgs e)
        {
            if(Casino.GetInstance().Guards.Count == 0)
            {
                spinBox_guard.Maximum = 1;
                spinBox_guard.Minimum = 1;
            }
            Casino.GetInstance().Balance -= (500 + Casino.GetInstance().Guards.Count * 100);
            Casino.GetInstance().HireNewGuard();
        }

        private void button_buy_table_Click(object sender, EventArgs e)
        {
            Casino.GetInstance().Building.BuyTable();
        }

        private void button_buy_space_Click(object sender, EventArgs e)
        {
            Casino.GetInstance().Building.BuySpace();
        }
    }
}
