#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
//	ofSetLogLevel(OF_LOG_VERBOSE);

//	glShadeModel(GL_SMOOTH);
//	glEnable(GL_NORMALIZE);
	ofEnableDepthTest();
//	ofEnableAlphaBlending();

	scale.set(0.01);
		
	ofLogNotice("Loading theatre");
	model.loadModel("Rosendal Teater_ARK Contiga skyveamfi.ifc", false);
	model.setScale(scale.x, scale.y, scale.z);

	world.setup();
	world.setGravity( ofVec3f(0, 0, 0) );
	world.enableGrabbing();
	world.enableDebugDraw();
	world.setCamera(&player.cam);

	player.setup(world, true);
	player2.setup(world, false);

	ofLogNotice("Loading meshes");
	for(unsigned i=0; i<model.getNumMeshes(); i++) {

		houseMeshes.push_back(model.getMesh(i));
		houseMaterials.push_back(model.getMaterialForMesh(i));

		ofxBulletCustomShape* h;
		h = new ofxBulletCustomShape();

		h->addMesh(houseMeshes.at(i), scale, true);
		h->create(world.world, randomPoint(), 10.);
		h->add();

		house.push_back(h);
	}

	ofLogNotice("Loaded ") << house.size() << "elements";

	light1.setPosition(0, 0, 0);

	light2.setParent(player.node);
	light2.setSpotlight(10);
	light2.setSpotConcentration(100);

	setupNetwork();
}

void ofApp::setupNetwork() {
	ofxUDPSettings settings;
	if(player.playerNum == 1) settings.sendTo("127.0.0.1", 12000);
	if(player.playerNum == 2) settings.sendTo("127.0.0.1", 12001);
	settings.blocking = false;
	udpSender.Setup(settings);

	if(player.playerNum == 1) settings.receiveOn(12001);
	if(player.playerNum == 2) settings.receiveOn(12000);

	udpReceiver.Setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){
	world.update();
	player.update();
	player2.update();
	updateNetwork();
}

void ofApp::updateNetwork() {
	// Multiplayer stuff
	// TODO Only send when pos is changed
	if(!(ofGetFrameNum() % 10)) {
		glm::vec3 p = player.getPosition();

		int x = (int)p.x;
		int y = (int)p.y;
		int z = (int)p.z;

		string sendMessage = ofToString(x) + "," + ofToString(y) + "," + ofToString(z);
		udpSender.Send(sendMessage.c_str(), sendMessage.length());
	}

	// Bot
//	if(!(ofGetFrameNum() % 120)) {
//		player2.moveTo(randomPoint());
//	}

	char udpMessage[100000];
	if(udpReceiver.Receive(udpMessage, 100000)){
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

	player.cam.begin();

	drawHouse();	
	player.drawBullets();
	player2.draw();
	player.drawRibbon();
	player2.drawRibbon();

	player.cam.end();

	light1.disable();
	light2.disable();
	ofDisableLighting();

	ofSetColor(255, 255, 255, 255);
	ofFill();
	ofDrawRectRounded(0, 0, 75, 20, 5);
	ofSetColor(50,50,50,255);
	ofDrawBitmapString(ofGetFrameRate(), 10, 10);
}

//--------------------------------------------------------------
void ofApp::drawHouse() {
	for(unsigned i=0; i<house.size(); i++) {
		houseMaterials.at(i).begin();
		house[i]->transformGL();
		ofScale(scale);
		houseMeshes.at(i).drawFaces();
		house[i]->restoreTransformGL();
		houseMaterials.at(i).end();
	}
}

glm::vec3 ofApp::randomPoint(int min, int max) {
	glm::vec3 p(ofRandom(min, max),ofRandom(min, max),ofRandom(min, max));

	return p;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	player.keyPressed(key);
}

void ofApp::keyReleased(int key){
	player.keyReleased(key);
}
