
#include "BotLogic.h"

BotLogic bl;

//Bot checks if the pixel has changed or not ever 20 miliseconds
void BotLogic::ColorChange_Arrow(bool& exit_flag, POINT la, COLORREF emptyecolor,  SHORT input,HWND hwND )
{
     while (!exit_flag) {
        HDC hdc = GetDC(hwND);
        COLORREF color = GetPixel(hdc, la.x, la.y);
        if (color != emptyecolor) {
            std::thread t_keypress(&BotLogic::press_key,bl,input);
            std::cout << "Button " << input << " Hit!" << std::endl;
           
            t_keypress.join();
        }
        
        //still adjusting the time 
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        //Good memory managment is always good~ OWO
        ReleaseDC(hwND, hdc);
        
    }


}

void BotLogic::press_key(SHORT virtual_key_code)
{
    INPUT Input = { 0 };
    Input.type = INPUT_KEYBOARD;
    Input.ki.wVk = virtual_key_code;
    SendInput(1, &Input, sizeof(Input));
    ZeroMemory(&Input, sizeof(Input));
    Input.type = INPUT_KEYBOARD;
    Input.ki.wVk = virtual_key_code;
    Input.ki.dwFlags = KEYEVENTF_KEYUP;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    SendInput(1, &Input, sizeof(Input));
    ZeroMemory(&Input, sizeof(Input));
}



