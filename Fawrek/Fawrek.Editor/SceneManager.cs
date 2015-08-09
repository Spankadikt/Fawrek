using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Media.Media3D;
using System.Xml;

namespace Fawrek.Editor
{
    public class SceneManager
    {
        private static SceneManager sceneManagerInstance;

        private Scene currentScene = new Scene();

        public Scene CurrentScene
        {
            get { return currentScene; }
            set { currentScene = value; OnChange(); }
        }


        public delegate void SceneChangedHandler();
        public event SceneChangedHandler Changed;

        public delegate void SceneClosedHandler();
        public event SceneClosedHandler Closed;

        public SceneManager()
        {
        }


        private void OnChange()
        {
            if (Changed != null)
                Changed();
        }

        private void OnClose()
        {
            if (Closed != null)
                Closed();
        }

        public static SceneManager GetInstance()
        {
            if (sceneManagerInstance != null)
            {
                return sceneManagerInstance;
            }
            else
            {
                sceneManagerInstance = new SceneManager();
                return sceneManagerInstance;
            }
        }

        public void OpenScene(string path)
        {
            if (!File.Exists(path))//new scene ?
            {
                CreateScene(path);
            }
            else
            {
                Scene scene = new Scene();

                scene.Path = path;
                scene.Name = Path.GetFileName(path);

                XmlReader reader = XmlReader.Create(path);

                while (reader.Read())
                {
                    if (reader.NodeType == XmlNodeType.Element && reader.Name == "LIGHTS")
                    {
                        while (reader.NodeType != XmlNodeType.EndElement)
                        {
                            reader.Read();
                            if (reader.Name == "LIGHT_DIRECTIONAL")
                            {
                                Light light = new Light();

                                light.Id = int.Parse(reader.GetAttribute(0));
                                light.Name = reader.GetAttribute(1);

                                string[] direction = reader.GetAttribute(2).Split(',').ToArray();
                                light.Direction = new Vector3D(double.Parse(direction[0]), double.Parse(direction[1]), double.Parse(direction[2]));

                                string[] color = reader.GetAttribute(3).Split(',').ToArray();
                                light.Color = new Vector3D(double.Parse(color[0]), double.Parse(color[1]), double.Parse(color[2]));

                                light.AmbiantIntensity = float.Parse(reader.GetAttribute(4).Replace('.', ','));
                                light.DiffuseIntensity = float.Parse(reader.GetAttribute(5).Replace('.', ','));

                                scene.LstObjects.Add(light);
                            }
                        }
                    }

                    if (reader.NodeType == XmlNodeType.Element && reader.Name == "CAMERAS")
                    {
                        while (reader.NodeType != XmlNodeType.EndElement)
                        {
                            reader.Read();
                            if (reader.Name == "CAMERA")
                            {
                                Camera camera = new Camera();

                                camera.Id = int.Parse(reader.GetAttribute(0));
                                camera.Name = reader.GetAttribute(1);

                                string[] translation = reader.GetAttribute(2).Split(',').ToArray();
                                camera.Translation = new Vector3D(double.Parse(translation[0]), double.Parse(translation[1]), double.Parse(translation[2]));

                                string[] target = reader.GetAttribute(3).Split(',').ToArray();
                                camera.Target = new Vector3D(double.Parse(target[0]), double.Parse(target[1]), double.Parse(target[2]));

                                string[] up = reader.GetAttribute(4).Split(',').ToArray();
                                camera.Up = new Vector3D(double.Parse(up[0].Replace('.', ',')), double.Parse(up[1].Replace('.', ',')), double.Parse(up[2].Replace('.', ',')));

                                camera.FOV = float.Parse(reader.GetAttribute(5).Replace('.', ','));
                                camera.NearZ = float.Parse(reader.GetAttribute(6).Replace('.', ','));
                                camera.FarZ = float.Parse(reader.GetAttribute(7).Replace('.', ','));
                                camera.AspectRatioWidth = float.Parse(reader.GetAttribute(8).Replace('.', ','));
                                camera.AspectRatioHeight = float.Parse(reader.GetAttribute(9).Replace('.', ','));

                                scene.LstObjects.Add(camera);
                            }
                        }
                    }

                    if (reader.NodeType == XmlNodeType.Element && reader.Name == "MODELS")
                    {
                        while (reader.NodeType != XmlNodeType.EndElement)
                        {
                            reader.Read();
                            if (reader.Name == "MODEL")
                            {
                                Model model = new Model();
                                
                                model.Id = int.Parse(reader.GetAttribute(0));
                                model.Name = reader.GetAttribute(1);
                                
                                string[] translation = reader.GetAttribute(2).Split(',').ToArray();
                                model.Translation = new Vector3D(double.Parse(translation[0]),double.Parse(translation[1]),double.Parse(translation[2]));

                                string[] rotation = reader.GetAttribute(3).Split(',').ToArray();
                                model.Rotation = new Vector3D(double.Parse(rotation[0]), double.Parse(rotation[1]), double.Parse(rotation[2]));

                                string[] scale = reader.GetAttribute(4).Split(',').ToArray();
                                model.Scale = new Vector3D(double.Parse(scale[0].Replace('.', ',')), double.Parse(scale[1].Replace('.', ',')), double.Parse(scale[2].Replace('.', ',')));

                                model.Filename = reader.GetAttribute(5);
                                model.AnimationFileName = reader.GetAttribute(6);

                                scene.LstObjects.Add(model);
                            }
                        }
                    }
                }

                reader.Close();

                CurrentScene = scene;
                FawrekEngine.InitFawrekPtr(path);
            }
        }

        private void CreateScene(string path)
        {
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;

            XmlWriter writer = XmlWriter.Create(path, settings);

            writer.WriteStartDocument();
            writer.WriteComment("This file is automaticaly generated by the FawrekEngine. Do not edit it.");
            writer.WriteStartElement("MODELS");
            writer.WriteEndElement();
            writer.WriteEndDocument();

            writer.Flush();
            writer.Close();
        }

        public void SaveScene()
        {
            if (CurrentScene != null && string.IsNullOrEmpty(CurrentScene.Path))
            {
                Stream myStream;
                System.Windows.Forms.SaveFileDialog saveSceneDialog = new System.Windows.Forms.SaveFileDialog();

                saveSceneDialog.Filter = "xml files (*.xml)|*.xml|All files (*.*)|*.*";
                saveSceneDialog.FilterIndex = 2;
                saveSceneDialog.RestoreDirectory = true;

                if (saveSceneDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    CurrentScene.Path = saveSceneDialog.FileName;
                }
            }

            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;

            XmlWriter writer = XmlWriter.Create(CurrentScene.Path, settings);
            writer.WriteStartDocument();
            writer.WriteComment("This file is automaticaly generated by the FawrekEngine. Do not edit it.");

            writer.WriteStartElement("OBJECTS");

            writer.WriteStartElement("LIGHTS");
            foreach (Light light in CurrentScene.LstLights)
            {
                writer.WriteStartElement("LIGHT_DIRECTIONAL");

                writer.WriteAttributeString("id", light.Id.ToString());
                writer.WriteAttributeString("name", light.Name);

                string direction = light.Direction.X.ToString() + "," + light.Direction.Y.ToString() + "," + light.Direction.Z.ToString();
                writer.WriteAttributeString("direction", direction);

                string color = light.Color.X.ToString() + "," + light.Color.Y.ToString() + "," + light.Color.Z.ToString();
                writer.WriteAttributeString("color", color);

                writer.WriteAttributeString("ambiantintensity", light.AmbiantIntensity.ToString());
                writer.WriteAttributeString("diffuseintensity", light.DiffuseIntensity.ToString());

                writer.WriteEndElement();   
            }
            writer.WriteEndElement();

            writer.WriteStartElement("CAMERAS");
            foreach (Camera cam in CurrentScene.LstCameras)
            {
                writer.WriteStartElement("CAMERA");

                writer.WriteAttributeString("id", cam.Id.ToString());
                writer.WriteAttributeString("name", cam.Name);

                string translation = cam.Translation.X.ToString() + "," + cam.Translation.Y.ToString() + "," + cam.Translation.Z.ToString();
                writer.WriteAttributeString("translation", translation);

                string target = cam.Target.X.ToString() + "," + cam.Target.Y.ToString() + "," + cam.Target.Z.ToString();
                writer.WriteAttributeString("target", target);

                string up = cam.Up.X.ToString() + "," + cam.Up.Y.ToString() + "," + cam.Up.Z.ToString();
                writer.WriteAttributeString("up", up);

                writer.WriteAttributeString("fov", cam.FOV.ToString());
                writer.WriteAttributeString("nearz", cam.NearZ.ToString());
                writer.WriteAttributeString("farz", cam.FarZ.ToString());
                writer.WriteAttributeString("aspectratiowidth", cam.AspectRatioWidth.ToString());
                writer.WriteAttributeString("aspectratioheight", cam.AspectRatioHeight.ToString());

                writer.WriteEndElement();
            }
            writer.WriteEndElement();  
                
            writer.WriteStartElement("MODELS");
            foreach (Model model in CurrentScene.LstModels)
            {
                writer.WriteStartElement("MODEL");

                writer.WriteAttributeString("id", model.Id.ToString());
                writer.WriteAttributeString("name", model.Name);

                string translation = model.Translation.X.ToString() + "," + model.Translation.Y.ToString() + "," + model.Translation.Z.ToString();
                writer.WriteAttributeString("translation", translation);

                string rotation = model.Rotation.X.ToString() + "," + model.Rotation.Y.ToString() + "," + model.Rotation.Z.ToString();
                writer.WriteAttributeString("rotation", rotation);

                string scale = model.Scale.X.ToString() + "," + model.Scale.Y.ToString() + "," + model.Scale.Z.ToString();
                writer.WriteAttributeString("scale", scale);

                writer.WriteAttributeString("filename", model.Filename);
                writer.WriteAttributeString("animationfilename", model.AnimationFileName);

                writer.WriteEndElement();
            }
            writer.WriteEndElement();

            writer.WriteEndDocument();
            writer.Flush();
            writer.Close();
            
        }

        public void CloseScene()
        {
            if (CurrentScene != null && !string.IsNullOrEmpty(CurrentScene.Path))
            {
                FawrekEngine.DisposeFawrekPtr();
                CurrentScene.LstModels.Clear();
                OnClose();
            }
        }
    }
}
