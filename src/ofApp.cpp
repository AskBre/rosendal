#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(false);
	ofBackground(0, 0, 0);
//	ofSetLogLevel(OF_LOG_VERBOSE);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	ofEnableDepthTest();

	scale.set(0.01);

	player.setup(true);
	player2.setup(false);
	player2.moveTo(glm::vec3(-240, -270, -300));
		
	model.loadModel("Rosendal Teater_ARK Contiga skyveamfi.ifc", false);
	model.setScale(scale.x, scale.y, scale.z);

	world.setup();
	world.setGravity( ofVec3f(0, 0, 0) );
	world.enableGrabbing();
//	world.enableDebugDraw();
	world.setCamera(&player.cam);

	vector<string> meshNames = model.getMeshNames();

	for(unsigned i=0; i<model.getNumMeshes(); i++) {
		ofxBulletCustomShape* h;
		h = new ofxBulletCustomShape();

		h->addMesh(model.getMesh(i), scale, true);
		h->create(world.world, randomPoint(), 10.);
		h->add();

		house.push_back(h);
		houseMeshes.push_back(model.getMesh(i));
		houseMaterials.push_back(model.getMaterialForMesh(i));
	}

	ofLogNotice("Loaded ") << house.size() << "elements";

//	light1.setParent(player.cam);
	light1.setPosition(0, 0, 0);
//	light1.setSpotlight(25);
	light1.setSpotConcentration(100);
//	light1.lookAt(ofVec3f(500,500,500));
//	light2.setPosition(500,500,500);

	setupNetwork();
}

void ofApp::setupNetwork() {
	ofxUDPSettings settings;
	settings.sendTo("192.168.1.195", 12000);
	settings.blocking = false;
	udpSender.Setup(settings);

	settings.receiveOn(12001);
	udpReceiver.Setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){
	player.update();
	player2.update();
	world.update();
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

	if(!(ofGetFrameNum() % 120)) {
		player2.moveTo(randomPoint());
	}

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
	light1.enable();
//	light2.enable();

	player.cam.begin();
	drawHouse();	
	player2.draw();
	player.drawRibbon();
	ofSetColor(255,0,0);
	ofSetColor(255, 255, 255);

//	world.drawDebug();
//	model.drawFaces();
	player.cam.end();
	light1.disable();
//	light2.disable();

	ofSetColor(255, 255, 255, 255);
	ofFill();
	ofDrawRectRounded(0, 0, 75, 20, 5);
	ofSetColor(0,0,0,255);
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
