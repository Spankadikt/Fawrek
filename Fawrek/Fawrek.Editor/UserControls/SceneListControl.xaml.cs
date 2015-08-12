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
    /// Logique d'interaction pour SceneListControl.xaml
    /// </summary>
    public partial class SceneListControl : UserControl
    {
        public ObservableCollection<Object> LstObjects
        {
            get { return (ObservableCollection<Object>)GetValue(LstObjectsProperty); }
            set { SetValue(LstObjectsProperty, value); }
        }
        public static readonly DependencyProperty LstObjectsProperty = DependencyProperty.Register("LstObjects", typeof(ObservableCollection<Object>), typeof(SceneListControl), null);


        public SceneListControl()
        {
            InitializeComponent();
            LstObjects = new ObservableCollection<Object>();
            DataContext = this;
            SceneManager.GetInstance().Changed += BindLstObjects;
        }

        private void BindLstObjects()
        {
            LstObjects = SceneManager.GetInstance().CurrentScene.LstObjects;
        }

        private void AddModel_Click(object sender, RoutedEventArgs e)
        {
            Model model = new Model();
            LstObjects.Add(model);
            SceneManager.GetInstance().CurrentScene.LstModels.Add(model);
        }

        private void AddCamera_Click(object sender, RoutedEventArgs e)
        {
            Camera camera = new Camera();
            LstObjects.Add(camera);
            SceneManager.GetInstance().CurrentScene.LstCameras.Add(camera);
        }

        private void AddLight_Click(object sender, RoutedEventArgs e)
        {
            Light light = new Light();
            LstObjects.Add(light);
            SceneManager.GetInstance().CurrentScene.LstLights.Add(light);
        }

        private void RemoveObject_Click(object sender, RoutedEventArgs e)
        {
            var frameworkElement = e.OriginalSource as FrameworkElement;
            var obj = frameworkElement.DataContext as Object;

            if (null == obj)
            {
                return;
            }

            LstObjects.Remove(obj);
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
