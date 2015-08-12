using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Fawrek.Editor
{
    class CharacterModel : Model
    {

        private string animationFileName = "";

        public string AnimationFileName
        {
            get { return animationFileName; }
            set { animationFileName = value; }
        }

        public CharacterModel()
        {
        }
    }
}
