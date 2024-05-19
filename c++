#include <SDL2/SDL.h>
#include <iostream>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Function prototypes
bool init();
bool loadMedia();
void close();
void handleEvents(bool& quit);

// The window we'll be rendering to
SDL_Window* gWindow = nullptr;

// The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    } else {
        // Create window
        gWindow = SDL_CreateWindow("The Eminence in Shadow Color Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        } else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return true;
}

bool loadMedia() {
    // Placeholder function for loading media
    return true;
}

void close() {
    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

void handleEvents(bool& quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        // User requests quit
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        // User presses a key
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_r:
                    SDL_FillRect(gScreenSurface, nullptr, SDL_MapRGB(gScreenSurface->format, 255, 0, 0));
                    break;
                case SDLK_g:
                    SDL_FillRect(gScreenSurface, nullptr, SDL_MapRGB(gScreenSurface->format, 0, 255, 0));
                    break;
                case SDLK_b:
                    SDL_FillRect(gScreenSurface, nullptr, SDL_MapRGB(gScreenSurface->format, 0, 0, 255));
                    break;
                default:
                    SDL_FillRect(gScreenSurface, nullptr, SDL_MapRGB(gScreenSurface->format, 255, 255, 255));
                    break;
            }
        }
    }
}

int main(int argc, char* args[]) {
    // Start up SDL and create window
    if (!init()) {
        std::cout << "Failed to initialize!" << std::endl;
    } else {
        // Load media
        if (!loadMedia()) {
            std::cout << "Failed to load media!" << std::endl;
        } else {
            // Main loop flag
            bool quit = false;

            // While application is running
            while (!quit) {
                // Handle events on queue
                handleEvents(quit);

                // Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}
