#pragma once
#include<windows.h>
#include<random>
#include"mymath.h"
#include"Robot.h"
#include<iostream>
class inputmanager
{
public:
    vec2 MoveKeys();
    void moverobot(Robot& rob);
    bool press(int in);
    void inputs();
    void MaxDrift(vec2 drif);
private:
    bool End;
    vec2 drift = { 0,0 };
    int x;
    int y;
    double power = 1;
};