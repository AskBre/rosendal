#pragma once

#include "ofMain.h"

class Player : public ofBaseApp{
	public:
		void setup();
		void update();

		void keyPressed(int key);
		void keyReleased(int key);

		ofCamera cam;

		void setPosition(int x=0, int y=0, int z=0);
	private:

		void updateCam();
		void drawCamPos();

		ofPoint camForce;
		ofPoint panForce;

		vector<bool> keys;
};
