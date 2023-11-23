void move_forward()
{
  Serial.println("forward function called");
  rightservo.writeMicroseconds(mean - wheel_speed);
  leftservo.writeMicroseconds(mean + wheel_speed);
  // delay(500);

}


void stopped()
{
  Serial.println("stop function called");
  rightservo.writeMicroseconds(mean);
  leftservo.writeMicroseconds(mean);
}


void ex_left()
{
  Serial.println("new left function called");
  rightservo.writeMicroseconds(mean + wheel_speed);
  leftservo.writeMicroseconds(mean - reduce_speed);
  //  delay(500);
}

void ex_right()
{
  Serial.println("new right function called");
  rightservo.writeMicroseconds(mean + increase_speed);
  leftservo.writeMicroseconds(mean - wheel_speed);
  //  delay(500);
}

void left()
{
  Serial.println("left function called");
  rightservo.writeMicroseconds(mean - wheel_speed);
  leftservo.writeMicroseconds(mean - wheel_speed);
  //delay(500);
}

void right()
{
  Serial.println("right function called");
  rightservo.writeMicroseconds(mean + wheel_speed);
  leftservo.writeMicroseconds(mean + wheel_speed);
  //delay(500);
}

//To send out ultrasonic pulses and measure the distance
int send_ultrasonic_waves()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;


  return distance;
}
