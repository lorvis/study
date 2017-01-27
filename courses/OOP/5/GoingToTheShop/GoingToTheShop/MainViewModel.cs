using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace GoingToTheShop
{
    public class ViewModelBase : INotifyPropertyChanged
    {
        #region Implementation of INotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            OnPropertyChanged(new PropertyChangedEventArgs(propertyName));
        }

        protected virtual void OnPropertyChanged(PropertyChangedEventArgs args)
        {
            var handler = PropertyChanged;
            if (handler != null)
                handler(this, args);
        }
        #endregion
    }

    public class DelegateCommand : ICommand
    {
        public delegate void ICommandOnExecute(object parameter);
        public delegate bool ICommandOnCanExecute(object parameter);

        private ICommandOnExecute _execute;
        private ICommandOnCanExecute _canExecute;

        public DelegateCommand(ICommandOnExecute onExecuteMethod, ICommandOnCanExecute onCanExecuteMethod)
        {
            _execute = onExecuteMethod;
            _canExecute = onCanExecuteMethod;
        }

        #region ICommand Members

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        public bool CanExecute(object parameter)
        {
            return _canExecute.Invoke(parameter);
        }

        public void Execute(object parameter)
        {
            _execute.Invoke(parameter);
        }

        #endregion
    }

    //----------------------------------------------------------------

    public class MainViewModel : ViewModelBase
    {
        private DelegateCommand exitCommand;

        #region Constructor

        public GoodsModel Goods { get; set; }
        public string GoodNameToAdd { get; set; }
        public int GoodCostToAdd { get; set; }
        public bool IsTransactionEnabled;
        public bool IsNameCorrect { get; set; }
        public bool IsCostCorrect { get; set; }
        public int SummaryCost { get; set; }
        public int Money { get; set; }
        public int CurrentID { get; set; }

        public void UpdateTransactionAbility()
        {
            //if (IsNameCorrect && IsCostCorrect)
            //    IsTransactionEnabled = "True";
            //else
            //    IsTransactionEnabled = "False";
            IsTransactionEnabled = IsNameCorrect && IsCostCorrect;
            CommandManager.InvalidateRequerySuggested();
        }


        public MainViewModel()
        {
            Goods = GoodsModel.Current;
            SummaryCost = 0;
            CurrentID = 0;
            Money = 10000;
            IsNameCorrect = false;
            IsCostCorrect = false;
            UpdateTransactionAbility();
        }

        #endregion

        public ICommand ExitCommand
        {
            get
            {
                if (exitCommand == null)
                {
                    exitCommand = new DelegateCommand(Exit, CanAddGoodToList);
                }
                return exitCommand;
            }
        }

        private void Exit(object parameter)
        {
            Application.Current.Shutdown();
        }


        public bool CanAddGoodToList(object parameter)
        {
            return IsTransactionEnabled;
            //return true;
        }

        private ICommand _AddGood;
        public ICommand AddGood
        {
            get
            {
                if (_AddGood == null)
                {
                    _AddGood = new DelegateCommand(AddGoodToList, CanAddGoodToList);
                }

                return _AddGood;
            }
        }

        public bool CanRemoveFromList(object parameter)
        {
            return true;
        }

        private ICommand _RemoveGood;
        public ICommand RemoveGood
        {
            get
            {
                if (_RemoveGood == null)
                {
                    _RemoveGood = new DelegateCommand(RemoveGoodFromList, CanRemoveFromList);
                }
                return _RemoveGood;
            }
        }

        public void AddGoodToList(object parameter)
        {

            GoodNameToAdd.Trim();

            StringBuilder SB = new StringBuilder();
            if (GoodNameToAdd == "")
            {
                SB.Remove(0, SB.Length);
                SB.Append("Write the name of product.");
                throw new ArgumentException(SB.ToString());
            }

            if (GoodCostToAdd < 0)
            {
                SB.Remove(0, SB.Length);
                SB.Append("Write valid cost.");
                throw new ArgumentException(SB.ToString());
            }

            if (GoodCostToAdd > Money)
            {
                return;
            }

                
            SB.Remove(0, SB.Length);
            SB.Append("Good ");
            SB.Append(GoodNameToAdd);
            SB.Append(" is added");

            Goods.AddGood(GoodNameToAdd,
                GoodCostToAdd, CurrentID);
            CurrentID++;
            SummaryCost += GoodCostToAdd;
            Money -= GoodCostToAdd;
        }

       public void RemoveGoodFromList(object parameter)
        {
            Good curr = (Good)Goods.Where(good => good.ID == (int)parameter);
            SummaryCost -= curr.Cost;
            Money += curr.Cost;
            Goods.RemoveGood((int)parameter);
        }
    }
}
