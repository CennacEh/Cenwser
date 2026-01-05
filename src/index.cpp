#include <iostream>

#include "GUI/gui.h"
#include "requests/requests.h"
#include "global.h"
#include "other/other.h"

bool error = false;
unsigned int frames = 0;

int main(int argc, char* argv[]) {
    //Initializing stuff
    MainWindow = InitWindow(1024, 512, "Cenwser");
    TTF_Init();
    curl_global_init(CURL_GLOBAL_DEFAULT);
    FontsList.push_back(TTF_OpenFont(".\\resources\\arial.ttf", 24));
    currentTab.url = "https://youtube.com"; 
    currentTab.loaded = false;
    currentTab.html = "";
    ///////////////////
    while (WindowShouldClose() == false) {
        if (error == true) {
            CleanBWindow(MainWindow);
            continue;
        }
        HandleEvents();
        //Updating variables
        SDL_GetWindowSize(MainWindow.sdlWindow, &width, &height);
        ////////////////////
        //Update Background
        //NOTE: MAKE THIS UPGRADE BACKGROUND BASED ON WHAT HTML SAYS, NOT BROWSER DEFAULT!
        UpdateBackground(); 
        if (currentTab.loaded == false) {
            GetResponse get = SendGet(currentTab.url);
            if (get.html == "" || get.html == " ") currentTab.html = "FAILED TO GET WEBSITE";
            else currentTab.html = get.html;
            currentTab.loaded = true;
        }
        DrawTextSDL(MainWindow, currentTab.html, 5, 50, 10, 10, 10, 255, FontsList[0]);
        RenderBar();
        SDL_RenderPresent(MainWindow.sdlRenderer);
        WaitFrames(60);
    };
    CleanUp(MainWindow);
    curl_global_init(CURL_GLOBAL_DEFAULT);
    return 0;
}