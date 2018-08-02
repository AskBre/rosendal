#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(10, 10, 10);
	ofSetLogLevel(OF_LOG_VERBOSE);
//	ofSetOrientation(OF_ORIENTATION_DEFAULT,false);

	scale.set(0.01);
	keys.resize(8);
	
	model.loadModel("Rosendal Teater_ARK Contiga skyveamfi.ifc", false);
//	model.optimizeScene();
//	model.setScaleNormalization(true);
	model.setScale(scale.x, scale.y, scale.z);
//	model.setPosition(0,0,0);

	cam.setPosition(-240,-270,-300);
//	cam.lookAt(model.getSceneMin(), ofVec3f(0, -1, 0));

	world.setup();
	world.setGravity( ofVec3f(0, 0, 0) );
	world.enableGrabbing();
//	world.enableDebugDraw();
	world.setCamera(&cam);

	sphere = new ofxBulletSphere();
	sphere->create(world.world, randomPoint(), 0.9, 1);
	sphere->add();

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

	cam.lookAt(sphere->getPosition(), ofVec3f(0, -1, 0));
	camForce.set(ofPoint(0));
	panForce.set(ofPoint(0));

	light.setPosition(-500,-500,-500);

	ground.create( world.world, ofVec3f(0., -100, 0.), 0., 100.f, 1.f, 100.f );
//	ground.setProperties(.25, .95);
	ground.add();

}

void ofApp::update(){
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

	updateCam();

//	cam.lookAt(sphere->getPosition());

//	model.update();
	world.update();
}

void ofApp::draw(){
	ofEnableDepthTest();
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	ofSetColor(255);
	light.enable();
	cam.begin();

//	world.drawDebug();

	sphere->draw();
	
//	model.drawFaces();

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

	cam.end();
	light.disable();

	drawCamPos();
}

//--------------------------------------------------------------
void ofApp::updateCam() {
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

void ofApp::exportPly(ofxAssimpModelLoader &model) {
	ofMesh bigMesh;

	for(int i=0; i<model.getNumMeshes(); i++){
		bigMesh.append(model.getMesh(i));
	}

	bigMesh.save("RosendalTeater.ply");
}

ofMesh ofApp::makeMesh(ofxAssimpModelLoader &modelfxAssimp) {
	ofMesh bigMesh;

	for(int i=0; i<model.getNumMeshes(); i++){
		bigMesh.append(model.getMesh(i));
	}

	return bigMesh;
}

void ofApp::drawCamPos() {
	string camPosString = "Pos: " + ofToString(cam.getPosition());
	ofDrawBitmapString(camPosString, 10, 10);
}

ofPoint ofApp::randomPoint(int min, int max) {
	ofPoint p(ofRandom(min, max),ofRandom(min, max),ofRandom(min, max));

	return p;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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

void ofApp::keyReleased(int key){
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

void ofApp::mouseMoved(int x, int y){
}

void ofApp::mouseDragged(int x, int y, int button){
	/*
	   float amt = 0.5;
	   ofPoint mouseDist;
	   ofPoint curMouse;
	   curMouse.set(x,y);

	   mouseDist = prevMouse-curMouse;
	   mouseDist.scale(1);

	   cam.panDeg(mouseDist.x*amt);
	   cam.tiltDeg(mouseDist.y*amt);
	   */

}

void ofApp::mousePressed(int x, int y, int button){
//	prevMouse.set(x,y);
}

void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
