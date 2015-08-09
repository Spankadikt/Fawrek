using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Media.Media3D;

namespace Fawrek.Editor
{
    public class Model : Object
    {
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

        private Vector3D translation = new Vector3D();

        public Vector3D Translation
        {
            get { return translation; }
            set
            {
                translation = value;
                Fawrek.Wrapper.Wrapper.RunObjectSetTranslate(FawrekEngine.fawrekPtr, id, (float)translation.X, (float)translation.Y, (float)translation.Z);
            }
        }

        private Vector3D rotation = new Vector3D();

        public Vector3D Rotation
        {
            get { return rotation; }
            set
            {
                rotation = value;
                Fawrek.Wrapper.Wrapper.RunObjectSetRotate(FawrekEngine.fawrekPtr, id, (float)rotation.X, (float)rotation.Y, (float)rotation.Z);
            }
        }

        private Vector3D scale = new Vector3D();

        public Vector3D Scale
        {
            get { return scale; }
            set
            {
                scale = value;
                Fawrek.Wrapper.Wrapper.RunObjectSetScale(FawrekEngine.fawrekPtr, id, (float)scale.X, (float)scale.Y, (float)scale.Z);
            }
        }

        public Model()
        {
            Name = "model";
        }
    }
}
