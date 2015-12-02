#include "ofApp.h"
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

ofVideoPlayer video;

float vw = 0.0;
float vh = 0.0;
float w = 0.0;
float h = 0.0;
float vsr = 0.0;

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
  video.loadMovie("/home/fu/Videos/Love-and-Math-videos/1.mp4");
  video.setVolume(0);

  // Get sizes
  vw = video.getWidth();
  vh = video.getHeight();
  w = ofGetScreenWidth();
  h = ofGetScreenHeight();
  // Calculate video scaling rate
  vsr = (h / vh) * 0.8;

  cout << currentDate() << endl;
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  // cout << "ON : key " << key << endl;

  // when press [space] key
  if(key == 32){
    if(video.isPlaying()){
      bool paused = video.isPaused();
      // const char* status = (!paused)? "[pause]": "[resume]";
      // cout << "Video: " << status << endl;
      video.setSpeed(1.0);
      video.setPaused(!paused);
    }else{
      // cout << "Video: [play]" << endl;
      video.play();
    }
  // when press [e] key
  }else if(key == 101){
    string path = currentDateWithCount() + ".png";
    ofPixels* pix = new ofPixels();

    video.setPaused(true);
    pix->setFromPixels(video.getPixels(), vw, vh, OF_IMAGE_COLOR);
    ofSaveImage(*pix, path, OF_IMAGE_QUALITY_MEDIUM);
    cout << "\nSaved frame to \"" << path << "\"" << endl;
  // left key
  }else if(key == 356){
    video.setPaused(false);
    video.setSpeed(2.0);
  // right key
  }else if(key == 358){
    video.setPaused(false);
    video.setSpeed(-2.0);
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  // cout << "OFF: key " << key << endl;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

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
