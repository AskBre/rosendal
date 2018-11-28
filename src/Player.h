#pragma once

#include "ofMain.h"

class Player : public ofBaseApp{
	public:
		void setup(bool _isLocal);
		void update();

		void draw();
		void drawRibbon();
		void drawBullets();

		void moveTo(glm::vec3 pos);

		void keyPressed(int key);
		void keyReleased(int key);

		ofNode node;
		ofCamera cam;

		glm::vec3 getPosition(){return node.getPosition();};

	private:
		void updatePos();
		void drawPos();

		void fillRibbon();

		bool isLocal;

		glm::vec3 targetPos;

		glm::vec3 movForce;
		glm::vec3 panForce;
		glm::vec3 movAmt;
		glm::vec3 panAmt;

		vector<bool> keys;

		ofMesh ribbon;
//		ofMaterial ribbonMaterial;
		ofFloatColor ribbonColor;
		ofShader shader;
};
