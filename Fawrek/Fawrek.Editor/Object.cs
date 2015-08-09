using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Media.Media3D;

namespace Fawrek.Editor
{
    public class Object
    {
        protected int id = -1;

        public int Id
        {
            get { return id; }
            set { id = value; }
        }

        protected string name = "";

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        protected bool isSelected = false;

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
