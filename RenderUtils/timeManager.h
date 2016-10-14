#pragma once



#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

class timer
{
	float curTime;
	float prevTime;
	float deltaTime;


public:


	bool init();
	bool step();
	bool term();

	//fixed to start of frame
	float getDeltaTime() const;
	//fixed to start of frame
	float getTime() const;

	//return the actual passage of time
	float getActualTime() const;
};




#endif
