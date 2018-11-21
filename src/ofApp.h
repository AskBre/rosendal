#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxBullet.h"
#include "ofxNetwork.h"

#include "Player.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void setupNetwork();

		void update();
		void updateNetwork();

		void draw();
		void drawHouse();

		glm::vec3 randomPoint(int min=0, int max=1000);

		void keyPressed(int key);
		void keyReleased(int key);

		ofxAssimpModelLoader model;

		ofLight light1;
		ofLight light2;
		ofLight light3;
		ofVec3f scale;

		Player player;
		Player player2;

		ofxBulletWorldRigid world;
		vector<ofxBulletCustomShape*> house;
		vector<ofVboMesh> houseMeshes;
		vector<ofMaterial> houseMaterials;

		ofxUDPManager udpSender;
		ofxUDPManager udpReceiver;
};
