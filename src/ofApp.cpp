#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(10, 10, 10);
	ofSetLogLevel(OF_LOG_VERBOSE);
//	ofSetOrientation(OF_ORIENTATION_DEFAULT,false);

	scale.set(0.01);

	player.setup();
	
	model.loadModel("Rosendal Teater_ARK Contiga skyveamfi.ifc", false);
//	model.optimizeScene();
//	model.setScaleNormalization(true);
	model.setScale(scale.x, scale.y, scale.z);
//	model.setPosition(0,0,0);

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
		ofLogNotice("Loaded") << meshNames[i];
	}

	light.setPosition(-500,-500,-500);

	ground.create( world.world, ofVec3f(0., -100, 0.), 0., 100.f, 1.f, 100.f );
//	ground.setProperties(.25, .95);
	ground.add();

}

void ofApp::update(){
	player.update();

//	model.update();
	world.update();
}

void ofApp::draw(){
	ofEnableDepthTest();
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	ofSetColor(255);
	light.enable();
	player.cam.begin();
	drawHouse();	

	// world.drawDebug();
	// model.drawFaces();
	player.cam.end();
	light.disable();
}

//--------------------------------------------------------------
void ofApp::drawHouse() {
	for(unsigned i=0; i<house.size(); i++) {
		ofxAssimpMeshHelper & meshHelper = model.getMeshHelper(i);
		ofMaterial & material = meshHelper.material;
		if(meshHelper.hasTexture()){
			meshHelper.getTextureRef().bind();
		}
		material.begin();
		house[i]->transformGL();
		ofScale(scale);
		model.getMesh(i).drawFaces();
		house[i]->restoreTransformGL();
		material.end();
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
