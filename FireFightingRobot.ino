/*------ Arduino Fire Fighting Robot Code----- */



#include <Servo.h>

  Servo myservo;



  int pos = 0;

  boolean fire = false;



  /*-------defining Inputs------*/

  int forwardSensor = 8;
  int leftSensor = 9;
  int rightSensor = 10;



  /*-------defining Outputs------*/
  int pump = 6;
  int leftMotor1 = 2;
  int leftMotor2 = 3;
  int rightMotor1 = 4;
  int rightMotor2 = 5;
  


    void
    setup()

  {

    pinMode(leftSensor, INPUT);

    pinMode(rightSensor, INPUT);

    pinMode(forwardSensor, INPUT);

    pinMode(leftMotor1, OUTPUT);

    pinMode(leftMotor2, OUTPUT);

    pinMode(rightMotor1, OUTPUT);

    pinMode(rightMotor2, OUTPUT);

    pinMode(pump, OUTPUT);

    Serial.begin(9600);

    myservo.attach(11);

    myservo.write(90);
  }



  void put_off_fire()

  {

    delay(500);



    digitalWrite(leftMotor1, HIGH);

    digitalWrite(leftMotor2, HIGH);

    digitalWrite(rightMotor1, HIGH);

    digitalWrite(rightMotor2, HIGH);



    digitalWrite(pump, HIGH);
    delay(500);



    for (pos = 50; pos <= 130; pos += 1) {

      myservo.write(pos);

      delay(10);
    }

    for (pos = 130; pos >= 50; pos -= 1) {

      myservo.write(pos);

      delay(10);
    }



    digitalWrite(pump, LOW);

    myservo.write(90);



    fire = false;
  }



  void loop()

  {

    myservo.write(90); 


    if (digitalRead(leftSensor) == 1 && digitalRead(rightSensor) == 1 && digitalRead(forwardSensor) == 1)  //If Fire not detected all sensors are one

    {

      //Do not move the robot

      digitalWrite(leftMotor1, LOW);

      digitalWrite(leftMotor2, LOW);

      digitalWrite(rightMotor1, LOW);

      digitalWrite(rightMotor2, LOW);

    }



    else if (digitalRead(forwardSensor) == 0)  //If Fire is straight ahead

    {

      //Move the robot forward

      digitalWrite(leftMotor1, HIGH);

      digitalWrite(leftMotor2, LOW);

      digitalWrite(rightMotor1, HIGH);

      digitalWrite(rightMotor2, LOW);

      fire = true;
      Serial.println("forward");

    }



    else if (digitalRead(leftSensor) == 0)  //If Fire is to the left

    {

      //Move the robot left

      digitalWrite(leftMotor1, LOW);

      digitalWrite(leftMotor2, HIGH);

      digitalWrite(rightMotor1, HIGH);

      digitalWrite(rightMotor2, HIGH);

      Serial.println("left");

    }



    else if (digitalRead(rightSensor) == 0)  //If Fire is to the right

    {

      //Move the robot right

      digitalWrite(leftMotor1, HIGH);

      digitalWrite(leftMotor2, HIGH);

      digitalWrite(rightMotor1, HIGH);

      digitalWrite(rightMotor2, LOW);

      Serial.println("right");
    }

  

    delay(300);  //Slow down the speed of robot



    while (fire == true)

    {

      put_off_fire();
    }
  }
