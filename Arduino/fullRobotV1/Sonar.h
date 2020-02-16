#include <AFMotor.h>

AF_DCMotor motorLF(1);  //motor setup
AF_DCMotor motorLB(2);
AF_DCMotor motorRB(3);
AF_DCMotor motorRF(4);

class Sonar{
private:
public:
	void awayWall();
	void towardsWall();
	void straight();
}

void Sonar::awayWall(){
  motorLF.setSpeed(lowSpeed);
  motorLB.setSpeed(lowSpeed);
  motorRF.setSpeed(highSpeed+30);
  motorRB.setSpeed(highSpeed+30);
}

void Sonar::towardsWall(){
  motorLF.setSpeed(highSpeed-30);
  motorLB.setSpeed(highSpeed-30);
  motorRF.setSpeed(lowSpeed);
  motorRB.setSpeed(lowSpeed);
}

void Sonar::straight(){
  motorRF.setSpeed(highSpeed);
  motorRB.setSpeed(highSpeed);
  motorLF.setSpeed(highSpeed-40);
  motorLB.setSpeed(highSpeed-40);
}