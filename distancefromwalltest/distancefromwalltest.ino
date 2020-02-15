AF_DCMotor motorLF(1);  //motor setup
AF_DCMotor motorLB(2);
AF_DCMotor motorRB(3);
AF_DCMotor motorRF(4);

int trigPin = 9;
int echoPin = 10;

void towardsWall()
{
  MotorLF.setSpeed(250);
  MotorLB.setSpeed(250);
  MotorRF.setSpeed(225);
  MotorRB.setSpeed(225);
  
}

void awayWall()
{
  MotorRF.setSpeed(225);
  MotorRB.setSpeed(225);
  MotorLF.setSpeed(250);
  MotorLB.setSpeed(250);
}

void straight()
{
  MotorRF.setSpeed(250);
  MotorRB.setSpeed(250);
  MotorLF.setSpeed(250);
  MotorLB.setSpeed(250);
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  MotorRF.setSpeed(250);
  MotorRB.setSpeed(250);
  MotorLF.setSpeed(250);
  MotorLB.setSpeed(250);
  
}

void loop() {
  motorLF.run(FORWARD);
  motorRF.run(FORWARD);
  motorLB.run(FORWARD);
  motorRB.run(FORWARD);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1;
  if (cm > 40)
  {
    towardsWall();
  }
  else if (cm<20)
  {
    awayWall();
  }
  else
  {
    straight();
  }
  }
  
  
}
