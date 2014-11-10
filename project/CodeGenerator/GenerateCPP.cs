using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator
{
    class GenerateCPP : FileGenerator
    {
        public override void Run(string filename)
        {
            FileContents = new List<string>();
            OutputPath = filename;

            Console.WriteLine("[CodeGenerator] Generating CPP data...");

            WriteIncludes();
            WriteClassDefinition();

            Console.WriteLine("[CodeGenerator] Writing CPP data to file...");

            // Write the data to the output file
            string path = ConfigFile.Get().GetString("CPPOutput") + "\\";
            string fullpath = path + OutputPath + ".cpp";
            if (Write(fullpath))
            {
                Console.WriteLine("[CodeGenerator] CPP file written successfully.");
            }
            else
            {
                Console.WriteLine("[CodeGenerator] Error: CPP file failed to write.");
            }
        }

        void WriteIncludes()
        {
            string deplist = "CPPDependencies";
            WriteIncludes(deplist);

            string header = "\"" + OutputPath + ".h\"";
            FileContents.Insert(1, "#include " + header);
            NewLine();
        }

        void WriteClassDefinition()
        {
            string cname = OutputPath;
            if (ConfigFile.Get().GetBool("PrefixClassName"))
            {
                cname = "C" + cname;
            }
            string func = "BOOL " + cname + "::" + "execute(CString &params)";

            AddLine(0, func);
            AddLine(0, "{");
            AddLine(1, Format.comment + " Decode Parameters");
            AddLine(1, "CStringList paramStrList;");
            AddLine(1, "CScriptParser::StringSplit(paramStrList, params, CString(' '));", true);
            AddLine(1, Format.comment + " Need n params for dimensions");
            AddLine(1, "const int numParams = 0;");
            AddLine(1, "if (paramStrList.GetCount() != numParams)");
            AddLine(1, "{");
            AddLine(2, "return FALSE;");
            AddLine(1, "}", true);
            AddLine(1, "return TRUE;");
            AddLine(0, "}");
        }
    }
}
