using System;
using System.Collections.Generic;

using System.Runtime.InteropServices;
using System.Text;


namespace demo
{
    class DllWrapper
    {
        [DllImport(@"YlzEcard\YlzEcard.dll", EntryPoint = "YlzEcard", CallingConvention = CallingConvention.StdCall)]
        public static extern int ReadCard(byte[] req,byte[] res);
        
    }
}
