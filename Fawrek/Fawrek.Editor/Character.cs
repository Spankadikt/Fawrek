using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;

namespace Fawrek.Editor
{
    public class Character
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

        private List<Clip> lstClips = new List<Clip>();

        internal List<Clip> LstClips
        {
            get { return lstClips; }
            set { lstClips = value; }
        }

        private ObservableCollection<Object> lstObjects = new ObservableCollection<Object>();

        internal ObservableCollection<Object> LstObjects
        {
            get { return lstObjects; }
            set { lstObjects = value; }
        }

        private Skeleton skeleton = new Skeleton();

        internal Skeleton Skeleton
        {
            get { return skeleton; }
            set { skeleton = value; }
        }

        public Character()
        {
        }

    }
}
