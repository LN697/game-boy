#include "display.hpp"

void InitDisplay() {
    SDL_Init(SDL_INIT_VIDEO);
    DEBUG_INFO("SDL initialized.");
    TTF_Init();
    DEBUG_INFO("TTF initialized.");
    DEBUG_INFO("Display initialized.");
}
void UpdateDisplay() {
    DEBUG_INFO("Display updated.");
}