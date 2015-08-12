using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Fawrek.Editor
{
    public static class FawrekEngine
    {
        public static IntPtr fawrekPtr;

        public static void InitFawrekScenePtr(string scenePath)
        {
            fawrekPtr = Fawrek.Wrapper.Wrapper.RunFawrekCreate(scenePath);
            int initResult = Fawrek.Wrapper.Wrapper.RunFawrekInit(fawrekPtr);
        }

        public static void DisposeFawrekScenePtr()
        {
            Fawrek.Wrapper.Wrapper.RunFawrekDelete(FawrekEngine.fawrekPtr);
            FawrekEngine.fawrekPtr = IntPtr.Zero;
        }
    }
}
