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
        public SceneEditorControl()
        {
            InitializeComponent();
        }

        private void LoadScene_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Forms.OpenFileDialog ofd = new System.Windows.Forms.OpenFileDialog();
            if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                string path = ofd.FileName;
                SceneManager.GetInstance().OpenScene(path);

            }
        }

        private void SaveScene_Click(object sender, RoutedEventArgs e)
        {
            SceneManager.GetInstance().SaveScene();
        }

        private void CloseScene_Click(object sender, RoutedEventArgs e)
        {
            SceneManager.GetInstance().CloseScene();
        }
    }
}
