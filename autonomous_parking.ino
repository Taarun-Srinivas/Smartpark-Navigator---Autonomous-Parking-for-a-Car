#include <Servo.h>

long unsigned start_time;
long unsigned end_time;

Servo leftservo;
Servo rightservo;

const int mean = 1500;
const int wheel_speed = 80;
const int increase_speed = wheel_speed + 70;
const int reduce_speed = wheel_speed + 60;

int intersection_counter = 0;
int obstacle_counter = 0;

int IR1 = 8;
int IR_val1 = 0;

int IR2 = 9;
int IR_val2 = 0;

int IR3 = 10;
int IR_val3 = 0;

const int trigPin = 7;
const int echoPin = 6;

const int obstacleLed = 11;
const int intersectionLed = 12;


long duration;
int distance;
int dist_;

bool ultra_flag = 0;
bool spots[2] = {0, 0}; //[0] -> right, [1] -> left


void setup() {
  leftservo.attach(2);

  rightservo.attach(4);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(obstacleLed, OUTPUT);
  pinMode(intersectionLed, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  IR_val1 = digitalRead(IR1);
  IR_val2 = digitalRead(IR2);
  IR_val3 = digitalRead(IR3);

  Serial.print(String(IR_val1) + "  " + String(IR_val2) + "  " + String(IR_val3) + "  " + String(ultra_flag) + "  " + String(intersection_counter) + "  " + String(spots[0]) + "  " + String(spots[1]) + "\t\t" );


  if (ultra_flag)
  {
    Serial.println("sending out ultrasonic signals");
    dist_ = send_ultrasonic_waves();
    Serial.println("distance is " + String(dist_));
    start_time = millis();
    if (dist_ < 20 && intersection_counter == 1)
    {
      digitalWrite(obstacleLed, HIGH);
      delay(3000);
      obstacle_counter += 1;
      Serial.println("Obstacle detected" + String(obstacle_counter));
      spots[0] = 1;
    }

    else if (dist_ < 20 && intersection_counter == 4)
    {
      digitalWrite(obstacleLed, HIGH);
      delay(3000);
      obstacle_counter += 1;
      
      Serial.println("Obstacle detected" + String(obstacle_counter));
      spots[1] = 1;
    }
    else
    {
      digitalWrite(obstacleLed, LOW);
    }
  }
  else
  {
    digitalWrite(obstacleLed, LOW);
  }

  if (IR_val1 == 1 && IR_val2 == 1 && IR_val3 == 1)  // At intersection
  {
    Serial.println("intersection detected  " + String(intersection_counter));
    move_forward();
    delay(100);
    stopped();
    intersection_counter++;

    //Newly added code begins here
    if (intersection_counter == 1)
    {

      digitalWrite(intersectionLed, HIGH);
      delay(1500);
      digitalWrite(intersectionLed, LOW);
      // Serial.println(" intersection  detected");
      move_forward();
      delay(100);
      right();
      delay(850);
      
//      do
//      {
//        IR_val1 = digitalRead(IR1);
//        IR_val2 = digitalRead(IR2);
//        IR_val3 = digitalRead(IR3);
//      } while (!(IR_val1 == 0 && IR_val2 == 1 && IR_val3 == 0));
      ultra_flag = 1;
    }

    else if (intersection_counter == 2)
    {
      ultra_flag = 0;

      digitalWrite(intersectionLed, HIGH);
      delay(1500);
      digitalWrite(intersectionLed, LOW);

      // Serial.println("this the counter 2 counter loop bot has entered here" + String(intersection_counter));
      // stopped();
      // delay(100);
      right();
      delay(2100);
    }

    else if (intersection_counter == 3)
    {
      ultra_flag = 0;

      digitalWrite(intersectionLed, HIGH);
      delay(1000);
      digitalWrite(intersectionLed, LOW);

      // Serial.println("this the counter 3 counter loop bot has entered here" + String(intersection_counter));
      // intersection_counter++;
      stopped();
      delay(100);
      move_forward();
      delay(100);

    }

    else if (intersection_counter == 4)
    {
      // dist_ = send_ultrasonic_waves();
      // if (dist_ < 10)
      // {
      //   obstacle_counter += 1;
      // }

      digitalWrite(intersectionLed, HIGH);
      delay(1500);
      digitalWrite(intersectionLed, LOW);

      // Serial.println("this the counter 4 counter loop bot has entered here" + String(intersection_counter));
      // stopped();
      // delay(100);
      right();
      delay(1900);
      ultra_flag = 1;

    }

    else if (intersection_counter == 5)
    {
      ultra_flag = 0;

      digitalWrite(intersectionLed, HIGH);
      delay(1500);
      digitalWrite(intersectionLed, LOW);

      stopped();
      delay(200);

      move_forward();
      delay(250);

      left();
      delay(900);
      // Serial.println("this the counter 5 counter loop bot has entered here" + String(intersection_counter));
      // do {
      //   left();
      //   delay(350);
      //   IR_val1 = digitalRead(IR1);
      //   IR_val2 = digitalRead(IR2);
      //   IR_val3 = digitalRead(IR3);
      //   // Serial.println(String(IR_val1)+"   "+String(IR_val2)+"   "+String(IR_val3));
      // } while (!(IR_val1 == 0 && IR_val2 == 1 && IR_val3 == 0));
      // Serial.println("out of while 2");
      // intersection_counter++
    }

    else if (intersection_counter == 6)
    {
      digitalWrite(intersectionLed, HIGH);
      delay(1500);
      digitalWrite(intersectionLed, LOW);

      stopped();
      delay(200);
      move_forward();
      delay(200);

      if (spots[0] == 1 && spots[1] == 0)
      {
        left(); 
        delay(500);
        if (IR_val1 == 1 && IR_val2 == 1 && IR_val3 == 1)
        {
          stopped();
        }
      }

      else if (spots[0] == 0 && spots[1] == 1)
      {
        right();
        delay(600);
        if (IR_val1 == 1 && IR_val2 == 1 && IR_val3 == 1)
        {
          stopped();
        }
      }

      else if (spots[0] == 1 && spots[1] == 1)
      {
        move_forward();
        intersection_counter = 0;
        spots[0] = 0;
        spots[1] = 0;
      }

      else if (spots[0] == 0 && spots[1] == 0)
      {
        right();
        delay(500);
        if (IR_val1 == 1 && IR_val2 == 1 && IR_val3 == 1)
        {
          stopped();
        }
      }


    }
  }

  else if (IR_val2 == 1)  // to move forward
  {
    move_forward();
  }

  else if (IR_val1 == 1)  // Take left turn
  {
    right();
    //left();
  }

  else if (IR_val3 == 1)  //Take right turn
  {
    left();
    //right();
  }

  else if (IR_val2 == 1 && IR_val3 == 1)
  {
    ex_right();
  }

  else if (IR_val2 == 1 && IR_val1 == 1)
  {
    ex_left();
  }

  else {
    stopped();
    delay(1000);
  }

}
