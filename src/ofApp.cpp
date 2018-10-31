#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(10, 10, 10);
//	ofSetLogLevel(OF_LOG_VERBOSE);
//	ofSetOrientation(OF_ORIENTATION_DEFAULT,false);

//	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	ofEnableDepthTest();

	scale.set(0.01);

	player.setup();
	player2.setPosition(-240, -270, -300);
	player2.lookAt(ofVec3f(0,0,0), ofVec3f(0, -1, 0));
		
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
	light1.setPosition(-500,-500,-500);
	light2.setPosition(500,500,500);


	// Multiplayer stuff
	ofxUDPSettings settings;
	settings.sendTo("192.168.1.195", 12000);
	settings.blocking = false;
	udpSender.Setup(settings);

	settings.receiveOn(12001);
	udpReceiver.Setup(settings);
}

void ofApp::update(){
	player.update();
	world.update();

	// Multiplayer stuff
	// TODO Only send when pos is changed
	ofPoint p = player.getPosition();

	int x = (int)p.x;
	int y = (int)p.y;
	int z = (int)p.z;

	string sendMessage = ofToString(x) + "," + ofToString(y) + "," + ofToString(z);
	udpSender.Send(sendMessage.c_str(), sendMessage.length());

	char udpMessage[100000];
	if(udpReceiver.Receive(udpMessage, 100000)){
		string recMessage = udpMessage;
		ofLogNotice("Received udp:") << recMessage;

		vector<string> coordinates = ofSplitString(recMessage, ",");
		ofPoint pos;
		pos.x = stoi(coordinates.at(0));
		pos.y = stoi(coordinates.at(1));
		pos.z = stoi(coordinates.at(2));

		player2.setPosition(pos);
	}
}

void ofApp::draw(){
	ofSetColor(255);
	light1.enable();
	light2.enable();

	player.cam.begin();
	drawHouse();	
	player2.draw();
	player.drawRibbon();

	// world.drawDebug();
//	model.drawFaces();
	player.cam.end();
	light1.disable();
	light2.disable();

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

ofPoint ofApp::randomPoint(int min, int max) {
	ofPoint p(ofRandom(min, max),ofRandom(min, max),ofRandom(min, max));

	return p;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	player.keyPressed(key);
}

void ofApp::keyReleased(int key){
	player.keyReleased(key);
}
