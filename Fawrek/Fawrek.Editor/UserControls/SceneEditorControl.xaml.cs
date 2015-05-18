using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Fawrek.Editor.UserControls
{
    /// <summary>
    /// Logique d'interaction pour SceneEditorControl.xaml
    /// </summary>
    public partial class SceneEditorControl : System.Windows.Controls.UserControl
    {
        SceneManager SM = new SceneManager();

        public ObservableCollection<Model> LstModels
        {
            get { return (ObservableCollection<Model>)GetValue(LstModelsProperty); }
            set { SetValue(LstModelsProperty, value); }
        }
        public static readonly DependencyProperty LstModelsProperty = DependencyProperty.Register("LstModels", typeof(ObservableCollection<Model>), typeof(SceneEditorControl), null);

        public SceneEditorControl()
        {
            InitializeComponent();
        }

        private void LoadScene_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                string path = ofd.FileName;
                SM.OpenScene(path);

                LstModels = SM.CurrentScene.LstModels;
            }
        }

        private void SaveScene_Click(object sender, RoutedEventArgs e)
        {
            SM.SaveScene();
        }

        private void CloseScene_Click(object sender, RoutedEventArgs e)
        {
            SM.CloseScene();
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
            var model = lv.SelectedItem as Model;
            
            if(model != null)
                LVProperties.ItemsSource = model.Properties();
        }
    }
}
