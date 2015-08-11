using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Media.Media3D;
using System.Xml;

namespace Fawrek.Editor
{
    public class CharacterManager
    {
        private static CharacterManager characterManagerInstance;

        private Character currentCharacter = new Character();

        public Character CurrentCharacter
        {
            get { return currentCharacter; }
            set { currentCharacter = value; OnChange(); }
        }


        public delegate void CharacterChangedHandler();
        public event CharacterChangedHandler Changed;

        public delegate void CharacterClosedHandler();
        public event CharacterClosedHandler Closed;

        public CharacterManager()
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

        public static CharacterManager GetInstance()
        {
            if (characterManagerInstance != null)
            {
                return characterManagerInstance;
            }
            else
            {
                characterManagerInstance = new CharacterManager();
                return characterManagerInstance;
            }
        }

        public void OpenCharacter(string path)
        {
            if (!File.Exists(path))//new character ?
            {
                CreateCharacter(path);
            }
            else
            {
                Character character = new Character();

                character.Path = path;
                character.Name = Path.GetFileName(path);

                XmlReader reader = XmlReader.Create(path);

                while (reader.Read())
                {
                    if (reader.NodeType == XmlNodeType.Element && reader.Name == "CLIPS")
                    {
                        while (reader.NodeType != XmlNodeType.EndElement)
                        {
                            reader.Read();
                            if (reader.Name == "CLIP")
                            {
                                Clip clip = new Clip();

                                clip.Id = int.Parse(reader.GetAttribute(0));
                                clip.Name = reader.GetAttribute(1);

                                clip.StartTime = int.Parse(reader.GetAttribute(2).Replace('.', ','));
                                clip.EndTime = int.Parse(reader.GetAttribute(3).Replace('.', ','));
                                clip.Loop = bool.Parse(reader.GetAttribute(4));

                                string sBodyPart = reader.GetAttribute(5);
                                if(sBodyPart == Clip.BODYPART.lower_body.ToString())
                                {
                                    clip.BodyPart = Clip.BODYPART.lower_body;
                                }
                                else if (sBodyPart == Clip.BODYPART.upper_body.ToString())
                                {
                                    clip.BodyPart = Clip.BODYPART.upper_body;
                                }
                                else
                                {
                                    clip.BodyPart = Clip.BODYPART.full_body;
                                }
                                
                                clip.BaseSpeed = float.Parse(reader.GetAttribute(6).Replace('.', ','));

                                character.LstObjects.Add(clip);
                                character.LstClips.Add(clip);
                            }
                        }
                    }

                    if (reader.NodeType == XmlNodeType.Element && reader.Name == "SKELETON")
                    {
                        Skeleton skeleton = new Skeleton();

                        while (reader.NodeType != XmlNodeType.EndElement)
                        {
                            reader.Read();
                            if (reader.Name == "NODEPACK")
                            {
                                Skeleton.NodePack nodePack = new Skeleton.NodePack();

                                nodePack.Id = int.Parse(reader.GetAttribute(0));
                                nodePack.Name = reader.GetAttribute(1);

                                while (reader.NodeType != XmlNodeType.EndElement)
                                {
                                    reader.Read();
                                    if (reader.Name == "NODE")
                                    {
                                        Skeleton.Node node = new Skeleton.Node();

                                        node.NodeId = reader.GetAttribute("nodeId");

                                        ReadNode(node, reader);

                                        nodePack.LstNode.Add(node);
                                    }
                                }

                                character.LstObjects.Add(nodePack);
                                skeleton.LstNodePack.Add(nodePack);
                            }
                        }
                    }
                }

                reader.Close();

                CurrentCharacter = character;
            }
        }

        private void CreateCharacter(string path)
        {
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;

            XmlWriter writer = XmlWriter.Create(path, settings);

            writer.WriteStartDocument();
            writer.WriteComment("This file is automaticaly generated by the FawrekEngine. Do not edit it.");
            writer.WriteStartElement("CHARACTER");
            writer.WriteEndElement();
            writer.WriteEndDocument();

            writer.Flush();
            writer.Close();
        }

        public void SaveCharacter()
        {
            if (CurrentCharacter != null && string.IsNullOrEmpty(CurrentCharacter.Path))
            {
                Stream myStream;
                System.Windows.Forms.SaveFileDialog saveSceneDialog = new System.Windows.Forms.SaveFileDialog();

                saveSceneDialog.Filter = "xml files (*.xml)|*.xml|All files (*.*)|*.*";
                saveSceneDialog.FilterIndex = 2;
                saveSceneDialog.RestoreDirectory = true;

                if (saveSceneDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    CurrentCharacter.Path = saveSceneDialog.FileName;
                }
            }

            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;

            XmlWriter writer = XmlWriter.Create(CurrentCharacter.Path, settings);
            writer.WriteStartDocument();
            writer.WriteComment("This file is automaticaly generated by the FawrekEngine. Do not edit it.");

            writer.WriteStartElement("CHARACTER");

            writer.WriteStartElement("CLIPS");
            writer.WriteAttributeString("nb_clip", CurrentCharacter.LstClips.Count().ToString());
            foreach (Clip clip in CurrentCharacter.LstClips)
            {
                writer.WriteStartElement("CLIP");

                writer.WriteAttributeString("id", clip.Id.ToString());
                writer.WriteAttributeString("name", clip.Name);

                writer.WriteAttributeString("start_time", clip.StartTime.ToString());
                writer.WriteAttributeString("end_time", clip.EndTime.ToString());
                writer.WriteAttributeString("loop", clip.Loop.ToString().ToLower());
                writer.WriteAttributeString("body_part", clip.BodyPart.ToString());
                writer.WriteAttributeString("base_speed", clip.BaseSpeed.ToString());

                writer.WriteEndElement();
            }
            writer.WriteEndElement();

            writer.WriteStartElement("SKELETON");
            foreach (Skeleton.NodePack nodePack in CurrentCharacter.Skeleton.LstNodePack)
            {
                writer.WriteStartElement("NODEPACK");

                writer.WriteAttributeString("id", nodePack.Id.ToString());
                writer.WriteAttributeString("name", nodePack.Name.ToString());
                writer.WriteAttributeString("nb_node", nodePack.LstNode.Count().ToString());

                foreach (Skeleton.Node node in nodePack.LstNode)
                {
                    WriteNode(node,writer);
                }

                writer.WriteEndElement();
            }
            writer.WriteEndElement();

            writer.WriteEndDocument();
            writer.Flush();
            writer.Close();

        }

        public void CloseCharacter()
        {
            if (CurrentCharacter != null && !string.IsNullOrEmpty(CurrentCharacter.Path))
            {
                CurrentCharacter.LstClips.Clear();
                OnClose();
            }
        }

        private void WriteNode(Skeleton.Node _node, XmlWriter _writer)
        {
            _writer.WriteStartElement("NODE");

            _writer.WriteAttributeString("nodeId", _node.NodeId);

            foreach (Skeleton.Node node in _node.LstNode)
            {
                WriteNode(node, _writer);
            }

            _writer.WriteEndElement();
        }

        private void ReadNode(Skeleton.Node _parentNode, XmlReader _reader)
        {
            while (_reader.NodeType != XmlNodeType.EndElement)
            {
                _reader.Read();
                if (_reader.Name == "NODE")
                {
                    Skeleton.Node node = new Skeleton.Node();

                    node.NodeId = _reader.GetAttribute("nodeId");

                    ReadNode(node, _reader);

                    _parentNode.LstNode.Add(node);
                }
            }
        }
    }
}
