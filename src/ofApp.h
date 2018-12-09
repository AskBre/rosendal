#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxNetwork.h"

#include "Player.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void setupNetwork();

		void update();
		void updateNetwork();

		void draw();

		ofxAssimpModelLoader model;

		ofLight light1;
		ofLight light2;

		Player player1;
		Player player2;
		ofCamera cam;

		ofxUDPManager udpReceiver1;
		ofxUDPManager udpReceiver2;
};
