#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxBullet.h"

#include "Player.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void drawHouse();

		ofPoint randomPoint(int min=0, int max=1000);

		void keyPressed(int key);
		void keyReleased(int key);
		
		ofxAssimpModelLoader model;

		ofLight light1;
		ofLight light2;
		ofVec3f scale;

		Player player;

		ofxBulletWorldRigid world;
		vector<ofxBulletCustomShape*> house;
		vector<ofVboMesh> houseMeshes;
		vector<ofMaterial> houseMaterials;
};
