using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator
{
    class GenerateHeader : FileGenerator
    {
        public override void Run(string filename)
        {
            FileContents = new List<string>();
            OutputPath = filename;

            Console.WriteLine("[CodeGenerator] Generating header data...");

            WriteIncludes();
            WriteClassDeclaration();
            WriteHeaderGuard();

            Console.WriteLine("[CodeGenerator] Writing header data to file...");

            // Write the data to the output file
            string path = ConfigFile.Get().GetString("HeaderOutput") + "\\";
            string fullpath = path + OutputPath + ".h";
            if (Write(fullpath))
            {
                Console.WriteLine("[CodeGenerator] Header file written successfully.");
            }
            else
            {
                Console.WriteLine("[CodeGenerator] Error: Header file failed to write.");
            }
        }

        // Create the pre-processor header guards
        void WriteHeaderGuard()
        {
            string headermacro = null;
            string format = ConfigFile.Get().GetString("HeaderGuardFormat");

            // Check for a flag indicator
            if (format.Contains('<'))
            {
                int beg = format.IndexOf('<');
                int end = format.IndexOf('>');
                headermacro = format.Substring(0, beg);

                // Parse the flag
                string flag = format.Substring(beg+1, end-beg-1);
                if (flag.CompareTo("filename") == 0)
                {
                    // "file" = filename
                    headermacro = headermacro + OutputPath.ToUpper();
                }
                headermacro = headermacro + format.Substring(end + 1, format.Length - (end+1));
            }
            else
            {
                // Default macro definition
                headermacro = "INCLUDED_" + OutputPath.ToUpper() + "_H";
            }

            string endif = "#endif";
            string hguardIF = "#ifndef " + headermacro;
            string hguardDEF = "#define " + headermacro;

            // Insert the header guard macro definitions at the beginning of the file
            FileContents.Insert(0, hguardIF);
            FileContents.Insert(1, hguardDEF + Format.endl);

            // Close the preprocessor definition at the end of the file
            NewLine();
            FileContents.Add(endif + " " + "//" + hguardIF);
        }

        void WriteIncludes()
        {
            string deplist = "HeaderDependencies";
            WriteIncludes(deplist);
            NewLine();
        }

        void WriteClassDeclaration()
        {
            string cname = OutputPath;
            if (ConfigFile.Get().GetBool("PrefixClassName"))
            {
                cname = "C" + cname;
            }

            string parent = "CCmdCommand";
            string ctor = cname + "(void) {}";
            string dtor = "~" + ctor;
            string func = "BOOL execute(CString &params);";

            AddLine(0, "class " + cname + " : public " + parent);
            AddLine(0, "{");
            AddLine(0, "public:");
            AddLine(1, ctor);
            AddLine(1, dtor, true);
            AddLine(0, "public:");
            AddLine(1, func, true);
            AddLine(0, "};");
        }
    }
}
