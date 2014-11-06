using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace CodeGenerator
{
    abstract class FileGenerator : IFileGenerator
    {
        protected List<string> FileContents;
        protected string OutputPath;


        public abstract void Run(string filename);


        protected bool Write(string fullpath)
        {
            return FileIO.WriteFile(fullpath, FileContents);
        }

        //protected void AddToProject(string file, string projectpath, string cmp)
        //{
        //    List<string> projFile = new List<string>();
        //    FileIO.ReadFile(projectpath, projFile);
        //
        //    string add = Format.tab + Format.tab + "<ClCompile Include=\"..\\..\\source\\" + file + "\" />";
        //    int size = projFile.Count;
        //    for (int i=0; i < size; ++i)
        //    {
        //        string line = projFile[i];
        //        if (line.Contains(cmp))
        //        {
        //            projFile.Insert(i, add);
        //            break;
        //        }
        //    }
        //    FileIO.WriteFile(projectpath, projFile);
        //}

        protected void WriteIncludes(string deplist)
        {
            List<string> includes = ConfigFile.Get().GetList(deplist);
            foreach (string incl in includes)
            {
                AddLine(0, "#include " + incl);
            }
        }

        protected void AddLine(int tabindex, string text, bool newline = false)
        {
            string t = null;
            for (int i = 0; i < tabindex; ++i)
            {
                t = t + Format.tab;
            }

            t = t + text;
            if (newline)
            {
                t = t + Format.endl;
            }
            FileContents.Add(t);
        }

        protected void NewLine()
        {
            FileContents.Add(null);
        }
    }
}
