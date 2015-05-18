using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Media.Media3D;

namespace Fawrek.Editor
{
    public class ModelProperty
    {
        public Model Model;

        public string ModelPropertyName
        {
            get { return ModelPropertyInfo.Name; }
        }

        public object ModelPropertyValue
        {
            get
            {
                return this.Model.GetType().GetProperty(ModelPropertyInfo.Name).GetValue(Model, null);
            }
            set
            {
                this.Model.GetType().GetProperty(ModelPropertyInfo.Name).SetValue(Model.GetType(), value, null);
            }
        }

        public PropertyInfo ModelPropertyInfo { get; set; }
    }

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
            name = "model";
        }

        public List<ModelProperty> Properties()
        {
            System.Type type = this.GetType();
            System.Reflection.PropertyInfo[] pi = type.GetProperties();

            List<ModelProperty> lstProperties = new List<ModelProperty>();

            foreach (PropertyInfo p in pi)
            {
                ModelProperty mp = new ModelProperty();
                mp.ModelPropertyInfo = p;
                mp.Model = this;
                lstProperties.Add(mp);
            }

            return lstProperties;
        }
    }
}
