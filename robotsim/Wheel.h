#pragma once
#include "Robot.h"
class wheel {
	Robot *parent;
	vec2 pos;
public:
	wheel(Robot *inrob,vec2 pos) :parent(inrob),pos(pos) {};
	void setPower(double power) {
		parent->wheelPower(pos, power);
	}
private:

};