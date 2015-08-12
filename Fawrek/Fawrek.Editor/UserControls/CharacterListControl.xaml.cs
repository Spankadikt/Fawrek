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
    /// Logique d'interaction pour CharacterListControl.xaml
    /// </summary>
    public partial class CharacterListControl : UserControl
    {
        public ObservableCollection<Object> LstCharacterObjects
        {
            get { return (ObservableCollection<Object>)GetValue(LstObjectsProperty); }
            set { SetValue(LstObjectsProperty, value); }
        }
        public static readonly DependencyProperty LstObjectsProperty = DependencyProperty.Register("LstCharacterObjects", typeof(ObservableCollection<Object>), typeof(CharacterListControl), null);


        public CharacterListControl()
        {
            InitializeComponent();
            LstCharacterObjects = new ObservableCollection<Object>();
            DataContext = this;
            CharacterManager.GetInstance().Changed += BindLstObjects;
        }

        private void BindLstObjects()
        {
            LstCharacterObjects = CharacterManager.GetInstance().CurrentCharacter.LstObjects;
        }


        private void AddClip_Click(object sender, RoutedEventArgs e)
        {
            Clip clip = new Clip();
            LstCharacterObjects.Add(clip);
            CharacterManager.GetInstance().CurrentCharacter.LstClips.Add(clip);
        }

        private void AddNodePack_Click(object sender, RoutedEventArgs e)
        {
            Skeleton.NodePack nodePack = new Skeleton.NodePack();
            LstCharacterObjects.Add(nodePack);
            CharacterManager.GetInstance().CurrentCharacter.Skeleton.LstNodePack.Add(nodePack);
        }

        private void RemoveObject_Click(object sender, RoutedEventArgs e)
        {
            var frameworkElement = e.OriginalSource as FrameworkElement;
            var obj = frameworkElement.DataContext as Object;

            if (null == obj)
            {
                return;
            }

            LstCharacterObjects.Remove(obj);
        }

        private void LVCharacterObjects_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            System.Windows.Controls.ListView lv = (System.Windows.Controls.ListView)sender;
            Object obj = lv.SelectedItem as Object;

            if (obj != null)
                ObjectManager.GetInstance().CurrentObject = obj;
        }
    }
}
