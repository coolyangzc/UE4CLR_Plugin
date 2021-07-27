using System;
using System.Runtime.InteropServices;

namespace ManagedLib
{
    public static class Lib
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct LibArgs
        {
            public int IntNumber;
            public IntPtr Message;
            public long LongNumber;
        }

        public delegate float SquareDelegate(float x);
        public static float Square(float x)
        {
            return x * x;
        }

        public delegate LibArgs FunctionReturnStructDelegate(LibArgs libArgs);
        public static LibArgs FunctionReturnStruct(LibArgs libArgs)
        {
            LibArgs returnArgs = libArgs;
            returnArgs.IntNumber += 1;
            returnArgs.Message = Marshal.StringToHGlobalUni("Returned Message");
            returnArgs.LongNumber += 2;
            return returnArgs;
        }

       
    }
}
