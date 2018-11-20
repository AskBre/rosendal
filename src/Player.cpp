#include "Player.h"

void Player::setup(ofxBulletWorldRigid &_world, bool _isLocal) {
	world = &_world;
	isLocal = _isLocal;

	shader.load("shaders/noise");

	keys.resize(9);

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
	fillRibbon();
	updatePos();
	if(keys.at(8)) shootBullet();
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

void Player::drawBullets() {
	for(auto &b : bullets) b->draw();
}

void Player::moveTo(glm::vec3 pos) {
	targetPos = pos;	
}

//--------------------------------------------------------------
void Player::keyPressed(int key){
	switch (key) {
		case 'w':
			keys.at(0) = true;
			break;
		case 's':
			keys.at(1) = true;
			break;
		case 'd':
			keys.at(2) = true;
			break;
		case 'a':
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
		case ' ':
			keys.at(8) = true;
			break;
	}
}

void Player::keyReleased(int key){
	switch (key) {
		case 'w':
			keys.at(0) = false;
			break;
		case 's':
			keys.at(1) = false;
			break;
		case 'd':
			keys.at(2) = false;
			break;
		case 'a':
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
		case ' ':
			keys.at(8) = false;
			break;
	}
}

//--------------------------------------------------------------
void Player::updatePos() {
	
	// Only look for keys and update stuff if player is locally controllable
	if(isLocal) {
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

		float movVel = 1;
		float panVel = 0.5;

		if(keys.at(0)) movForce.z -= movVel;
		if(keys.at(1)) movForce.z += movVel;
		if(keys.at(2)) movForce.x += movVel;
		if(keys.at(3)) movForce.x -= movVel;

		if(keys.at(4)) panForce.y -= panVel;
		if(keys.at(5)) panForce.y += panVel;
		if(keys.at(6)) panForce.x -= panVel;
		if(keys.at(7)) panForce.x += panVel;
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
        ribbon.addColor(ribbonColor);

	pos.x += 5;
	ribbon.addVertex(pos); // make a new vertex
        ribbon.addColor(ribbonColor);
}

void Player::shootBullet() {
	unique_ptr<ofxBulletSphere> bullet(new ofxBulletSphere());

	bullet->create(world->world, node.getPosition(), 1, 1);
	bullet->setDamping(0);
	bullet->add();

	auto frc = node.getLookAtDir();
	frc = glm::normalize(frc);
	bullet->applyCentralForce(frc * 40000);

	bullets.push_back(move(bullet));

	if(bullets.size() > 100) bullets.pop_front();
}
