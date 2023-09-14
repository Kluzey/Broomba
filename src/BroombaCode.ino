// Created By Noah Branley & Julian Langford
// This is an open source non-commercial project. 

#include <AFMotor.h>

// Defines
#define SPEED 150
#define TRIGPIN A0
#define ECHOPIN A1

// Declarations
class Move {
  public:
    void Forward();
    void Backward();
    void Left();
    void Right();
    void Stop();
} Move;

AF_DCMotor motors[4] = {
  AF_DCMotor(1, MOTOR12_1KHZ),
  AF_DCMotor(2, MOTOR12_1KHZ),
  AF_DCMotor(3, MOTOR34_1KHZ),
  AF_DCMotor(4, MOTOR34_1KHZ),
};

// Function Definitions
void
Move::Forward()
{
  for (uint8_t i = 0; i < 4; ++i)
    motors[i].run(FORWARD);
}

void
Move::Backward()
{
  for (uint8_t i = 0; i < 4; ++i)
    motors[i].run(BACKWARD);
}

void
Move::Left()
{
  for (uint8_t i = 0; i < 4; ++i) {
    if (i == 0 || i == 3) 
      motors[i].run(BACKWARD);
    else 
      motors[i].run(FORWARD);
  }
}

void
Move::Right()
{
  for (uint8_t i = 0; i < 4; ++i) {
    if (i == 0 || i == 3)
      motors[i].run(FORWARD);
    else
      motors[i].run(BACKWARD);
  }
}

void
Move::Stop()
{
  for (uint8_t i = 0; i < 4; ++i)
    motors[i].run(RELEASE);
}

int
GetDistance()
{
  int distance;
  long duration;

  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  duration = pulseIn(ECHOPIN, HIGH);
  distance = duration / 29 / 2;

  return distance;
}

void
setup()
{
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  // start delay of 10 seconds.
  delay(10000);
  for (uint8_t i = 0; i < 4; ++i) {
    motors[i].setSpeed(SPEED);
    motors[i].run(RELEASE);
  }
}

void
loop()
{
  if (GetDistance() < 30) {
    Move.Backward();
    delay(500);
    int dir = random(0, 1);
    if(dir) Move.Left();
    else Move.Right();
    delay(random(2000, 10000));
  } else Move.Forward();
}
