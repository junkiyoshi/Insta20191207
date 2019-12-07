#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(315);

	int gon = 36;
	int u_span = 360 / gon;

	ofMesh face, frame;
	for (int v = 0; v <= 360; v += 5) {

		int index = face.getNumVertices() - gon;
		auto noise_value = ofMap(ofNoise(200 * cos(v * DEG_TO_RAD) * 0.0065, 200 * sin(v * DEG_TO_RAD) * 0.0065, ofGetFrameNum() * 0.01), 0, 1, 0.5, 1.5);

		for (int u = 0; u < 360; u += u_span) {

			face.addVertex(this->make_point(200, 50 * noise_value, u, v));
			frame.addVertex(this->make_point(200, 51 * noise_value, u, v));
		}

		if (index > -1) {

			for (int g = 0; g < gon; g++) {

				face.addIndex(index + g); face.addIndex(index + (g + 1) % gon); face.addIndex(index + g + gon);
				face.addIndex(index + (g + 1) % gon + gon); face.addIndex(index + (g + 1) % gon); face.addIndex(index + g + gon);

				frame.addIndex(index + g); frame.addIndex(index + (g + 1) % gon); frame.addIndex(index + g + gon);
				frame.addIndex(index + (g + 1) % gon + gon); frame.addIndex(index + (g + 1) % gon); frame.addIndex(index + g + gon);
			}
		}
	}

	ofSetColor(239);
	face.drawFaces();

	ofSetColor(39);
	frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}