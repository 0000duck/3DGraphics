#pragma once

#include <map>
#include "CmdCommand.h"

class CScriptParser
{
public:
	CScriptParser(void);
	~CScriptParser(void);

public:
	// List of commands to run
	typedef struct
	{
		CString keyword;
		CString params;
	} CommandLine;

public:
	static void StringSplit( CStringList &result, CString &inputString, CString &splitter );

	template <typename T>
	static void ToArray(CStringList& list, const int numparams, T* arr);

public:
	CCmdCommand *CommandLookup( CString &cmd );
	void ParseScript( CString &script );
	void ExecuteScript();

private:
	std::map<CString, CCmdCommand *> m_CommandDictionary;
	CList<CommandLine> m_CommandLines;
};

template <typename T>
void CScriptParser::ToArray(CStringList& list, const int numparams, T* arr)
{
	POSITION coord = list.GetHeadPosition();
	for (int i = 0; i < numparams; i++)
	{
		CString paramStr = list.GetNext(coord);
		arr[i] = (float)(wcstod(paramStr, NULL));
	}
}