using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
using Xceed.Wpf.Toolkit.PropertyGrid;

namespace Fawrek.Editor.UserControls
{
    /// <summary>
    /// Logique d'interaction pour ObjectListControl.xaml
    /// </summary>
    public partial class ObjectListControl : UserControl
    {

        public ObservableCollection<Model> LstModels
        {
            get { return (ObservableCollection<Model>)GetValue(LstModelsProperty); }
            set { SetValue(LstModelsProperty, value); }
        }
        public static readonly DependencyProperty LstModelsProperty = DependencyProperty.Register("LstModels", typeof(ObservableCollection<Model>), typeof(ObjectListControl), null);


        public ObjectListControl()
        {
            InitializeComponent();

            DataContext = this;
            SceneManager.GetInstance().Changed += BindLstModels;
        }

        private void BindLstModels()
        {
            LstModels = SceneManager.GetInstance().CurrentScene.LstModels;
        }

        private void AddModel_Click(object sender, RoutedEventArgs e)
        {
            Model model = new Model();
            LstModels.Add(model);
        }

        private void RemoveModel_Click(object sender, RoutedEventArgs e)
        {
            var frameworkElement = e.OriginalSource as FrameworkElement;
            var model = frameworkElement.DataContext as Model;

            if (null == model)
            {
                return;
            }

            LstModels.Remove(model);
        }

        private void LVSceneObjects_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            System.Windows.Controls.ListView lv = (System.Windows.Controls.ListView)sender;
            Object obj = lv.SelectedItem as Object;

            if (obj != null)
                ObjectManager.GetInstance().CurrentObject = obj;
        }
    }
}
