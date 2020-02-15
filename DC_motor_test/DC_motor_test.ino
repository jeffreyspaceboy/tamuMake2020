#include <AFMotor.h>

AF_DCMotor motor(1);

void setup() {
  // put your setup code here, to run once:
  motor.setSpeed(100);
  motor.run(RELEASE);
}

void loop() {
  // put your main code here, to run repeatedly:
  motor.run(FORWARD);

  for (int i = 0; i<100; i++)
  {
      motor.setSpeed(i);
      delay(10);
  }

  for (int i = 255; i!= 0; i--)
  {
    motor.setSpeed(i);
    delay(10);

  }

    motor.run(RELEASE);
    delay(1000);

    motor.run(BACKWARD);

  for (int i = 0; i<100; i++)
  {
      motor.setSpeed(i);
      delay(10);
  }

  for (int i = 255; i!= 0; i--)
  {
    motor.setSpeed(i);
    delay(10);

  }

  motor.run(RELEASE);
    delay(1000);

    


  
}
