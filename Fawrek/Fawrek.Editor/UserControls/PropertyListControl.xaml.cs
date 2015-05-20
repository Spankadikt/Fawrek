using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Fawrek.Editor.UserControls
{
    /// <summary>
    /// Logique d'interaction pour PropertyListControl.xaml
    /// </summary>
    public partial class PropertyListControl : UserControl
    {
        public PropertyListControl()
        {
            InitializeComponent();

            DataContext = this;

            ObjectManager.GetInstance().Selected += new ObjectManager.ObjectSelectedHandler(BindOject);
            SceneManager.GetInstance().Closed += UnBindObject;
        }

        private void BindOject(Object obj)
        {
            ObjectPropertyGrid.SelectedObject = obj;
        }

        private void UnBindObject()
        {
            ObjectPropertyGrid.SelectedObject = null;
        }
    }
}
