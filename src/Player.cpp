#include "Player.h"

void Player::setup(bool _isLocal) {
	isLocal = _isLocal;

	shader.load("shaders/noise");

	keys.resize(9);

	cam.setParent(node);
//	node.setPosition(-240,-270,-300);
	node.setPosition(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	node.lookAt(ofVec3f(0,0,0), ofVec3f(0, -1, 0));

	ribbonColor.set(ofRandom(1000), ofRandom(1000), ofRandom(1000), 1);
	ribbonColor *= 0.001;

	ribbon.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
//	if(isLocal) ribbonMaterial.setDiffuseColor(ofFloatColor::red);
//	else ribbonMaterial.setDiffuseColor(ofFloatColor::blue);
}

void Player::update() {
	if(!(ofGetFrameNum()%2)) fillRibbon();
	updatePos();
}

void Player::draw() {
	node.transformGL();
		ofDrawCone(10,30);
	node.restoreTransformGL();
}

void Player::drawRibbon() {
//	ribbonMaterial.begin();
	shader.begin();

	shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
	shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18 );

	ribbon.drawFaces();

	shader.end();
//	ribbonMaterial.end();
}

void Player::moveTo(glm::vec3 pos) {
	targetPos = pos;	
}

//--------------------------------------------------------------
void Player::keyPressed(int key){

	float maxMov = 1;
	float maxPan = 0.5;

	switch (key) {
		case 'w':
			movAmt.z = -maxMov;
			break;
		case 's':
			movAmt.z = maxMov;
			break;
		case 'd':
			movAmt.x = maxMov;
			break;
		case 'a':
			movAmt.x = -maxMov;
			break;
		case OF_KEY_UP:
			panAmt.y = -maxPan;
			break;
		case OF_KEY_DOWN:
			panAmt.y = maxPan;
			break;
		case OF_KEY_RIGHT:
			panAmt.x = -maxPan;
			break;
		case OF_KEY_LEFT:
			panAmt.x = maxPan;
			break;
	}
}

void Player::keyReleased(int key){
	switch (key) {
		case 'w':
			movAmt.z = 0;
			break;
		case 's':
			movAmt.z = 0;
			break;
		case 'd':
			movAmt.x = 0;
			break;
		case 'a':
			movAmt.x = 0;
			break;
		case OF_KEY_UP:
			panAmt.y = 0;
			break;
		case OF_KEY_DOWN:
			panAmt.y = 0;
			break;
		case OF_KEY_RIGHT:
			panAmt.x = 0;
			break;
		case OF_KEY_LEFT:
			panAmt.x = 0;
			break;
	}
}

//--------------------------------------------------------------
void Player::updatePos() {
	// Only look for keys and update stuff if player is locally controllable
	if(isLocal) {
		movForce += movAmt;
		panForce += panAmt;

		if(movForce != glm::vec3(0)) {
			node.dolly(movForce.z);
			node.truck(movForce.x);
			movForce *= 0.9;
		}

		if(panForce != glm::vec3(0)) {
			node.panDeg(panForce.x);
			node.tiltDeg(panForce.y);
			panForce *= 0.9;
		}

	} else {
		if(node.getPosition() != targetPos) {
			ofNode tmpNode = node;;
			tmpNode.lookAt(targetPos, glm::vec3(0,1,0));
			tmpNode.tiltDeg(90);
			glm::quat lookDiff = glm::mix(node.getOrientationQuat(), tmpNode.getOrientationQuat(), (float)0.05);
			node.setOrientation(lookDiff);

			glm::vec3 amtVec;
			amtVec.x = 0.02;
			amtVec.y = 0.02;
			amtVec.z = 0.02;

			glm::vec3 newPos = glm::mix(node.getPosition(), targetPos, amtVec);
			node.setPosition(newPos);
		}
	}
}

void Player::drawPos() {
	string posString = "Pos: " + ofToString(node.getPosition());
	ofDrawBitmapString(posString, 10, 10);
}

void Player::fillRibbon() {
	glm::vec3 pos = node.getPosition();

	ribbon.addVertex(pos);
//        ribbon.addColor(ribbonColor);

	pos.x += 5;
	ribbon.addVertex(pos); // make a new vertex
 //       ribbon.addColor(ribbonColor);
}
