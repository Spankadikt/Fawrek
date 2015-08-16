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

        private List<Model> lstModels = new List<Model>();

        public List<Model> LstModels
        {
            get { return lstModels; }
            set { lstModels = value; }
        }

        private List<CharacterModel> lstCharacterModels = new List<CharacterModel>();

        public List<CharacterModel> LstCharacterModels
        {
            get { return lstCharacterModels; }
            set { lstCharacterModels = value; }
        }

        private List<Camera> lstCameras = new List<Camera>();

        public List<Camera> LstCameras
        {
            get { return lstCameras; }
            set { lstCameras = value; }
        }

        private List<Light> lstLights = new List<Light>();

        public List<Light> LstLights
        {
            get { return lstLights; }
            set { lstLights = value; }
        }

        private ObservableCollection<Object> lstObjects = new ObservableCollection<Object>();

        internal ObservableCollection<Object> LstObjects
        {
            get { return lstObjects; }
            set { lstObjects = value; }
        }

        public Scene()
        {
        }

    }
}
