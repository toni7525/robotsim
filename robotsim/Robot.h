#pragma once
#include "mymath.h"
#include <string>

class Robot{
public:
    Robot(vec3 start);
    void ResetPos(vec3 res);
    vec3 GetPos();
    vec2 GetSpeedvec();
    double Getspeed();
    vec2 GetAcelerationvec();
    double GetAceleration();
    void Acelerate(vec2 acc);
    void SetSpeed(vec2 setsp);
    void AddSpeed(vec2 add);
    void ChangePos(vec3 to);
    void ChangeError(vec2 in);
    void UpdateSpeed();
    void move(vec2 size);
    void wheelPower(vec2 wheel, double power);
    void UpdateWheels();
    void UpdatePos();
    void UpdateAcceleration();
    void UpdateFriction();
    std::string WheelState();
private:
    double FR=0;
    double FL=0;
    double BR=0;
    double BL=0;
    vec2 pos;
    double mass = 1;
    double angle;
    double frictionCoeficient = 0.14;
    double rotationspeed;
    vec2 speedvec;
    vec2 aceleratonvec;
    vec2 error;
};