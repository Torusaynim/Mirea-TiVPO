using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

using Microsoft.Modeling;

namespace SpecExplorer3
{
    static class AccumulatorModelProgram
    {
        static int accumulator;

        [Rule(Action = "Add(x)")]
        static void AddRule(int x)
        {
            Condition.IsTrue(x > 0);
            accumulator += x;
        }

        [Rule(Action = "ReadAndReset()/result")]
        static int ReadAndResetRule()
        {
            Condition.IsTrue(accumulator > 0);
            int oldValue = accumulator;
            accumulator = 0;
            return oldValue;
        }

        [Rule(Action = "Multy(x)")]
        static void MultyRule(int x)
        {
            Condition.IsTrue((accumulator >= 0) &(x > 0));
            accumulator *= x;
        }

    }
}
