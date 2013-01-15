#include "testApp.h"


testApp::testApp() :
	mRender		( mLondon )
{
}



void testApp::setup()
{

}

void testApp::update()
{
	mLondon.Update();
}

void testApp::draw()
{
	mRender.Render();
}

void testApp::exit()
{
	//	hack here, clean there
	mRender.~BRender();
}
