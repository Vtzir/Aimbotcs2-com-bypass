#include "cheat/cheat.h"




int main() { // o seu programa funcional lopp PRINCIPAL

	std::thread Readthread(&Reader::ThreadLoop, &reader);
	Readthread.detach();

	std::thread LoopThread(&Reader::Loopcheat, &reader);// thread do lopp do aimbot 
	LoopThread.detach();

	menu* Menu = new menu();
	Menu->RENDER();

	return 0;
}