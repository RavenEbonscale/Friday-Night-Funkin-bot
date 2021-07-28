
#include "BotLogic.h"

BotLogic bl;

//Bot checks if the pixel has changed or not ever 10 miliseconds
void BotLogic::ColorChange_Arrow(bool& exit_flag, POINT la, COLORREF emptyecolor,  SHORT input,HWND hwND )
{
     while (!exit_flag) {
        HDC hdc = GetDC(hwND);
        COLORREF color = GetPixel(hdc, la.x, la.y);
        if (color != emptyecolor) {
            std::thread t_keypress(&BotLogic::press_key,bl,input);
			//still adjusting the time 
			
            std::cout << "Button " << arrowkeys[input]  << " Hit!" << std::endl;
           
            t_keypress.join();
			std::this_thread::sleep_for(std::chrono::milliseconds(20));

        }
        
       

        //Good memory managment is always good~ OWO
        ReleaseDC(hwND, hdc);
        
    }


}

void BotLogic::Bot(bool& Exit_flag, BotLogic& bl, POINT& left, HWND& hwND, POINT& down, POINT& up, POINT& right)
{
	while (true) {
		if (GetAsyncKeyState(VK_NUMPAD1))
		{
			
			Exit_flag = false;
			//bot start up
			std::cout << "Starting Bot!" << std::endl;

			//Where the magic happens Checks each arrow in a diffrent thread to help speed up processing
			std::thread t_left(&BotLogic::ColorChange_Arrow, bl, std::ref(Exit_flag), left, Empty_arrow_color, VK_LEFT, hwND);
			std::thread t_down(&BotLogic::ColorChange_Arrow, bl, std::ref(Exit_flag), down, Empty_arrow_color, VK_DOWN, hwND);
			std::thread t_up(&BotLogic::ColorChange_Arrow, bl, std::ref(Exit_flag), up, Empty_arrow_color, VK_UP, hwND);
			std::thread t_right(&BotLogic::ColorChange_Arrow, bl, std::ref(Exit_flag), right, Empty_arrow_color, VK_RIGHT, hwND);
			while (true)
			{

				if (GetAsyncKeyState(VK_NUMPAD0)) {
					std::cout << "Stoping Bot!" << std::endl;
					Exit_flag = true;

					t_left.join();
					t_down.join();
					t_up.join();
					t_right.join();
					ReleaseDC(hwND, NULL);
					break;
				}




				Sleep(10);


			}


		}
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
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    SendInput(1, &Input, sizeof(Input));
    ZeroMemory(&Input, sizeof(Input));
}



