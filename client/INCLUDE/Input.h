#ifndef _INPUT_H_
#define _INPUT_H_

namespace Input
{
	enum eKey
	{
		// Unfilled enum of keys for supporting multiple input backends
		// for now this is unused since we only have SDL input atm
	};

	bool Init();
	void Shutdown();
	
	// Update the internal key arrays
	void Update();
	// Check if a key is pressed
	bool IsKeyUp(int key);
	bool IsKeyDown(int key);
	bool IsPressed(int key);
	// Mouse coordinates
	int MouseX();
	int MouseY();

	// These are some nasty string functions
	// (Sonic) These need to be removed some time in the future
	void SetString(const char *Text);
	char *GetString();
	void NullTerm();
	bool StringInput(int len);
	void ResetString();
}
#endif
