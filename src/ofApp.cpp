#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //サンプリングレイトの設定
    sampleRate = 44100;
    
    //サウンド録音再生の初期化
    ofSoundStreamSetup(1, 1, this, sampleRate, LENGTH, CHANNEL);
    
    //再生モードに
    mode = 2;
    
    //録音、再生の位置を先頭に
    recPos = 0;
    playPos = 0;
    
    if (mode == 1) {
        //録音モードの場合、recordingの表示をして、背景を青に
        ofDrawBitmapString("recording", 10, 20);
        ofBackground(255, 0, 0);
    } else if (mode == 2) {
        //再生モードの場合、playingの表示をして、背景を赤に
        ofDrawBitmapString("playing", 10, 20);
        ofBackground(0, 0, 255);
    }
    
    //画面の幅と録音サンプル数の比率を計算
    int ratio = LENGTH / ofGetWidth();
    
    //画面の横幅にあわせて、波形を描画
    for (int i = 0; i < LENGTH; i+=ratio){
        ofLine(i/ratio,ofGetHeight()/2,i/ratio,ofGetHeight()/2+buffer[i]*100.0f);
    }
    
}

//--------------------------------------------------------------
//オーディオ入力の処理
void ofApp::audioReceived(float * input, int bufferSize, int nChannels){

    
    float crop = 1.0;
    
    //もし録音モードだったら
//        ofSoundStreamSetup(1, 1, this, sampleRate, LENGTH, CHANNEL);
    if (mode == 1) {
        //バッファされたサンプルの数だけ処理
        for (int i = 0; i < bufferSize*nChannels; i++){
            //録音位置が設定した最大の長さに逹っしていなければ
            if(recPos<LENGTH){
                //バッファにサウンド入力を設定
                buffer[recPos] = input[i];
                //録音位置を進める
                recPos++;
            } else {
                //もし最大位置を越えていたら、最初に戻る(ループ録音)
                recPos = 0;
            }
            
        }
    }
}


//--------------------------------------------------------------
//オーディオ再生の処理
void ofApp::audioRequested(float * output, int bufferSize, int nChannels){
    
//    int st = playPos;
    float spd =1.5;
    float target = (float)bufferSize*spd;
    float now = 0.0;
    int index = 0;
    
    //もし再生モードだったら
    if (mode == 2) {
        //バッファされたサンプル数だけ処理
        for (int i = 0; i < bufferSize*nChannels; i++) {
            //再生位置が設定した最大の長さに逹っしていなければ
            now = (float)i/(float)bufferSize; //CheckNowPosition
            //バッファに格納したサウンドを再生
            index = playPos+( (int)target*now );
            if(index>=LENGTH)index = index-LENGTH;
            output[i] = buffer[index];

        } playPos = index;
    }
}

////オーディオ再生の処理
//void ofApp::audioRequested(float * output, int bufferSize, int nChannels){
//    //もし再生モードだったら
//    if (mode == 2) {
//        //バッファされたサンプル数だけ処理
//        //        playPos*=1.03;
//        for (int i = 0; i < bufferSize*nChannels; i++) {
//            //再生位置が設定した最大の長さに逹っしていなければ
//            if(playPos<LENGTH){
//                //バッファに格納したサウンドを再生
//                //output[i] = buffer[playPos];
//                output[i] = ( buffer[playPos]+buffer[playPos+1] )*0.5;
//                //再生位置を進める
//                playPos++;
//                //                playPos+=2;
//            } else {
//                //もし最大位置を越えていたら、最初に戻る(ループ再生)
//                playPos = 0;
//            }
//        }
//    }
//}




//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    if(key=='p'){
 
        //画面をから指を離すと、再生モードへ
        mode = 2;
        playPos = 0;
        
        
    }
    if(key=='r'){
        
        //画面をタッチすると、録音モードへ
        mode = 1;
        recPos = 0;
        
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    //画面をタッチすると、録音モードへ
    mode = 1;
    recPos = 0;
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    //画面をから指を離すと、再生モードへ
    mode = 2;
    playPos = 0;
    
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
