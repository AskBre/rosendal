#include "Player.h"

void Player::setup(ofxBulletWorldRigid &_world, bool _isLocal) {
	world = &_world;
	isLocal = _isLocal;

	shader.load("shaders/noise");
	bulletSound.load("laserShot.wav");
	bulletSound.setMultiPlay(true);

	glm::vec3 scale(0.1);

	ship.loadModel("SpaceShip.obj", false);
	ship.setScale(scale.x, scale.y, scale.z);

	keys.resize(9);

	if(ofxGamepadHandler::get()->getNumPads()>0){
			ofxGamepad* pad = ofxGamepadHandler::get()->getGamepad(playerNum-1);
			ofAddListener(pad->onAxisChanged, this, &Player::axisChanged);
			ofAddListener(pad->onButtonPressed, this, &Player::buttonPressed);
			ofAddListener(pad->onButtonReleased, this, &Player::buttonReleased);
	} else {
		ofLogNotice("Gamepad") << "No gamepad connected";
	}

	cam.setParent(node);
	node.setPosition(-240,-270,-300);
	node.lookAt(ofVec3f(0,0,0), ofVec3f(0, -1, 0));

	ribbonColor.set(ofRandom(1000), ofRandom(1000), ofRandom(1000), 1);
	ribbonColor *= 0.001;

	ribbon.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
//	if(isLocal) ribbonMaterial.setDiffuseColor(ofFloatColor::red);
//	else ribbonMaterial.setDiffuseColor(ofFloatColor::blue);
}

void Player::update() {
	if(!(ofGetFrameNum()%2)) fillRibbon();
//	if(!(ofGetFrameNum()%160)) ribbon.mergeDuplicateVertices();
	updatePos();
}

void Player::draw() {
	node.transformGL();
		ship.drawFaces();
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

void Player::drawBullets() {
	for(auto &b : bullets) b->draw();
}

void Player::moveTo(glm::vec3 position) {
	targetPos = position;	
}

void Player::rotateTo(glm::vec3 orientation) {
	targetOrient = orientation;	
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
		case ' ':
			shootBullet();
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
void Player::axisChanged(ofxGamepadAxisEvent& e) {
	if(!isLocal) return;

	float maxMov = 0.25;
	float maxPan = 0.12;
	switch (e.axis) {
		// Left joystick
		case 0:
			if(playerNum == 2) movAmt.x = ofMap(e.value - 0.0620584, -1, 1, -maxMov, maxMov, true);
			else movAmt.x = ofMap(e.value, -1, 1, -maxMov, maxMov, true);
			break;
		case 1:
			if(playerNum == 2) movAmt.z = ofMap(e.value - 0.0598612, 1, -1, -maxMov, maxMov, true);
			else movAmt.z = ofMap(e.value, 1, -1, -maxMov, maxMov, true);
			break;
		// Right joystick
		case 3:
			if(playerNum == 1) panAmt.x = -(e.value - 0.0583657) * maxPan;
			else panAmt.x = -e.value * maxPan;
			break;
		case 4:
			panAmt.y = -e.value * maxPan;
			break;
		// L2
		case 2:
			if(e.value < 0) isBulletReady = true;
			if(e.value > 0 && isBulletReady) shootBullet();
			break;
		// R2
		case 5:
			if(e.value < 0) isBulletReady = true;
			if(e.value > 0 && isBulletReady) shootBullet();
			break;
		default:
			break;
	}
}

void Player::buttonPressed(ofxGamepadButtonEvent& e) {
}

void Player::buttonReleased(ofxGamepadButtonEvent& e) {
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
		glm::vec3 amtVec(0.02);

		if(node.getPosition() != targetPos) {
			glm::vec3 newPos = glm::mix(node.getPosition(), targetPos, amtVec);
			node.setPosition(newPos);
		}

		node.setOrientation(targetOrient);
		/*
		if(node.getOrientationEulerDeg() != targetOrient) {
			glm::vec3 newOrient = glm::mix(node.getOrientationEulerDeg(), targetOrient, 0.002);
			node.setOrientation(newOrient);
		}
		*/
	}
}

void Player::drawPos() {
	string posString = "Pos: " + ofToString(node.getPosition());
	ofDrawBitmapString(posString, 10, 10);
}

void Player::fillRibbon() {
	glm::vec3 pos = node.getPosition();

	ribbon.addVertex(pos);
        ribbon.addColor(ribbonColor);

	pos.x += 2;
	ribbon.addVertex(pos); // make a new vertex
       ribbon.addColor(ribbonColor);
}

void Player::shootBullet() {
	bulletSound.play();

	isShootingBullet = true;

	unique_ptr<ofxBulletSphere> bullet(new ofxBulletSphere());

	bullet->create(world->world, node.getPosition(), 1, 1);
	bullet->setDamping(0);
	bullet->add();

	auto frc = node.getLookAtDir();
	frc = glm::normalize(frc);
	bullet->applyCentralForce(frc * 20000);

	bullets.push_back(move(bullet));

	if(bullets.size() > 100) bullets.pop_front();

	isBulletReady = false;

}
