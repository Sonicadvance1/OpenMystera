#include <stdio.h>
#include "utils.h"
#include "script_system.h"
#include "portdir.h"
#include "signal.h"

void ScriptSignalHandler(int Signal);

void cScriptSystem::runDll(int id)
{
//	if(id>=0 && id<hDLL.size())
//	{
//		void (*pFunc)();
//		pFunc = (void (*)())GetProcAddress(hDLL[id],"main");
//		if(pFunc != NULL)
//			pFunc();
//	}
    // Not yet implemented
    UNUSED(id);
}

int cScriptSystem::load(int id)
{
//	char temp[64];
//	sprintf(temp,"%d.dll",id);
//	hDLL.at(id) = LoadLibrary(temp);
//	return int(hDLL[id] != NULL);

    // Not yet implemented
    UNUSED(id);
    return false;
}

cScriptSystem::cScriptSystem()
{
    curScript=-1;
}

void cScriptSystem::freeAll()
{
    for(int i=0; i<hDLL.size(); i++)
        free(i);
}

void cScriptSystem::run(int id,int index)
{
//    printf("***slot %d running script %d\n",id,index);
    rPlayerID = index;
    curScript=id;
    runDll(id);
}

void cScriptSystem::free(int id)
{
    // Not yet implemented
    UNUSED(id);
//	FreeLibrary(hDLL[id]);
}

void cScriptSystem::loadAll()
{
    printf("Compiling of scripts not yet enabled\n");
    return;

    char dirname[64];
    strcpy(dirname,"serverdata/scripts");
    DIRT *dirt;
    int rc;
    int id;
    const char *entry;
    if ( (dirt = dirt_open(dirname, &rc)) == NULL )
    {
        fprintf(stderr, "can't open %s: %s\n", dirname, dirt_error(rc));
        return;
    }
    while ( (entry = dirt_next(dirt)) != NULL )
    {
        if(strstr(entry,".txt")!=0)
        {
            sscanf(entry,"%d.txt",&id);
            sprintf(dirname,"%d.dll",id);
            if(!fileExists(dirname))
            {
                printf("\rCreating %s...",dirname);
                if(!compile(id))
                    printf("\nError: %s\n",dllErrString);
            }
            load(id);
        }
    }
    printf("\n");
    dirt_close(dirt);
}

int cScriptSystem::compile(int id)
{
    char temp[64];
    sprintf(temp,"makedll.bat serverdata\\scripts\\%d.txt %d",id,id);
    system(temp);
    FILE *f=fopen("output.txt","r");
    if (!f)
        return false;
    fgets(dllErrString,256,f);
    fgets(dllErrString,256,f);
    fclose(f);
    if(strstr(dllErrString,"error")!=0)
        return 0;
    load(id);
    return 1;
}

char* cScriptSystem::getError()
{
    return dllErrString;
}

int cScriptSystem::getPlayer()
{
    return rPlayerID;
}

int cScriptSystem::getScript()
{
    return curScript;
}

void cScriptSystem::compileAll()
{
    printf("Compiling of scripts not yet enabled\n");
    return;
    freeAll();
    char dirname[64];
    strcpy(dirname,"serverdata/scripts");
    DIRT *dirt;
    int rc;
    int id;
    const char *entry;
    if ( (dirt = dirt_open(dirname, &rc)) == NULL )
    {
        fprintf(stderr, "can't open %s: %s\n", dirname, dirt_error(rc));
        return;
    }
    while ( (entry = dirt_next(dirt)) != NULL )
    {
        if(strstr(entry,".txt")!=0)
        {
            sscanf(entry,"%d.txt",&id);
            sprintf(dirname,"%d.dll",id);
            printf("\rCreating %s...",dirname);
            if(!compile(id))
                printf("\nError: %s\n",dllErrString);
            load(id);
        }
    }
    printf("\n");
    dirt_close(dirt);
}

