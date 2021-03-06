﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Fawrek.Editor
{
    public class Clip : Object
    {
        public enum BODYPART
        {
            full_body,
            upper_body,
            lower_body
        }

        private float startTime = 0.0f;

        public float StartTime
        {
            get { return startTime; }
            set
            {
                startTime = value;
            }
        }

        private float endTime = 0.0f;

        public float EndTime
        {
            get { return endTime; }
            set
            {
                endTime = value;
            }
        }

        private bool loop = false;

        public bool Loop
        {
            get { return loop; }
            set
            {
                loop = value;
            }
        }

        private BODYPART bodyPart = BODYPART.full_body;

        public BODYPART BodyPart
        {
            get { return bodyPart; }
            set
            {
                bodyPart = value;
            }
        }

        private float baseSpeed = 0.0f;

        public float BaseSpeed
        {
            get { return baseSpeed; }
            set
            {
                baseSpeed = value;
            }
        }

        public Clip()
        {
            Name = "clip";
            Id = CharacterManager.GetInstance().CurrentCharacter.LstClips.Count();
        }
    }
}
