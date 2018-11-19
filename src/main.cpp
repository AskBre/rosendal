#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	/*
	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context
	*/

	ofGLESWindowSettings settings;
	settings.setGLESVersion(2); //we define the OpenGL version we want to use
	ofCreateWindow(settings);

	/*
	ofGLFWWindowSettings settings;
	settings.setGLVersion(3, 3);
	ofCreateWindow(settings);
	*/

	ofRunApp(new ofApp());
}
