#include "ofApp.h"
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

ofVideoPlayer video;

float vw = 0.0;
float vh = 0.0;
float winX = 0.0;
float winY = 0.0;
float w = 0.0;
float h = 0.0;
float vsr = 0.0;
float scaleRate = 1.0;

float vSpeed = 1.0;
float vVector = 1.0;

string currentDate(){
  struct tm *date;
  time_t now;
  time(&now);
  date = localtime(&now);
  int y = date->tm_year + 1900;
  int mon = date->tm_mon + 1;
  int d = date->tm_mday;
  int h = date->tm_hour;
  int min = date->tm_min;
  int sec = date->tm_sec;

  ostringstream oss;
  oss << y <<
    setfill('0') << setw(2) << mon <<
    setfill('0') << setw(2) << d << "-" <<
    setfill('0') << setw(2) << h <<
    setfill('0') << setw(2) << min <<
    setfill('0') << setw(2) << sec;
  return oss.str();
}

string currentDateWithCount(){
  static long count = 0;
  ostringstream oss;
  oss << currentDate() << "-" <<
    setfill('0') << setw(3) << ++count;
  return oss.str();
}

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetLogLevel(OF_LOG_NOTICE);

  ofFileDialogResult result = ofSystemLoadDialog("Select movie file...");
  if(result.bSuccess == false){
    ofLogWarning() << "SystemDialog canceled";
    ofExit(1);
  }

  ofSleepMillis(300);
  video.load(result.getPath());
  video.setVolume(0);
  video.setLoopState(OF_LOOP_NONE);

  // WORKAROUND
  video.play();
  video.stop();

  // Get sizes
  vw = video.getWidth();
  vh = video.getHeight();
  w = ofGetWindowWidth();
  h = ofGetWindowHeight();

  winX = ofGetWindowPositionX();
  winX = ofGetWindowPositionY();

  // Calculate video scaling rate
  if(vh > vw){
    vsr = (h / vh) * scaleRate;
  }else{
    vsr = (w / vw) * scaleRate;
  }
}

//--------------------------------------------------------------
void ofApp::update(){
  video.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofPushMatrix();
  ofScale(vsr,vsr);
  video.draw(0,0);
  ofPopMatrix();
}

void ofApp::applyVideoMatrix(){
  bool stopped = video.isPaused();
  video.setSpeed(vVector * vSpeed);
  ofLogNotice() << "Speed: " << vSpeed << ", Vector: " << vVector;
  if(stopped){
    video.setPaused(true);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  ofLogVerbose() << "ON : key " << key;

  // [space]: toggle pause and resume
  if(key == 32){
    if(video.isPlaying()){
      bool paused = video.isPaused();

      const char* status = (!paused)? "[pause]": "[resume]";
      ofLogNotice() << "Video: " << status;

      video.setPaused(!paused);
    }else{
      ofLogNotice() << "Video: [play]";
      video.play();
    }
  // [e] or [s]: save frame
  }else if(key == 101 || key == 115){
    string path = currentDateWithCount() + ".png";
    ofPixels* pix = new ofPixels();

    video.setPaused(true);
    pix->setFromPixels(video.getPixels(), vw, vh, OF_IMAGE_COLOR);
    ofSaveImage(*pix, path, OF_IMAGE_QUALITY_MEDIUM);

    ofLogWarning() << "\nSaved frame to \"" << path << "\"" << endl;

  // left key: forward
  }else if(key == 356){
    vVector = 1.0;
    applyVideoMatrix();
  // right key: backward
  }else if(key == 358){
    vVector = -1.0;
    applyVideoMatrix();

  // [0]: very slow speed
  }else if(key == 48){
    vSpeed = 0.25;
    applyVideoMatrix();
  // [1]: normal speed
  }else if(key == 49){
    vSpeed = 1.0;
    applyVideoMatrix();
  // [2]: fast speed
  }else if(key == 50){
    vSpeed = 2.0;
    applyVideoMatrix();
  // [9]: slow speed
}else if(key == 57){
    vSpeed = 0.5;
    applyVideoMatrix();
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  ofLogVerbose() << "OFF: key " << key;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  ofLogNotice() << "Position: " << x/w << "";
  video.setPosition(x / w);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
