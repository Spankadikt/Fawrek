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
            public static extern IntPtr FawrekCreate();

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "FawrekInit")]
            public static extern int FawrekInit(IntPtr value);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "FawrekRender")]
            public static extern void FawrekRender(IntPtr value);

            [DllImport(@"Fawrek.Engine.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "FawrekDelete")]
            public static extern void FawrekDelete(IntPtr value);
        }

        public static IntPtr RunFawrekCreate()
        {
            try
            {
                return DllHelper.FawrekCreate();
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
    }
}
