#pragma once

#include "Main.h"
#include "BLondon.h"
#include "BRender.h"


class testApp : public ofBaseApp
{
public:
	testApp();

	virtual void setup();
	virtual void update();
	virtual void draw();
	virtual void exit();

public:
	BLondon		mLondon;		//	simulator!
	BRender		mRender;		//	renderer of the simulator!
};

