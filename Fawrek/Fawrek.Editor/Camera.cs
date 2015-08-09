using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Media.Media3D;

namespace Fawrek.Editor
{
    public class Camera : Object
    {
        private Vector3D translation = new Vector3D();

        public Vector3D Translation
        {
            get { return translation; }
            set
            {
                translation = value;
                Fawrek.Wrapper.Wrapper.RunObjectSetTranslate(FawrekEngine.fawrekPtr, id, (float)translation.X, (float)translation.Y, (float)translation.Z);
            }
        }

        private Vector3D target = new Vector3D();

        public Vector3D Target
        {
            get { return target; }
            set
            {
                target = value;
                Fawrek.Wrapper.Wrapper.RunCameraSetTarget(FawrekEngine.fawrekPtr, id, (float)target.X, (float)target.Y, (float)target.Z);
            }
        }

        private Vector3D up = new Vector3D();

        public Vector3D Up
        {
            get { return up; }
            set
            {
                up = value;
                Fawrek.Wrapper.Wrapper.RunCameraSetUp(FawrekEngine.fawrekPtr, id, (float)up.X, (float)up.Y, (float)up.Z);
            }
        }

        private float fov = 0.0f;

        public float FOV
        {
            get { return fov; }
            set
            {
                fov = value;
                Fawrek.Wrapper.Wrapper.RunCameraSetFOV(FawrekEngine.fawrekPtr, id, fov);
            }
        }

        private float nearZ = 0.0f;

        public float NearZ
        {
            get { return nearZ; }
            set
            {
                nearZ = value;
                Fawrek.Wrapper.Wrapper.RunCameraSetNearZ(FawrekEngine.fawrekPtr, id, nearZ);
            }
        }

        private float farZ = 0.0f;

        public float FarZ
        {
            get { return farZ; }
            set
            {
                farZ = value;
                Fawrek.Wrapper.Wrapper.RunCameraSetFarZ(FawrekEngine.fawrekPtr, id, farZ);
            }
        }

        private float aspectRatioWidth = 0.0f;

        public float AspectRatioWidth
        {
            get { return aspectRatioWidth; }
            set
            {
                aspectRatioWidth = value;
                Fawrek.Wrapper.Wrapper.RunCameraSetAspectRatio(FawrekEngine.fawrekPtr, id, aspectRatioWidth / aspectRatioHeight);
            }
        }

        private float aspectRatioHeight = 0.0f;

        public float AspectRatioHeight
        {
            get { return aspectRatioHeight; }
            set
            {
                aspectRatioHeight = value;
                Fawrek.Wrapper.Wrapper.RunCameraSetAspectRatio(FawrekEngine.fawrekPtr, id, aspectRatioWidth / aspectRatioHeight);
            }
        }

        public Camera()
        {
            Name = "camera";
        }
    }
}
