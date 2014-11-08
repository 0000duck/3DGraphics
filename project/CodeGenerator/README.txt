Installation
======================================================================

1. Open the visual studio project
2. Right click on the project in the solution explorer and click "Build"
The executable "CodeGenerator.exe" will output to the bin directory.
You can move the executable wherever you want, but the Config file must always be one directory above it.


Configuration
======================================================================

File: CodeGeneratorConfig.ini

Legend
------
* - indicates the value must be set (non-optional)
[] - required commands
{} - optional commands
<> - user specified value
| - separates valid inputs
" - if a command is surrounded in quotes, it must have them. 

Options Overview
----------------

*HeaderOutput: ["<drive\fully\qualified\path\>"]
	full path to output directory for the header.
	Must have a trailing backslash.

*CPPOutput: ["<drive\fully\qualified\path\>"]
	full path to output directory for the cpp.
	Must have a trailing backslash.

AuthorName: ["<name>"]
	Currently unused.

PrefixClassName: [true | false]
	true -> class names are prefixed with a 'C' (filenames and header guards unaffected)
	false -> Class names are not prefixed.

Default Header Dependencies: [List <"foo.h">]
	Files included when the header is generated.
	List format requires a new line after each entry.
	Only include the filename and extension.

Default CPP Dependencies: [List <"foo.cpp">]
	Files included when the cpp is generated.
	List format requires a new line after each entry.
	Only include the filename and extension.


Usage
======================================================================

CodeGenerator.exe [<class name>]
	example: CmdTest
	No quotes or file extension.

Once it finishes, right click on your project and select "Add existing item".
Navigate to the directory you specified in the config file, and select the files.

It is reccommended to add a toolbar option in Visual Studio to launch this.
TOOLS -> External Tools
Add
Title: <AddCommandClass>
Command: <full\path\to\CodeGenerator.exe> (use the explorer button (...) and manually open it).
Arguments: None (maybe just put "Cmd" so you don't have to type it every time).
Initial directory: $(SolutionDir)