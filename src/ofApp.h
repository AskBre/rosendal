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

		ofVec3f scale;

		Player player;
		ofCamera cam;

		ofxUDPManager udpSender;
		ofxUDPManager udpReceiver;
};
