#include "Main.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( )
{

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 600,400, OF_WINDOW);			// <-------- setup the GL context

	//	core window/global setup
	window.setWindowPosition( 800, 200 );
	ofSetVerticalSync(true);
	ofEnableSmoothing(); 

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
