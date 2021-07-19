#include<iostream>
#include<thread>
#include<chrono>
#include<Windows.h>



class BotLogic
{
public:
	//Checks if there is a color change for the arrow
	void ColorChange_Arrow(bool& exit_flag, POINT la, COLORREF emptyecolor,SHORT input, HWND hwND);
	//

private:
	void press_key(SHORT virtual_key_code);

};
