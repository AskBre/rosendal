#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxBullet.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void updateCam();
		void exportPly(ofxAssimpModelLoader &model);
		ofMesh makeMesh(ofxAssimpModelLoader &model);
		void drawCamPos();
		ofPoint randomPoint(int min=0, int max=1000);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxAssimpModelLoader model;
		ofCamera cam;
		ofLight light;
		ofPoint camForce;
		ofPoint panForce;;
		ofPoint prevMouse;
		ofVec3f scale;
		vector<bool> keys;

		ofxBulletWorldRigid world;
		ofxBulletBox ground;
		ofxBulletSphere* sphere;
		vector<ofxBulletCustomShape*> house;
};
