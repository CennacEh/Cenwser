#include "../GUI/gui.h"
#include "../global.h"

void ShowError(std::string error) {
    BWindow errorwin = InitWindow(300, 150, "ERROR");
    
    error = true;
    while (!WindowShouldClose(errorwin)) {
        if (shouldExit) break;
        UpdateBackground();
        DrawRectangle(errorwin, 0, 0, 1280, 1280, 150, 150, 150, 255);
        DrawTextSDL(errorwin, "You fucked up something", 0, 30, 0, 0, 0, 255, FontsList[0]);
        SDL_RenderPresent(errorwin.sdlRenderer);
        WaitFrames(30);
    }
    CleanUp(errorwin);
}