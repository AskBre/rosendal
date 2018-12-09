#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
//	ofSetLogLevel(OF_LOG_VERBOSE);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	ofEnableDepthTest();
	ofEnableAlphaBlending();

	ofLogNotice("Loading theatre");
	model.loadModel("Rosendal Teater_ARK Contiga skyveamfi.ifc", true);
	model.setPosition(250, 250, 250);

	player1.setup(false);
	player2.setup(false);

	cam.lookAt(ofVec3f(0,0,0), ofVec3f(0, -1, 0));

	light1.setPosition(0, 0, 0);
	light1.setParent(cam);
	light1.setPosition(1000, 1000, 1000);
	light1.setParent(cam);

	setupNetwork();
}

void ofApp::setupNetwork() {
	ofxUDPSettings settings;
//	settings.sendTo("192.168.1.195", 12000);

	settings.blocking = false;
	settings.receiveOn(12002);
	udpReceiver1.Setup(settings);

	settings.receiveOn(12003);
	udpReceiver2.Setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){
	player1.update();
	player2.update();

	glm::vec3 origo = model.getPosition();
	origo.x -= 200;
	origo.y -= 200;
	origo.z -= 400;

	cam.orbitDeg(ofGetFrameNum()*0.25, 0, 2000, origo);
	updateNetwork();

//	if(!(ofGetFrameNum()%250)) player.moveTo(ofPoint(ofRandom(1000),ofRandom(1000),ofRandom(1000)));
}

void ofApp::updateNetwork() {
	// Multiplayer stuff
	char udpMessage[100000];
	if(udpReceiver1.Receive(udpMessage, 100000)){
		string recMessage = udpMessage;
		ofLogNotice("Received udp:") << recMessage;

		vector<string> coordinates = ofSplitString(recMessage, ",");
		glm::vec3 pos;
		pos.x = stoi(coordinates.at(0));
		pos.y = stoi(coordinates.at(1));
		pos.z = stoi(coordinates.at(2));

		player1.moveTo(pos);
	}

	if(udpReceiver2.Receive(udpMessage, 100000)){
		string recMessage = udpMessage;
		ofLogNotice("Received udp:") << recMessage;

		vector<string> coordinates = ofSplitString(recMessage, ",");
		glm::vec3 pos;
		pos.x = stoi(coordinates.at(0));
		pos.y = stoi(coordinates.at(1));
		pos.z = stoi(coordinates.at(2));

		player2.moveTo(pos);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	ofFill();

	ofEnableLighting();
	light1.enable();
	light2.enable();

	cam.begin();

	ofPushMatrix();
	ofRotate(180);
	model.drawFaces();
	ofPopMatrix();

	player1.drawRibbon();
	player2.drawRibbon();

	cam.end();

	light1.disable();
	light2.disable();
	ofDisableLighting();

	ofSetColor(255, 255, 255, 255);
	ofFill();
	ofDrawRectRounded(0, 0, 75, 20, 5);
	ofSetColor(50,50,50,255);
	ofDrawBitmapString(ofGetFrameRate(), 10, 10);
}
