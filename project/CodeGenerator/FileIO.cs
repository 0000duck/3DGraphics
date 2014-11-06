using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;

namespace CodeGenerator
{
    class FileIO
    {
        public static bool ReadFile(string path, List<string> contents)
        {
            bool rc = true;
            StreamReader reader = new StreamReader(path);

            try
            {
                while (reader.Peek() != -1)
                {
                    string line = reader.ReadLine();
                    contents.Add(line);
                }
            }
            catch
            {
                Console.WriteLine("[CodeGenerator] Error: Could not open file: " + path);
                rc = false;
            }

            reader.Close();
            return rc;
        }

        // Writes the data in the list to the file
        public static bool WriteFile(string path, List<string> contents)
        {
            // Check if the file already exists
            if (File.Exists(path))
            {
                // Prompt to overwrite the file
                //string fullpath = Path.GetFullPath(path);
                string msg = "File: " + path + " already exists\nWould you like to overwrite it?";
                if (MessageBox.Show(msg, "File Exists", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No)
                {
                    return false;
                }
            }

            // Write the data in contents to the file
            int i = 0;
            int contentsSize = contents.Count;
            StreamWriter writer = new StreamWriter(path);
            foreach (string line in contents)
            {
                ++i;
                if (i < contentsSize)
                {
                    writer.WriteLine(line);
                }
                else
                {
                    // Prevent a newline from being written on the last line
                    writer.Write(line);
                }
            }

            writer.Close();
            return true;
        }
    }
}
