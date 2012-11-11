#ifndef _MLSCRIPTSYSTEM_
#define _MLSCRIPTSYSTEM_

#include "list.h"

class cScriptSystem
{
private:
	cList <HINSTANCE> hDLL;
	char dllErrString[256];
	int rPlayerID,curScript;
	void runDll(int id);
	int load(int id);
public:
	cScriptSystem();
	void freeAll();
	void run(int id,int index);
	void free(int id);
	void loadAll();
	int compile(int id);
	char *getError();
	int getPlayer();
	int getScript();
	void compileAll();
};

#endif