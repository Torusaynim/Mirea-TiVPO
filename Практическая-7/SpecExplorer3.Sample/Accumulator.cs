using System;
using System.Collections.Generic;
using System.Text;

namespace SpecExplorer3.Sample
{
    /// <summary>
    /// A dummy implementation that doesn't conform to the model (testing should fail).
    /// </summary>
    public class Accumulator
    {
        private static int count = 0;
        public static void Add(int i)
        {
            if (i > 0)
                count += i;
        }

        public static int ReadAndReset()
        {
            int ret = count;
            count = 0;
            return ret;
        }

        public static void Multy(int i)
        {
            if ((count >= i) & (i > 0))
            {
                count *= i;
            }
        }
    }
}
