#include "BotLogic/BotLogic.h"
#include <iostream>
#include<windows.h>
#include<vector>
#include "FNF pixelBot.h"

#define left_arrow {734,103}
#define down_arrow {860,103}
#define up_arrow {969,103}
#define right_arrow {1081,103}




int main()
{
	std::cout << "[N1] Get Start Bot" << std::endl;
	std::cout << "[N2] Close Bot Exit" << std::endl;
	std::cout << "[N0] Stop Bot from Running" << std::endl;

	POINT left = left_arrow;
	POINT down = down_arrow;
	POINT up = up_arrow;
	POINT right = right_arrow;
	LPCWSTR w[4] = { L"Friday Night Funkin'", L"Friday Night Funkin' Kade Engine",L"High Effort Ugh",L"Friday Night Funkin': Mid-Fight Masses - Selever Edition"};
	bool Exit_flag = false;
	POINT origin = { 0,0 };
	RECT rect;
	//not needed  should delte
	//HDC hdcMemory = NULL;
	int width ;
	int height;
	HWND hwND = NULL;
	BotLogic bl;


	while (TRUE)
	{

		//Wait For Game to Load!!!
		while (hwND == NULL)
		{
			for (LPCWSTR n : w) {


				HWND hwND = (FindWindow(NULL, n));
				

				
				if(hwND != NULL)
				{
					std::cout << "Bot is Ready to start" << std::endl;
					
					bl.Bot(Exit_flag, bl, left, hwND, down, up, right);
					
				}
				std::cout << "Start Game" << std::endl;
				Sleep(100);
			}
			break;
			
		}


		
		if (GetAsyncKeyState(VK_NUMPAD3))
		{ // Exit
			return 0;
		}

		}

	}




