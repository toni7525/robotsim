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
    double out = speedvec.x * speedvec.x + speedvec.y * speedvec.y ;
    return sqrt(out);
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
void Robot::move(vec2 size)
{
    pos.x += cos(angle) * size.x - size.y * sin(angle);
    pos.y += size.x * sin(angle) + size.y * cos(angle);
}
void Robot::wheelPower(vec2 wheel, double power)
{
    if (wheel.y == 1) {
        if (wheel.x == 0) {
            FR = power;
        }
        else {
            FL = power;
        }
    }
    else {
        if (wheel.x == 0) {
            BR = power;
        }
        else {
            BL = power;
        }
    }
}
void Robot::UpdateWheels()
{
    double rotspa=0,rotspb=0;
    if ((FR * BL)<0) {
        rotspa = FR / fabs(FR) * fmax(fabs(FR), fabs(BL)) / 2;
        FR += rotspa * 2;
        BL -= rotspa * 2;
        
    }
    if ((BR * FL) < 0) {
        rotspb = FL / fabs(FL) * fmax(fabs(BR), fabs(FL)) / 2;
        FL -= rotspb * 2;
        BR += rotspb * 2;
    }
    rotationspeed = rotspa + rotspb;
    angle += rotationspeed;
    double x = 0.7071 * (BR + FL - FR - BL);
    double y = 0.7071 * (BR + FL + FR + BL);
    pos.x += x * cos(angle) - sin(angle) * y;
    pos.y += x * sin(angle) + cos(angle) * y;
     
    FR = 0;
    FL = 0;
    BR = 0;
    BL = 0;
    rotationspeed = 0;
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

std::string Robot::WheelState()
{
    std::string s1 = std::to_string(FL);
    std::string s2 = std::to_string(FR);
    std::string s3 = std::to_string(BL);
    std::string s4 = std::to_string(BR);
    std::string out = s1+ s2+'\n'+ s3+s4+'\n'+'\n';
    return out;
}
