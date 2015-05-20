using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Fawrek.Editor
{
    public class Object
    {
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
