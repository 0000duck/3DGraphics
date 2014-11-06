using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator
{
    interface IFileGenerator
    {
        void Run(string filename);
    }
}
