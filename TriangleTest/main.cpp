

#include "crenderutils.h"
#include "window.h"

// This is in a develop branch!

void main()
{
	Window window;
	window.init();


	while (window.step());

	window.term();

	return;
}