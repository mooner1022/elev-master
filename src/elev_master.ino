#include <Arduino.h>
#include <stdio.h>

const int TouchPin[] = {22,24,26,28,30,32};
boolean isMoving[] = {false,false,false};
boolean moveDirection[] = {false,false,false};
int currentFloor[3] = {0,0,0};
//int inSensorVal[3] = {0,0,0};
//boolean isRequireCalibration[3] = {true,true,false);
boolean touchFlag[6] = {false,false,false,false,false,false};

void setup() {
  pinMode(TouchPin[0], INPUT);
  pinMode(TouchPin[1], INPUT);
  pinMode(TouchPin[2], INPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  int sensorValue1 = digitalRead(TouchPin[0]);
  int sensorValue2 = digitalRead(TouchPin[1]);
  int sensorValue3 = digitalRead(TouchPin[2]);
  int sensorValue4 = digitalRead(TouchPin[3]);
  int sensorValue5 = digitalRead(TouchPin[4]);
  int sensorValue6 = digitalRead(TouchPin[5]);
  if(sensorValue1==1) {
    if (touchFlag[0] == false) {
      Serial.println('1');
      Serial1.println('1');
      Serial2.println('1');
      touchFlag[0] = true;
      requestState(1);
      requestState(2);
      requestState(3);
    }
  } else if (sensorValue1 == 0) {
    touchFlag[0] = false;
  }
  if(sensorValue2==1) {
    if (!touchFlag[1]) {
      Serial.println('2');
      Serial1.println('2');
      Serial2.println('2');
      touchFlag[1] = true;
    }
  } else {
    touchFlag[1] = false;
  }
  if(sensorValue3==1) {
    if (!touchFlag[2]) {
      Serial.println('2');
      Serial1.println('2');
      Serial2.println('2');
      touchFlag[2] = true;
    }
  } else {
    touchFlag[2] = false;
  }
  if(sensorValue4==1) {
    if (!touchFlag[3]) {
      Serial.println('3');
      Serial1.println('3');
      Serial2.println('3');
      touchFlag[3] = true;
    }
  } else {
    touchFlag[3] = false;
  }
  if(sensorValue5==1) {
    if (!touchFlag[4]) {
      Serial.println('3');
      Serial1.println('3');
      Serial2.println('3');
      touchFlag[4] = true;
    }
  } else {
    touchFlag[4] = false;
  }
  if(sensorValue6==1) {
    if (!touchFlag[5]) {
      Serial.println('4');
      Serial1.println('4');
      Serial2.println('4');
      touchFlag[5] = true;
    }
  } else {
    touchFlag[5] = false;
  }
  
  if(Serial.available()){
    String inStr=Serial.readStringUntil('\n');
    saveRequest(inStr,0);
  }
  if(Serial1.available()){
    String inStr=Serial1.readStringUntil('\n');
    saveRequest(inStr,1);
  }
  if(Serial2.available()){
    String inStr=Serial2.readStringUntil('\n');
    saveRequest(inStr,2);
  }
}

void saveRequest(String inStr,int elevNum) {
  currentFloor[elevNum] = getValue(inStr,',',0).toInt();
  int raw = getValue(inStr,',',0).toInt();
  if (raw==0) {
    isMoving[elevNum] = false;
  } else {
    isMoving[elevNum] = true;
    moveDirection[elevNum] = (raw==1);
  }
  Serial.print(currentFloor[elevNum]);
  Serial.print(" ");
  Serial.print(isMoving[elevNum]);
  Serial.print(" ");
  Serial.print(moveDirection[elevNum]);
  Serial.println();
}

void requestState(int elev) {
  switch (elev) {
  case 1:
    Serial.println('S');
    break;
  case 2:
    Serial1.println('S');
    break;
  case 3:
    Serial2.println('S');
    break;
  default:
    break;
  }
}

String getValue(String data, char separator, int index){
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
