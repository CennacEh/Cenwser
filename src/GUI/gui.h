#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <string>
#include <vector>
#include <cmath>

struct BWindow {
    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
};

struct Tab {
    std::string url;
    std::string html;
    bool loaded;
};

struct Vector2 {
    int x, y;
};

extern std::vector<TTF_Font*> FontsList;
extern BWindow MainWindow;
extern SDL_Cursor* cursor;
extern Tab currentTab;
extern bool isTypingInBar;
extern bool shouldExit;

extern int width;
extern int height;

BWindow InitWindow(int height, int width, const char* title);
bool CleanUp(BWindow windowToDestroy);
bool WindowShouldClose();
void DrawRectangle(BWindow window, int x, int y, int w, int h, int r, int g, int b, int a);
void UpdateCursor(SDL_SystemCursor to);
void UpdateBackground(Uint8 r = 240, Uint8 g = 240, Uint8 b = 240, Uint8 a = 255);
void DrawTextSDL(BWindow window, std::string text, int x, int y, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255, TTF_Font* font = FontsList[0]);
void WaitFrames(int fps = 60);
void RenderBar();
void CleanBWindow(BWindow windowToClean);
void HandleEvents();