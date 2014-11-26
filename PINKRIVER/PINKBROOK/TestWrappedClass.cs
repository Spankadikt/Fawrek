using System;
using System.Runtime.InteropServices;

namespace TestCSharpLibrary
{
    public class TestWrappedClass
    {
        // From c++ Dll (unmanaged)
        [DllImport("PinkSpring")]
        public static extern float[] GetTest(float a);
    }
}