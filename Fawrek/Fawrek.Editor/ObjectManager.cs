using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Fawrek.Editor
{
    class ObjectManager
    {
        private static ObjectManager objectManagerInstance;

        private Object currentObject = new Object();

        internal Object CurrentObject
        {
            get { return currentObject; }
            set
            {
                currentObject = value;
                currentObject.IsSelected = true;
                OnSelect();
            }
        }

        public delegate void ObjectSelectedHandler(Object obj);
        public event ObjectSelectedHandler Selected;

        public ObjectManager()
        {
        }

        public void OnSelect()
        {
            if (Selected != null)
                Selected(CurrentObject);
        }

        public static ObjectManager GetInstance()
        {
            if (objectManagerInstance != null)
            {
                return objectManagerInstance;
            }
            else
            {
                objectManagerInstance = new ObjectManager();
                return objectManagerInstance;
            }
        }
    }
}
