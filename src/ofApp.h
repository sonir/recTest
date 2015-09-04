#pragma once

#include "ofMain.h"

#define SAMPLING_RATE 44100
#define CHANNEL 1
#define REC_DURATION_SEC 5
//#define LENGTH (SAMPLING_RATE * REC_DURARTION_SEC * CHANNEL)
#define LENGTH SAMPLING_RATE * (CHANNEL * REC_DURATION_SEC)


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void audioReceived(float * input, int bufferSize, int nChannels);
        void audioRequested(float * output, int bufferSize, int nChannels);
    

        float buffer[LENGTH]; //オーディオバッファ
        int sampleRate; //サンプリングレイト
        int recPos; //レコード位置
        int playPos; //再生位置
        int mode; //現在のモード、0:off, 1:recording, 2:play
    
        int bg;
    
};
