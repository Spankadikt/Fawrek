using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Media.Media3D;

namespace Fawrek.Editor
{
    public class Model
    {
        private int id = -1;

        public int Id
        {
            get { return id; }
            set { id = value; }
        }

        private string name = "";

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        private Vector3D translation = new Vector3D();

        public Vector3D Translation
        {
            get { return translation; }
            set { translation = value; }
        }

        private Vector3D rotation = new Vector3D();

        public Vector3D Rotation
        {
            get { return rotation; }
            set { rotation = value; }
        }

        private Vector3D scale = new Vector3D();

        public Vector3D Scale
        {
            get { return scale; }
            set { scale = value; }
        }

        private string filename = "";

        public string Filename
        {
            get { return filename; }
            set { filename = value; }
        }

        private string animationFileName = "";

        public string AnimationFileName
        {
            get { return animationFileName; }
            set { animationFileName = value; }
        }

        public Model()
        {
        }
    }
}
