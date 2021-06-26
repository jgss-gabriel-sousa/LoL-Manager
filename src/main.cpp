#include <iostream>
#include "Game.h"
#include "DEFINITIONS.h"
#define _WIN32_WINNT 0x0500
#include <windows.h>

int main(){
    if(SHOW_CONSOLE == 0){
        ShowWindow(GetConsoleWindow(), SW_HIDE);
    }

    try{
        Game(SCREEN_WIDTH,SCREEN_HEIGHT,"LoL Manager");
    }
    catch(std::exception& e){
        std::cout<<"An Exception as occurred: ";
        std::cout << e.what() << std::endl;
        LogWrite();
        return EXIT_FAILURE;
    }

    LogWrite();
    return EXIT_SUCCESS;
}
