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
    /// Logique d'interaction pour ClipListControl.xaml
    /// </summary>
    public partial class ClipListControl : UserControl
    {
        public ObservableCollection<Clip> LstClipObjects
        {
            get { return (ObservableCollection<Clip>)GetValue(LstObjectsProperty); }
            set { SetValue(LstObjectsProperty, value); }
        }
        public static readonly DependencyProperty LstObjectsProperty = DependencyProperty.Register("LstClipObjects", typeof(ObservableCollection<Clip>), typeof(ClipListControl), null);


        public ClipListControl()
        {
            InitializeComponent();
            LstClipObjects = new ObservableCollection<Clip>();
            DataContext = this;
            CharacterManager.GetInstance().Changed += BindLstObjects;
        }

        private void BindLstObjects()
        {
            LstClipObjects = CharacterManager.GetInstance().CurrentCharacter.LstClips;
        }

        private void PlayClip_Click(object sender, RoutedEventArgs e)
        {
            var character = ObjectManager.GetInstance().CurrentObject as CharacterModel;

            if(character == null)
            {
                return;
            }

            var frameworkElement = e.OriginalSource as FrameworkElement;
            var clip = frameworkElement.DataContext as Clip;

            if (null == clip)
            {
                return;
            }

            Fawrek.Wrapper.Wrapper.RunClipCrossfade(FawrekEngine.fawrekPtr, character.Id, clip.Id, (int)clip.BodyPart);
        }

        private void AddClip_Click(object sender, RoutedEventArgs e)
        {
            Clip clip = new Clip();
            CharacterManager.GetInstance().CurrentCharacter.LstClips.Add(clip);
        }

        private void RemoveClip_Click(object sender, RoutedEventArgs e)
        {
            var frameworkElement = e.OriginalSource as FrameworkElement;
            var clip = frameworkElement.DataContext as Clip;

            if (null == clip)
            {
                return;
            }

            LstClipObjects.Remove(clip);

            if (clip.GetType().Name == "Clip")
            {
                CharacterManager.GetInstance().CurrentCharacter.LstClips.Remove(clip);
            }
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
