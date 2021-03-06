#pragma once

#include "ofMain.h"
#include "ofxBullet.h"
#include "ofxGamepadHandler.h"
#include "ofxAssimpModelLoader.h"
#include "playerNum.h"

class Player : public ofBaseApp{
	public:
		void setup(ofxBulletWorldRigid &_world, bool _isLocal);
		void update();

		void draw();
		void drawRibbon();
		void drawBullets();

		void moveTo(glm::vec3 position);
		void rotateTo(glm::vec3 orientation);
		void shootBullet();

		bool isShootingBullet = false;

		void keyPressed(int key);
		void keyReleased(int key);

		ofxBulletWorldRigid* world;
		ofNode node;
		ofCamera cam;

		ofSoundPlayer bulletSound;

		glm::vec3 getPosition(){return node.getPosition();};


		ofxAssimpModelLoader ship;

	private:
		void axisChanged(ofxGamepadAxisEvent &e);
		void buttonPressed(ofxGamepadButtonEvent &e);
		void buttonReleased(ofxGamepadButtonEvent &e);

		void updatePos();
		void drawPos();

		void fillRibbon();

		bool isLocal;

		glm::vec3 targetPos;
		glm::vec3 targetOrient;

		glm::vec3 movForce;
		glm::vec3 panForce;
		glm::vec3 movAmt;
		glm::vec3 panAmt;

		vector<bool> keys;

		ofMesh ribbon;
//		ofMaterial ribbonMaterial;
		ofFloatColor ribbonColor;
		ofShader shader;

		deque<unique_ptr<ofxBulletRigidBody>> bullets;
		bool isBulletReady = true;
};
