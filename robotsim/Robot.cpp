#include "Robot.h"
Robot::Robot(vec3 start)
{
    pos.x = start.x;
    pos.y = start.y;
    angle = start.z;
}
void Robot::ResetPos(vec3 res) {
    pos.x = res.x;
    pos.y = res.y;
    angle = res.z;
}
vec3 Robot::GetPos() {
    return{ pos.x,pos.y, angle};
}
vec2 Robot::GetSpeedvec() {
    return speedvec;
}
double Robot::Getspeed() {
    return sqrt(speedvec.x * speedvec.x + speedvec.y * speedvec.y);
}
vec2 Robot::GetAcelerationvec() {
    return aceleratonvec;
}
double Robot::GetAceleration() {
    return sqrt(aceleratonvec.x * aceleratonvec.x + aceleratonvec.y * aceleratonvec.y);
}
void Robot::Acelerate(vec2 acc) {
    aceleratonvec.x += acc.x;
    aceleratonvec.y += acc.y;
}
void Robot::SetSpeed(vec2 setsp) {
    speedvec.x = setsp.x;
    speedvec.y = setsp.y;
}
void Robot::AddSpeed(vec2 add) {
    speedvec.x += add.x;
    speedvec.y += add.y;
}
void Robot::ChangePos(vec3 to) {
    pos.x += to.x;
    pos.y += to.y;
    angle += to.z;
}
void Robot::ChangeError(vec2 in) {

}
void Robot::UpdateSpeed() {
    speedvec.x += aceleratonvec.x;
    speedvec.y += aceleratonvec.y;
}
void Robot::UpdateAcceleration() {

}
void Robot::UpdatePos() {
    pos.x += speedvec.x;
    pos.y += speedvec.y;
}
void Robot::UpdateFriction() {
    if (fabs(speedvec.x) <= mass * mass * frictionCoeficient)
        speedvec.x = 0;
    else speedvec.x -= mass * mass * frictionCoeficient * fabs(speedvec.x) * 1.1 / speedvec.x;
    if (fabs(speedvec.y) <= mass * mass * frictionCoeficient)
        speedvec.y = 0;
    else speedvec.y -= mass * mass * frictionCoeficient * fabs(speedvec.y) * 1.1 / speedvec.y;

}