#include<iostream>
#include<thread>
#include<chrono>
#include<map>
#include<string>
#include<Windows.h>

#define Empty_arrow_color 11379591

class BotLogic
{
public:
	//The main bot method
	void Bot(bool& Exit_flag, BotLogic& bl, POINT& left, HWND& hwND, POINT& down, POINT& up, POINT& right);
	//

private:
	//key map
	std::map<int, std::string> arrowkeys = 
	{ 
		{37,"left"},
		{ 39,"right"},
		{ 38,"up"},
		{ 40,"down"} 
	};
	//predd keys
	void press_key(SHORT virtual_key_code);
	//Checks if there is a color change for the arrow
	void ColorChange_Arrow(bool& exit_flag, POINT la, COLORREF emptyecolor, SHORT input, HWND hwND);

};
