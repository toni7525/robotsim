#include "InputManger.h"

void inputmanager::inputs()
{

}
void inputmanager::moverobot(Robot& rob) {
    x = 0;
    y = 0;
    if (press('A')) {
        x = -power;
    }
    if (press('D')) {
        x = power;
    }
    if (press('S')) {
        y = -power;
    }
    if (press('W')) {
        y = power;
    }
    std::cout << Clamp(x + drift.x, -1, 1);
    std::cout << Clamp(y + drift.y, -1, 1);
    rob.SetSpeed({ Clamp(x + drift.x,-1,1),Clamp(y + drift.y,-1,1) });
}

bool inputmanager::press(int in)
{
    //if (in >= 97 && in <= 122)
    //    in = in - 32;
    if (GetKeyState(in) & 0x8000)
        return true;
    return false;
}
