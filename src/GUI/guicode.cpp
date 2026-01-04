#include <stdio.h>

#include "gui.h"
#include "../global.h"

BWindow MainWindow;

std::vector<TTF_Font*> FontsList;
SDL_Cursor* cursor;
Tab currentTab;

Uint32 frameStart = 0;

bool isTypingInBar = false;

int width;
int height;

BWindow InitWindow(int width, int height, const char* title) {
    BWindow window;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        window.sdlRenderer = NULL;
        window.sdlWindow = NULL;
        return window;
    }
    window.sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    window.sdlRenderer = SDL_CreateRenderer(window.sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    return window;
}

bool WindowShouldClose(BWindow window) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return true;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    if (event.window.windowID == SDL_GetWindowID(window.sdlWindow)) {
                        return true;
                    }
                }
                break;
            default:
                break;
        }
    }
    return false;
}

void UpdateCursor(SDL_SystemCursor to) {
    cursor = SDL_CreateSystemCursor(to);
    SDL_SetCursor(cursor);
}

SDL_Point GetMousePosition() {
    SDL_Point MouseLoc;
    SDL_GetMouseState(&MouseLoc.x, &MouseLoc.y);
    return MouseLoc;
}

void DrawRectangle(BWindow window, int x, int y, int w, int h, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(window.sdlRenderer, r, g, b, a);
    SDL_Rect rect = { x, y, h, w };
    SDL_RenderFillRect(window.sdlRenderer, &rect);
}

void DrawCircle(BWindow window, int cx, int cy, int radius, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(window.sdlRenderer, r, g, b, a);
    const int NUM_SEGMENTS = 100; 
    float theta = 2 * M_PI / NUM_SEGMENTS;
    float tangential_factor = tan(theta);
    float radial_factor = cos(theta);

    float x = radius;
    float y = 0;
    for (int i = 0; i < NUM_SEGMENTS; i++) {
        int px = static_cast<int>(cx + x);
        int py = static_cast<int>(cy + y);
        SDL_RenderDrawPoint(window.sdlRenderer, px, py);

        float tx = -y;
        float ty = x;

        x += tx * tangential_factor;
        y += ty * tangential_factor;

        x *= radial_factor;
        y *= radial_factor;
    }
}

//FULL CLEANUP (FOR FULL EXIT)
bool CleanUp(BWindow windowToDestroy) {
    TTF_Quit();
    SDL_DestroyRenderer(windowToDestroy.sdlRenderer);
    SDL_DestroyWindow(windowToDestroy.sdlWindow);
    SDL_Quit();
    shouldExit = true;
    return true;
}

//FOR GETTING RID OF A WINDOW
void CleanBWindow(BWindow windowToClean) {
    SDL_DestroyRenderer(windowToClean.sdlRenderer);
    SDL_DestroyWindow(windowToClean.sdlWindow);
}

void UpdateBackground(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(MainWindow.sdlRenderer, r, g, b, a);
    SDL_RenderClear(MainWindow.sdlRenderer);
}

void DrawTextSDL(BWindow window, std::string text, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, TTF_Font* font) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { r, g, b, a });
    if (!surface) {
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(window.sdlRenderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }
    SDL_Rect loc = { x, y, surface->w, surface->h };
    SDL_RenderCopy(window.sdlRenderer, texture, nullptr, &loc);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void WaitFrames(int fps) {
    if (frameStart == 0) { frameStart = SDL_GetTicks(); }
    else {
        int frameTime = SDL_GetTicks() - frameStart;
        if (1000/fps > frameTime) SDL_Delay(1000/fps - frameTime);
        frameStart = SDL_GetTicks();
        frames++;
    }
}

void RenderBar() {
    DrawRectangle(MainWindow, 0, 0, 50, width, 110, 110, 110, 255);
    DrawRectangle(MainWindow, 10, 10, 30, width-20, 50, 50, 50, 255);
    if (currentTab.loaded == false || isTypingInBar) {
        DrawTextSDL(MainWindow, currentTab.url, 15, 10, 240, 100, 100, 255, FontsList[0]);
    } else DrawTextSDL(MainWindow, currentTab.url, 15, 10, 240, 240, 240, 255, FontsList[0]);
}

void HandleUrlTyping() {
    SDL_Rect bar;
    bar.x = 10;
    bar.y = 10;
    bar.h = 30;
    bar.w = width-20;
    SDL_Point mousePos = GetMousePosition();
    if (SDL_PointInRect(&mousePos, &bar)) {
        UpdateCursor(SDL_SYSTEM_CURSOR_HAND);
        isTypingInBar = true;
    } else {
        UpdateCursor(SDL_SYSTEM_CURSOR_ARROW);
        isTypingInBar = false;
    }
}