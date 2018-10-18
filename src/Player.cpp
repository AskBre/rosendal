#include "Player.h"

void Player::setup() {
	keys.resize(8);
	cam.setPosition(-240,-270,-300);
	cam.lookAt(ofVec3f(0,0,0), ofVec3f(0, -1, 0));

	camForce.set(ofPoint(0));
	panForce.set(ofPoint(0));
}

void Player::update() {
	updateCam();
}

void Player::keyPressed(int key){
	switch (key) {
		case 119:
			keys.at(0) = true;
			break;
		case 115:
			keys.at(1) = true;
			break;
		case 100:
			keys.at(2) = true;
			break;
		case 97:
			keys.at(3) = true;
			break;
		case OF_KEY_UP:
			keys.at(4) = true;
			break;
		case OF_KEY_DOWN:
			keys.at(5) = true;
			break;
		case OF_KEY_RIGHT:
			keys.at(6) = true;
			break;
		case OF_KEY_LEFT:
			keys.at(7) = true;
			break;
	}

}

void Player::keyReleased(int key){
	switch (key) {
		case 119:
			keys.at(0) = false;
			break;
		case 115:
			keys.at(1) = false;
			break;
		case 100:
			keys.at(2) = false;
			break;
		case 97:
			keys.at(3) = false;
			break;
		case OF_KEY_UP:
			keys.at(4) = false;
			break;
		case OF_KEY_DOWN:
			keys.at(5) = false;
			break;
		case OF_KEY_RIGHT:
			keys.at(6) = false;
			break;
		case OF_KEY_LEFT:
			keys.at(7) = false;
			break;
	}

}

//--------------------------------------------------------------
void Player::updateCam() {
	if(camForce != ofPoint(0)) {
		cam.dolly(camForce.z);
		cam.truck(camForce.x);
		camForce *= 0.9;
	}

	if(panForce != ofPoint(0)) {
		cam.panDeg(panForce.x);
		cam.tiltDeg(panForce.y);
		panForce *= 0.9;
	}

	float camVel = 1;
	float panVel = 0.5;

	if(keys.at(0)) camForce.z -= camVel;
	if(keys.at(1)) camForce.z += camVel;
	if(keys.at(2)) camForce.x += camVel;
	if(keys.at(3)) camForce.x -= camVel;

	if(keys.at(4)) panForce.y -= panVel;
	if(keys.at(5)) panForce.y += panVel;
	if(keys.at(6)) panForce.x -= panVel;
	if(keys.at(7)) panForce.x += panVel;
}

void Player::drawCamPos() {
	string camPosString = "Pos: " + ofToString(cam.getPosition());
	ofDrawBitmapString(camPosString, 10, 10);
}
