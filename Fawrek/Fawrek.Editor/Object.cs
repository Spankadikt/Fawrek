using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Media.Media3D;

namespace Fawrek.Editor
{
    public class Object
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
            set
            {
                translation = value;
                Fawrek.Wrapper.Wrapper.RunObjectTranslate(FawrekEngine.fawrekPtr, id, (float)translation.X, (float)translation.Y, (float)translation.Z);
            }
        }

        private Vector3D rotation = new Vector3D();

        public Vector3D Rotation
        {
            get { return rotation; }
            set
            {
                rotation = value;
                Fawrek.Wrapper.Wrapper.RunObjectRotate(FawrekEngine.fawrekPtr, id, (float)rotation.X, (float)rotation.Y, (float)rotation.Z);
            }
        }

        private Vector3D scale = new Vector3D();

        public Vector3D Scale
        {
            get { return scale; }
            set
            {
                scale = value;
                Fawrek.Wrapper.Wrapper.RunObjectScale(FawrekEngine.fawrekPtr, id, (float)scale.X, (float)scale.Y, (float)scale.Z);
            }
        }

        private bool isSelected = false;

        public bool IsSelected
        {
            get { return isSelected; }
            set { isSelected = value; }
        }

        public Object()
        {
        }
    }
}
