using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Fawrek.Editor
{
    class Skeleton : Object
    {
        public class Node
        {
            private string nodeId = "";

            public string NodeId
            {
                get { return nodeId; }
                set { nodeId = value; }
            }

            private List<Node> lstNode = new List<Node>();

            internal List<Node> LstNode
            {
                get { return lstNode; }
                set { lstNode = value; }
            }

            public Node()
            {
            }

            public Node(string _nodeId)
            {
                nodeId = _nodeId;
            }
        }

        public class NodePack : Object
        {
            private List<Node> lstNode = new List<Node>();

            public List<Node> LstNode
            {
                get { return lstNode; }
                set { lstNode = value; }
            }

            public NodePack()
            {
            }
        }

        private List<NodePack> lstNodePack = new List<NodePack>();

        public List<NodePack> LstNodePack
        {
            get { return lstNodePack; }
            set { lstNodePack = value; }
        }

        public Skeleton()
        {
        }
    }
}
