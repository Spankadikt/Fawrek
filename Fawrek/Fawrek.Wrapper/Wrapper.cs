using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Fawrek.Wrapper
{
    public class Wrapper
    {
        public static class DllHelper
        {

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "FawrekCreate")]
            public static extern IntPtr FawrekCreate(string scenePath);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "FawrekInit")]
            public static extern int FawrekInit(IntPtr value);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "FawrekRender")]
            public static extern void FawrekRender(IntPtr value);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "FawrekDelete")]
            public static extern void FawrekDelete(IntPtr value);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "ObjectSetRotate")]
            public static extern void ObjectSetRotate(IntPtr value, int id, float x, float y, float z);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "ObjectSetTranslate")]
            public static extern void ObjectSetTranslate(IntPtr value, int id, float x, float y, float z);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "ObjectSetScale")]
            public static extern void ObjectSetScale(IntPtr value, int id, float x, float y, float z);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "CameraSetTarget")]
            public static extern void CameraSetTarget(IntPtr value, int id, float x, float y, float z);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "CameraSetUp")]
            public static extern void CameraSetUp(IntPtr value, int id, float x, float y, float z);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "CameraSetFOV")]
            public static extern void CameraSetFOV(IntPtr value, int id, float fov);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "CameraSetNearZ")]
            public static extern void CameraSetNearZ(IntPtr value, int id, float nearZ);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "CameraSetFarZ")]
            public static extern void CameraSetFarZ(IntPtr value, int id, float farZ);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "CameraSetAspectRatio")]
            public static extern void CameraSetAspectRatio(IntPtr value, int id, float aspectRatio);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "LightSetDirection")]
            public static extern void LightSetDirection(IntPtr value, int id, float x, float y, float z);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "LightSetColor")]
            public static extern void LightSetColor(IntPtr value, int id, float r, float g, float b);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "LightSetAmbiantIntensity")]
            public static extern void LightSetAmbiantIntensity(IntPtr value, int id, float ambiantIntensity);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "LightSetDiffuseIntensity")]
            public static extern void LightSetDiffuseIntensity(IntPtr value, int id, float diffuseIntensity);

        }

        public static IntPtr RunFawrekCreate(string scenePath)
        {
            try
            {
                return DllHelper.FawrekCreate(scenePath);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return IntPtr.Zero;
            }
        }

        public static int RunFawrekInit(IntPtr value)
        {
            try
            {
                return DllHelper.FawrekInit(value);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return 2;
            }
        }

        public static void RunFawrekRender(IntPtr value)
        {
            try
            {
                DllHelper.FawrekRender(value);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunFawrekDelete(IntPtr value)
        {
            try
            {
                DllHelper.FawrekDelete(value);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunObjectSetRotate(IntPtr value, int id, float x, float y, float z)
        {
            try
            {
                DllHelper.ObjectSetRotate(value,id,x,y,z);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunObjectSetTranslate(IntPtr value, int id, float x, float y, float z)
        {
            try
            {
                DllHelper.ObjectSetTranslate(value, id, x, y, z);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunObjectSetScale(IntPtr value, int id, float x, float y, float z)
        {
            try
            {
                DllHelper.ObjectSetScale(value, id, x, y, z);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunCameraSetTarget(IntPtr value, int id, float x, float y, float z)
        {
            try
            {
                DllHelper.CameraSetTarget(value, id, x, y, z);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunCameraSetUp(IntPtr value, int id, float x, float y, float z)
        {
            try
            {
                DllHelper.CameraSetUp(value, id, x, y, z);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunCameraSetFOV(IntPtr value, int id, float fov)
        {
            try
            {
                DllHelper.CameraSetFOV(value, id, fov);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunCameraSetNearZ(IntPtr value, int id, float nearZ)
        {
            try
            {
                DllHelper.CameraSetNearZ(value, id, nearZ);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunCameraSetFarZ(IntPtr value, int id, float farZ)
        {
            try
            {
                DllHelper.CameraSetFarZ(value, id, farZ);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunCameraSetAspectRatio(IntPtr value, int id, float aspectRatio)
        {
            try
            {
                DllHelper.CameraSetAspectRatio(value, id, aspectRatio);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunLightSetDirection(IntPtr value, int id, float x, float y, float z)
        {
            try
            {
                DllHelper.LightSetDirection(value, id, x, y , z);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunLightSetColor(IntPtr value, int id, float r, float g, float b)
        {
            try
            {
                DllHelper.LightSetColor(value, id, r, g, b);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunLightSetAmbiantIntensity(IntPtr value, int id, float ambiantIntensity)
        {
            try
            {
                DllHelper.LightSetAmbiantIntensity(value, id, ambiantIntensity);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void RunLightSetDiffuseIntensity(IntPtr value, int id, float diffuseIntensity)
        {
            try
            {
                DllHelper.LightSetDiffuseIntensity(value, id, diffuseIntensity);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}
