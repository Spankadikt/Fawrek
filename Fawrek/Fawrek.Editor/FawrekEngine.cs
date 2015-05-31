using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Fawrek.Editor
{
    public static class FawrekEngine
    {
        public static IntPtr fawrekPtr;

        public static void InitFawrekPtr()
        {
            fawrekPtr = Fawrek.Wrapper.Wrapper.RunFawrekCreate();
            int initResult = Fawrek.Wrapper.Wrapper.RunFawrekInit(fawrekPtr);
        }

        public static void DisposeFawrekPtr()
        {
            Fawrek.Wrapper.Wrapper.RunFawrekDelete(FawrekEngine.fawrekPtr);
            FawrekEngine.fawrekPtr = IntPtr.Zero;
        }
    }
}
