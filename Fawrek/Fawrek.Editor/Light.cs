using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Media.Media3D;

namespace Fawrek.Editor
{
    public class Light : Object
    {
        private Vector3D direction = new Vector3D();

        public Vector3D Direction
        {
            get { return direction; }
            set
            {
                direction = value;
                Fawrek.Wrapper.Wrapper.RunLightSetDirection(FawrekEngine.fawrekPtr, id, (float)direction.X, (float)direction.Y, (float)direction.Z);
            }
        }

        private Vector3D color = new Vector3D();

        public Vector3D Color
        {
            get { return color; }
            set
            {
                color = value;
                Fawrek.Wrapper.Wrapper.RunLightSetColor(FawrekEngine.fawrekPtr, id, (float)color.X, (float)color.Y, (float)color.Z);
            }
        }

        private float ambiantIntensity = 0.0f;

        public float AmbiantIntensity
        {
            get { return ambiantIntensity; }
            set
            {
                ambiantIntensity = value;
                Fawrek.Wrapper.Wrapper.RunLightSetAmbiantIntensity(FawrekEngine.fawrekPtr, id, ambiantIntensity);
            }
        }

        private float diffuseIntensity = 0.0f;

        public float DiffuseIntensity
        {
            get { return diffuseIntensity; }
            set
            {
                diffuseIntensity = value;
                Fawrek.Wrapper.Wrapper.RunLightSetDiffuseIntensity(FawrekEngine.fawrekPtr, id, diffuseIntensity);
            }
        }

        public Light()
        {
            Name = "light";
        }
    }
}
