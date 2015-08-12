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
    /// Logique d'interaction pour CharacterEditorControl.xaml
    /// </summary>
    public partial class CharacterEditorControl : UserControl
    {
        public CharacterEditorControl()
        {
            InitializeComponent();
        }

        private void LoadCharacter_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Forms.OpenFileDialog ofd = new System.Windows.Forms.OpenFileDialog();
            if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                string path = ofd.FileName;
                CharacterManager.GetInstance().OpenCharacter(path);
            }
        }

        private void SaveCharacter_Click(object sender, RoutedEventArgs e)
        {
            CharacterManager.GetInstance().SaveCharacter();
        }

        private void CloseCharacter_Click(object sender, RoutedEventArgs e)
        {
            CharacterManager.GetInstance().CloseCharacter();
        }
    }
}
