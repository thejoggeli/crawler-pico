#include <Arduino.h>
#include "Robot.h"
#include "Benchmark.h"

Robot robot;

void setup() {
  robot.init();

  Serial.begin(115200);

}

void loop() {

  Vector3 Q = Vector3(0.2, 0.2, -0.2);
  float phi = 0.0f;
  float angles_out[4];
  Benchmark::tick();
  robot.legs[0].ik(Q, phi, angles_out);
  Benchmark::tock("ik");

  delay(5000);

}