using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace CodeGenerator
{
    class ConfigFile
    {
        private static ConfigFile Instance;
        private string ConfigPath;
        private bool Initialized;

        private Dictionary<string, string> StringTable;
        private Dictionary<string, bool> BoolTable;
        private Dictionary<string, List<string>> ListTable;

        private ConfigFile()
        {
            StringTable = new Dictionary<string, string>();
            BoolTable = new Dictionary<string, bool>();
            ListTable = new Dictionary<string, List<string>>();

            Initialized = false;
        }

        public static ConfigFile Get()
        {
            if (Instance == null)
            {
                Instance = new ConfigFile();
            }
            return Instance;
        }

        public bool Init(string configPath)
        {
            ConfigPath = configPath;
            Initialized = ReadConfig(ConfigPath);

            return Initialized;
        }

        // Public accessor for config settings
        public string GetString(string key)
        {
            return StringTable[key];
        }

        public bool GetBool(string key)
        {
            return BoolTable[key];
        }

        public List<string> GetList(string key)
        {
            return ListTable[key];
        }

        // Load the configuration settings into the dictionary
        bool ReadConfig(string filename)
        {
            List<string> fcontents = new List<string>();
            if (!FileIO.ReadFile(filename, fcontents))
            {
                return false;
            }

            int size = fcontents.Count;
            for (int i = 0; i < size; ++i)
            {
                string line = fcontents[i];

                // Ignore newlines and comments
                if (line.Length > 0 && line[0] != '[')
                {
                    // Parse for list syntax
                    if (line.StartsWith("_List"))
                    {
                        i = AddList(fcontents, i);
                    }
                    else
                    {
                        string[] vals = line.Split('=');
                        AddEntry(vals[0], vals[1]);
                    }
                }
            }
            return true;
        }

        void AddEntry(string key, string val)
        {
            char[] trimlist = { '\t', '\n' };
            val = val.Trim(trimlist);

            if (val.Length > 0)
            {
                if (val[0] == '"')
                {
                    val = val.Trim('"');
                    StringTable.Add(key, val);
                }
                else if (val.ToLower().CompareTo("true") == 0)
                {
                    BoolTable.Add(key, true);
                }
                else if (val.ToLower().CompareTo("false") == 0)
                {
                    BoolTable.Add(key, false);
                }
            }
        }

        int AddList(List<string> list, int index)
        {
            int i = index;
            string line = list[i];
            int size = list.Count;

            int beg = line.IndexOf(':') + 1;
            int end = line.LastIndexOf(' ') - beg;
            string listname = line.Substring(beg, end);

            // Initialize the sublist
            ListTable.Add(listname, new List<string>());

            line = list[++i];
            while (!line.Contains('}') && i < size)
            {
                line = line.TrimStart('\t');
                ListTable[listname].Add(line);
                line = list[++i];
            }
            return i;
        }
    }
}
