/*
   This Code written by Ahmed Shelbaya
   Founder of A.Shelbaya inc
   Main Code Function is Avoid Obstacles Robot
   Using Arduino UNO , Motor Shield V.1 and 3 Ultrasonic
*/
#include <AFMotor.h> //Add Motor Driver Libiry 
AF_DCMotor MFR(2, MOTOR12_64KHZ); //Connect Front Right Motor to Terminal M2 in Motor Shield
AF_DCMotor MFL(3, MOTOR34_64KHZ); //Connect Front Left  Motor to Terminal M3 in Motor Shield
AF_DCMotor MBR(1, MOTOR12_64KHZ); //Connect Back  Right Motor to Terminal M1 in Motor Shield
AF_DCMotor MBL(4, MOTOR34_64KHZ); //Connect Back  Left  Motor to Terminal M4 in Motor Shield
//Define Variables to store Ultrasonic Reading
int RU;
int CU;
int LU;
//Create Function to modify Ultraonic Reading if less than Zero to avoid any errors
int MinDistance(int Distance)
{
  if (Distance < 0)
  {
    Distance = 5;
  }
  return Distance;
}
//Create Function to modify Ultraonic Reading if more than 200 Cm as a Max Range
int MaxDistance(int Distance)
{
  if (Distance > 200)
  {
    Distance = 200;
  }
  return Distance;
}
void setup()
{
  // Determine Motor Speed
  MFR.setSpeed(255);
  MFL.setSpeed(255);
  MBR.setSpeed(255);
  MBL.setSpeed(255);
  Serial.begin(9600); // Start Serial Communication for Debuging only
}
void loop()
{
  // Call Ultrasonic Function which we made belw
  // Frist argument is Trig , Second is Echo
  RU = Ultrasonic(A0, A1);
  CU = Ultrasonic(A2, A3);
  LU = Ultrasonic(A4, A5);
  //calling Range Lock Function
  /* RU = MinDistance(RU);
    CU = MinDistance(CU);
    LU = MinDistance(LU);
    RU = MaxDistance(RU);
    CU = MaxDistance(CU);
    LU = MaxDistance(LU);*/
  //Debuging
  Serial.print("Right Ultrasonic: ");
  Serial.println(RU);
  Serial.print("Center Ultrasonic: ");
  Serial.println(CU);
  Serial.print("left Ultrasonic: ");
  Serial.println(LU);
  delay(10);
  //Check if Forward Direction are Clear
  if (CU < 12)
  {
    Right();
  }
  //Check if Left Direction Are Clear
  else if (RU < LU && CU < LU)
  {
    Left();
    Serial.println("Left");
  }
  //Check if Right Direction Are Clear

  else if (LU < RU && CU < RU)
  {
    Right();
    Serial.println("Right");
  }
  //Check if forward Direction Are Clear

  else if (RU == CU && CU == LU)
  {
    Forward();
  }
  // Moving in Forward as Defualt
  else
  {
    Forward();
  }
}
// Ultrasonic Function
int Ultrasonic(int Trig, int Echo)
{
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trig, LOW);
  delayMicroseconds(10);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  int Duration = pulseIn(Echo, HIGH);
  int Distance = Duration / 58.2;
  return Distance;
}
//Movments Functions
void Forward()
{
  MFR.run(FORWARD);
  MFL.run(FORWARD);
  MBR.run(FORWARD);
  MBL.run(FORWARD);

}
void Backword()
{
  MFR.run(BACKWARD);
  MFL.run(BACKWARD);
  MBR.run(BACKWARD);
  MBL.run(BACKWARD);

}
void Right()
{
  MFR.run(BACKWARD);
  MFL.run(FORWARD);
  MBR.run(BACKWARD);
  MBL.run(FORWARD);
}
void Left()
{
  MFR.run(FORWARD);
  MFL.run(BACKWARD);
  MBR.run(FORWARD);
  MBL.run(BACKWARD);
}
void STOP()
{
  MFR.run(RELEASE);
  MFL.run(RELEASE);
  MBR.run(RELEASE);
  MBL.run(RELEASE);
}
