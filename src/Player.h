#pragma once

#include "ofMain.h"

class Player : public ofBaseApp{
	public:
		void setup();
		void update();

		void keyPressed(int key);
		void keyReleased(int key);

		void drawRibbon();

		ofCamera cam;

		void setPosition(int x=0, int y=0, int z=0);
		ofPoint getPosition(){return cam.getPosition();};
	private:

		void updateCam();
		void drawCamPos();

		void fillRibbon();

		ofPoint camForce;
		ofPoint panForce;

		vector<bool> keys;

		ofMesh ribbon;
		ofMaterial ribbonMaterial;
};
