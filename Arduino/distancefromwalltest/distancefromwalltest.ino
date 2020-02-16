#include <AFMotor.h>


AF_DCMotor motorLF(1);  //motor setup
AF_DCMotor motorLB(2);
AF_DCMotor motorRB(3);
AF_DCMotor motorRF(4);

#define trigPin A5
#define echoPin A4

#define highSpeed 130
#define lowSpeed 100

#define wallDist 30
bool delivery = false;
int missedDelivery = 0;

void motorStop(){
  motorLF.run(RELEASE);
  motorRF.run(RELEASE);
  motorLB.run(RELEASE);
  motorRB.run(RELEASE);
}

void motorForward(){
  motorLF.run(FORWARD);
  motorRF.run(FORWARD);
  motorLB.run(FORWARD);
  motorRB.run(FORWARD);
}

void motorBackward(){
  motorLF.run(BACKWARD);
  motorRF.run(BACKWARD);
  motorLB.run(BACKWARD);
  motorRB.run(BACKWARD);
}

void towardsWall()
{
  motorForward();
  motorLF.setSpeed(highSpeed-30);
  motorLB.setSpeed(highSpeed-30);
  motorRF.setSpeed(lowSpeed);
  motorRB.setSpeed(lowSpeed);
  
}

void awayWall()
{
  motorForward();
  motorLF.setSpeed(lowSpeed);
  motorLB.setSpeed(lowSpeed);
  motorRF.setSpeed(highSpeed+30);
  motorRB.setSpeed(highSpeed+30);
}

void straight()
{
  motorForward();
  motorRF.setSpeed(highSpeed);
  motorRB.setSpeed(highSpeed);
  motorLF.setSpeed(highSpeed-40);
  motorLB.setSpeed(highSpeed-40);
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

bool inByte = false;
void loop() {
  if (Serial.available()) {
    if (Serial.read() != 0){
      inByte = !inByte;
    }
    Serial.print(Serial.read());
    
  }
  if(inByte){
      if (delivery == 1){
      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin,HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin,LOW);
      pinMode(echoPin, INPUT);
      double duration = pulseIn(echoPin, HIGH);
      double cm = (duration/2) / 29.1;
      Serial.println(cm);
      if ((cm > wallDist+5) & (cm<60)) {
        //motorStop();
        if ((missedDelivery % 2) == 0){
          motorForward();
        } else{
          motorBackward();
        }
        towardsWall();
        //Serial.println("Move towards wall");
      } else if (cm < wallDist-5) {
        //motorStop();
        if ((missedDelivery % 2) == 0){
          motorForward();
        } else{
          motorBackward();
        }

        awayWall();
        //Serial.println("Move away from wall");
      } else if(cm >= 60){
        //turn motor around
        missedDelivery = missedDelivery + 1;
      } else{
        if ((missedDelivery % 2) == 0){
          motorForward();
        } else{
          motorBackward();
        }

        straight();
        //Serial.println("Straight");
      }
      
      delay(50);
      motorStop();
      delay(25);
      //straight();
      delay(0);
      }else{
        //this is what happens whenever it has already delivered
      }  
    }else{
      motorStop();
      delay(1000);
    }
}
