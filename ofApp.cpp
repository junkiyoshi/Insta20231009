#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	auto param = ofGetFrameNum() % 50;
	if (param > 12 && param < 38) {

		if (param < 25) {
			
			this->noise_param += ofMap(param, 12, 25, 0, 0.15);
		}
		else if (param > 25) {

			this->noise_param += ofMap(param, 25, 38, 0.15, 0);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 2.88);

	int size = 10;
	for (int x = -100; x <= 100; x += size) {

		for (int y = -200; y <= 200; y += size) {

			for (int z = -100; z <= 100; z += size) {

				auto noise_value = ofNoise(x * 0.0025, y * 0.002 + this->noise_param, z * 0.005);
				if (noise_value >= 0.4 && noise_value <= 0.5) {

					ofSetColor(0);
					ofFill();
					ofDrawBox(glm::vec3(x, y, z), size * 0.99);

					ofSetColor(239);
					ofNoFill();
					ofDrawBox(glm::vec3(x, y, z), size * 0.99);
				}
			}
		}
	}

	ofSetColor(0);
	ofDrawBox(300 + size, 400 + size, 300 + size);

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}