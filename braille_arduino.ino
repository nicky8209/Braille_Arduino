#include <SoftwareSerial.h>
#include <Stepper.h>

int now = 0;
int next = 0;
String temp;
int now2 = 0;
int next2 = 0;
int now3 = 0;
int next3 = 0;
String temp2;
String braille[2];
int steps[8] = {0, 256, 512, 768, 1024, 1280, 1536, 1792}; //각도배열
Stepper myStepper(2048, 25, 23, 24, 22); //모터1
Stepper myStepper2(2048, 29, 27, 28, 26); //모터2
Stepper myStepper3(2048, 33, 31, 32, 30); //모터3

boolean motor1 = true;
boolean motor2 = false;
boolean motor3 = false;

#define BT_RXD 52
#define BT_TXD 53
SoftwareSerial bluetooth(BT_RXD, BT_TXD);
String btread;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  myStepper.setSpeed(14);
  myStepper2.setSpeed(14);
  myStepper3.setSpeed(14);
}

void loop() {
  if (bluetooth.available()) {
    btread = bluetooth.read();
    btread = btread.toInt() - 48;
    temp = btread.substring(0);
    /*
        for(int i=0;i<2;i++){ //블루투스에서 들어온 값을 배열에 각자 저장 현재 2개만 테스트용으로 해둠
          braille[i]=temp;
          Serial.print("braille ");
          Serial.print(i);
          Serial.print("번째:");
          Serial.println(braille[i]);
        }*/
    if (motor1 == true) { //모터1
      next = temp.toInt();
      Serial.print("next:");
      Serial.println(next);

      next = next - now;  //다음 칸 계산
      Serial.print("계산후next:");
      Serial.println(next);

      if (next >= 0) { //모터 회전
        Serial.println("모터1 정방향 회전");
        myStepper.step(steps[next]);
      } else {
        Serial.println("모터1 반대방향 회전");
        myStepper.step(-steps[next]);
      }

      now = next % 8; //현재값 저장
      Serial.print("now:");
      Serial.println(now);
      Serial.println("모터1 off 모터2 on");
      motor1 = false; //모터1 off
      motor2 = true; //모터2 on

      delay(500);
    } else if (motor2 == true) { //모터2
      next = temp.toInt();
      Serial.print("next:");
      Serial.println(next);

      next = next - now2;  //다음 칸 계산
      Serial.print("계산후next:");
      Serial.println(next);

      if (next >= 0) { //모터 회전
        Serial.println("모터2 정방향 회전");
        myStepper2.step(-steps[next]);
      } else {
        Serial.println("모터2 반대방향 회전");
        myStepper2.step(steps[next]);
      }
      now2 = next % 8; //현재값 저장
      Serial.print("now2:");
      Serial.println(now2);
      Serial.println("모터2 off 모터3 on");
      motor2 = false; //모터2 off
      motor3 = true; //모터3 on
    } else if (motor3 == true) { //모터3
      next = temp.toInt();
      Serial.print("next:");
      Serial.println(next);

      next = next - now3;  //다음 칸 계산
      Serial.print("계산후next:");
      Serial.println(next);

      if (next >= 0) { //모터 회전
        Serial.println("모터3 정방향 회전");
        myStepper3.step(steps[next]);
      } else {
        Serial.println("모터3 반대방향 회전");
        myStepper3.step(-steps[next]);
      }

      now2 = next % 8; //현재값 저장
      Serial.print("now3:");
      Serial.println(now3);
      Serial.println("모터3 off 모터1 on");
      motor3 = false; //모터3 off
      motor1 = true; //모터1 on
    }

  }//블루투스 연결 여기까지

  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }
}
