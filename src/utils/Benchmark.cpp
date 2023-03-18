#include "Benchmark.h"
#include <Arduino.h>
#include <cmath>
#include "math/Vector3.h"

namespace Benchmark {

static unsigned long t_start_us;

void tick(){
  t_start_us = micros();
}

void tock(const char* msg){
  unsigned long t_total_us = micros()-t_start_us;
  Serial.println(String(msg) + String(": ") + String(t_total_us) + String(" us"));
}

void doMath(){

  {
    Vector3 a(5.0, 10.0, 15.0);
    Vector3 b(10.0, 20.0, 40.0);
    tick();
    Vector3 c = a + b;
    tock("add");
  }

  {
    Vector3 a(5.0, 10.0, 15.0);
    Vector3 b(10.0, 20.0, 40.0);
    tick();
    Vector3 c = a - b;
    tock("sub");
  }
  
  {
    Vector3 a(5.0, 10.0, 15.0);
    Vector3 b(10.0, 20.0, 40.0);
    tick();
    Vector3 c = a * b;
    tock("mul");
  }
    
  {
    Vector3 a(5.0, 10.0, 15.0);
    Vector3 b(10.0, 20.0, 40.0);
    tick();
    Vector3 c = a / b;
    tock("div");
  }
  
  {
    Vector3 a(5.0, 10.0, 15.0);
    Vector3 b(10.0, 20.0, 40.0);
    tick();
    float c = Vector3::dot(a, b);
    tock("dot");
  }
  
  {
    Vector3 a(5.0, 10.0, 15.0);
    tick();
    float c = a.getLength();
    tock("get length");
  }
  
  {
    Vector3 a(5.0, 10.0, 15.0);
    tick();
    float c = a.getSquaredLength();
    tock("get squared length");
  }
  
  {
    Vector3 a(5.0, 10.0, 15.0);
    tick();
    a.setLength(1337.0);
    tock("set length");
  }
  
  {
    Vector3 a(5.0, 10.0, 15.0);
    Vector3 b(10.0, 20.0, 40.0);
    tick();
    float c = Vector3::getDistance(a, b);
    tock("get distance");
  }
    
  {
    tick();
    float a = std::sin(1.0);
    tock("cos");
  }
  
  {
    tick();
    float a = std::acos(0.2);
    tock("acos");
  }
  
  {
    tick();
    float a = std::atan(0.2);
    tock("atan");
  }
  
  {
    tick();
    float a = std::atan2(1.0, 5.0);
    tock("atan2");
  }

}

}