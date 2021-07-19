#include "BotLogic/BotLogic.h"
#include <iostream>
#include<windows.h>

#define left_arrow {734,103}
#define down_arrow {860,103}
#define up_arrow {969,103}
//need to adjust to be less center
#define right_arrow {1104,103}
#define Empty_arrow_color 11379591

int main()
{
	std::cout << "[N1] Get Start Bot" << std::endl;
	std::cout << "[N2] Close Bot Exit" << std::endl;
	std::cout << "[N0] Stop Bot from Running" << std::endl;
	POINT left = left_arrow;
	POINT down = down_arrow;
	POINT up = up_arrow;
	POINT right = right_arrow;

	bool Exit_flag = false;
	POINT origin = { 0,0 };
	RECT rect;
	//not needed  should delte
	//HDC hdcMemory = NULL;
	int width ;
	int height;
	
	BotLogic bl;


	while (TRUE)
	{

		LPCWSTR window = L"Friday Night Funkin'";
		HWND hwND = FindWindow(NULL, window);
		/*if (hdcMemory != NULL)
		{
			DeleteDC(hdcMemory);
		}*/

		//Wait For Game to Load!!!
		while (hwND == NULL)
		{
			HWND hwND = FindWindow(NULL, window);
			std::cout << "Start Game!" << std::endl;
			Sleep(10);
		}

		//Start Bot
		if (GetAsyncKeyState(VK_NUMPAD1))
		{
			Exit_flag = false;
			//bot start up
			std::cout << "Starting Bot!" << std::endl;

			ScreenToClient(hwND, &origin);
			if (GetClientRect(hwND, &rect))
			{
				width = rect.right - rect.left;
				height = rect.bottom - rect.top;

			}

			//Where the magic happens Checks each arrow in a diffrent thread to help speed up processing
			std::thread t_left(&BotLogic::ColorChange_Arrow, bl, std::ref(Exit_flag), left, Empty_arrow_color,  VK_LEFT, hwND);
			std::thread t_down(&BotLogic::ColorChange_Arrow, bl, std::ref(Exit_flag), down, Empty_arrow_color,  VK_DOWN, hwND);
			std::thread t_up(&BotLogic::ColorChange_Arrow, bl, std::ref(Exit_flag), up, Empty_arrow_color,  VK_UP, hwND);
			std::thread t_right(&BotLogic::ColorChange_Arrow, bl, std::ref(Exit_flag), right, Empty_arrow_color,VK_RIGHT, hwND);
			while (true)
			{
				
				if (GetAsyncKeyState(VK_NUMPAD0)) {
					std::cout << "Stoping Bot!" << std::endl;
					Exit_flag = true;

					t_left.join();
					t_down.join();
					t_up.join();
					t_right.join();
					break;
				}




				Sleep(10);
				

			}
			
		}
		if (GetAsyncKeyState(VK_NUMPAD3)) { // Exit
			return 0;
		}

		}

	}



