using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace GoingToTheShop
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            DataContext = new MainViewModel();
        }

        private void textBox1_TextChanged(object sender, TextChangedEventArgs e)
        {
            MainViewModel model = (MainViewModel)DataContext;
           if (textBox1.Text == "")
            {
                model.IsNameCorrect = false;
            }
           else
            {
                model.IsNameCorrect = true;
            }

            model.UpdateTransactionAbility();
            button.IsEnabled = model.IsTransactionEnabled;
        }

        private void textBox2_TextChanged(object sender, TextChangedEventArgs e)
        {
            int cost = -1;
            MainViewModel model = (MainViewModel)DataContext;

            try
            {
                cost = Convert.ToInt32(textBox2.Text);
            }
            catch
            {
                model.IsCostCorrect = false;
            }
            finally
            {
                if (cost < 0 || cost > model.Money)
                {
                    model.IsCostCorrect = false;
                }
                else
                {
                    model.IsCostCorrect = true;
                }
            }
            model.UpdateTransactionAbility();
            button.IsEnabled = model.IsTransactionEnabled;
        }

        private void textBox1_TextChanged_1(object sender, TextChangedEventArgs e)
        {

        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            Dispatcher.BeginInvoke(new ThreadStart(delegate ()
            {
                textBox.Text = ((MainViewModel)DataContext).Money.ToString();
                textBlock.Text = ((MainViewModel)DataContext).SummaryCost.ToString();
            }), null);
        }
    }
}
