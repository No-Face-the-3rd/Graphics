
#include "gManager.h"


const int screenWidth = 1360, screenHeight = 768;
const char *name = "Meow";

void main()
{
	gManager manager(screenWidth, screenHeight, name);
	
	manager.init();

	while (manager.step())
	{
		manager.draw();
	}

	manager.term();
}



