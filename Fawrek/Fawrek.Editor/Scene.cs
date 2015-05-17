using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;

namespace Fawrek.Editor
{
    public class Scene
    {
        private string name = "";

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        private string path = "";

        public string Path
        {
            get { return path; }
            set { path = value; }
        }

        private ObservableCollection<Model> lstModels = new ObservableCollection<Model>();

        internal ObservableCollection<Model> LstModels
        {
            get { return lstModels; }
            set { lstModels = value; }
        }

        public Scene()
        {
        }

    }
}
