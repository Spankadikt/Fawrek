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

        public Model()
        {
            Name = "model";
        }
    }
}
