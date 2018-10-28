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
	playerRibbon.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	ribbonMaterial.setDiffuseColor(ofFloatColor::red);
	ribbonMaterial.setSpecularColor(ofColor(255, 255, 255, 255));
	ribbonMaterial.setShininess(120);
	
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

//		houseMeshes.at(i).mergeDuplicateVertices();
	}

	ofLogNotice("Loaded ") << house.size() << "elements";
	light1.setPosition(-500,-500,-500);
	light2.setPosition(500,500,500);
}

void ofApp::update(){
	player.update();
	if(!(ofGetSeconds()%2)) fillRibbon();

//	model.update();
	world.update();
}

void ofApp::draw(){
	ofSetColor(255);
	light1.enable();
	light2.enable();
	player.cam.begin();
	drawHouse();	
	drawRibbon();

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

void ofApp::fillRibbon() {
	ofPoint pos = player.getPosition();

	playerRibbon.addVertex(pos); // make a new vertex
        playerRibbon.addColor(ofFloatColor(255));  // add a color at that vertex

	pos.x += 5;
	playerRibbon.addVertex(pos); // make a new vertex
        playerRibbon.addColor(ofFloatColor(255));  // add a color at that vertex
}

void ofApp::drawRibbon() {
	ribbonMaterial.begin();
	playerRibbon.drawFaces();
	ribbonMaterial.end();
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
