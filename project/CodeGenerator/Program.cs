using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace CodeGenerator
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                Console.WriteLine("Error: No arguments supplied. Shutting down.\n");
                return;
            }

            string projectdir = "..\\..\\";
            string filename = args[0];

            // Init and load the configuration file
            if (ConfigFile.Get().Init(projectdir + "Config.ini"))
            {
                IFileGenerator HeaderGen = new GenerateHeader();
                IFileGenerator CPPGen = new GenerateCPP();

                // Generate the file data
                HeaderGen.Run(filename);
                CPPGen.Run(filename);

                Console.WriteLine("[CodeGenerator] Finished running; Shutting down.");
            }
            else
            {
                Console.WriteLine("[CodeGenerator] Error: Failed to initialize config file.");
            }
        }
    }
}
