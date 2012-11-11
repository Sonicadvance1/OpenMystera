
#include <SDL/SDL_mixer.h>

int music=1,sound=1;

struct WaveFile
{
	Mix_Chunk *pSound;
	int Play(bool loop);
	void Stop();
	WaveFile(){pSound=0;}
	int Load(char *szFileName);
	~WaveFile();
};

int WaveFile::Load(char *szFileName)
{
	FILE *t=fopen(szFileName,"r");//test file
	if(t)fclose(t);
	else return 0;
    pSound = Mix_LoadWAV(szFileName);
	if(pSound)
	{
		Mix_VolumeChunk(pSound, 64);
		return 1;
	}
	return 0;
}

WaveFile::~WaveFile()
{
	Mix_FreeChunk(pSound);
	pSound=0;
}

int WaveFile::Play(bool loop=false)
{
	if(sound)
		Mix_PlayChannel(-1, pSound, 0);	
	return 1;
}

void WaveFile::Stop()
{
}

