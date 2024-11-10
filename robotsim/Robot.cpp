#include "Robot.h"
robot::robot(vec3 start)
{
    pos.x = start.x;
    pos.y = start.y;
    angle = start.z;
}
void robot::ResetPos(vec3 res) {
    pos.x = res.x;
    pos.y = res.y;
    angle = res.z;
}
vec3 robot::GetPos() {
    return{ pos.x,pos.y, angle};
}
vec2 robot::GetSpeedvec() {
    return speedvec;
}
double robot::Getspeed() {
    return sqrt(speedvec.x * speedvec.x + speedvec.y * speedvec.y);
}
vec2 robot::GetAcelerationvec() {
    return aceleratonvec;
}
double robot::GetAceleration() {
    return sqrt(aceleratonvec.x * aceleratonvec.x + aceleratonvec.y * aceleratonvec.y);
}
void robot::Acelerate(vec2 acc) {
    aceleratonvec.x += acc.x;
    aceleratonvec.y += acc.y;
}
void robot::SetSpeed(vec2 setsp) {
    speedvec.x = setsp.x;
    speedvec.y = setsp.y;
}
void robot::AddSpeed(vec2 add) {
    speedvec.x += add.x;
    speedvec.y += add.y;
}
void robot::GoTo(vec3 to) {

}
void robot::ChangeError(vec2 in) {

}
void robot::UpdateSpeed() {
    speedvec.x += aceleratonvec.x;
    speedvec.y += aceleratonvec.y;
}
void robot::UpdateAcceleration() {

}
void robot::UpdatePos() {
    pos.x += speedvec.x;
    pos.y += speedvec.y;
}
void robot::UpdateFriction() {
    if (fabs(speedvec.x) <= mass * mass * frictionCoeficient)
        speedvec.x = 0;
    else speedvec.x -= mass * mass * frictionCoeficient * fabs(speedvec.x) * 1.1 / speedvec.x;
    if (fabs(speedvec.y) <= mass * mass * frictionCoeficient)
        speedvec.y = 0;
    else speedvec.y -= mass * mass * frictionCoeficient * fabs(speedvec.y) * 1.1 / speedvec.y;

}