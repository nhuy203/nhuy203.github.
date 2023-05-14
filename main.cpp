#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int GRID_ROWS = 6;
const int GRID_COLS = 10;

const char *START_IMAGE = "start.jpg";
const char *WIN_IMAGE = "win.jpg";
const char *PKM_IMAGE_PREFIX = "pkm";
const char *PKM_IMAGE_EXTENSION = ".jpg";

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
SDL_Surface *gScreenSurface = nullptr;
SDL_Texture *gBackgroundTexture = nullptr;
TTF_Font *gFont = nullptr;

struct Animal {
    SDL_Texture *texture;
    SDL_Rect rect;
    int animalId;
    bool visible;

    Animal() : texture(nullptr), animalId(-1), visible(true) {}
};

std::vector<Animal> gAnimals;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    gWindow = SDL_CreateWindow("Pikachu Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    int imgFlags = IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

SDL_Texture *loadTexture(const std::string &path) {
    SDL_Texture *newTexture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! IMG_Error: " << IMG_GetError() << std::endl;
    } else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cerr << "Unable to create texture from " << path << "! SDL_Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void close() {
    for (auto &animal : gAnimals) {
        SDL_DestroyTexture(animal.texture);
    }
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void generateAnimalRects() {
    int cellWidth = SCREEN_WIDTH / GRID_COLS;
    int cellHeight = SCREEN_HEIGHT / GRID_ROWS;

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            Animal animal;
            animal.rect.x = j * cellWidth;
            animal.rect.y = i * cellHeight;
            animal.rect.w = cellWidth;
            animal.rect.h = cellHeight;
            gAnimals.push_back(animal);
        }
    }
}

void loadAnimalTextures() {
    std::vector<int> animalIds(GRID_ROWS * GRID_COLS);
    for (int i = 0; i < GRID_ROWS * GRID_COLS; i++) {
        animalIds[i] = i % 10;
    }
    std::shuffle(animalIds.begin(), animalIds.end(), std::default_random_engine(std::random_device{}()));

    for (int i = 0; i < GRID_ROWS * GRID_COLS; i++) {
        std::string imagePath = PKM_IMAGE_PREFIX + std::to_string(animalIds[i] + 1) + PKM_IMAGE_EXTENSION;
        gAnimals[i].texture = loadTexture(imagePath);
       gAnimals[i].animalId = animalIds[i];
    }
}

void renderAnimals() {
    SDL_RenderCopy(gRenderer, gBackgroundTexture, nullptr, nullptr);
    for (const auto &animal : gAnimals) {
        if (animal.visible) {
            SDL_RenderCopy(gRenderer, animal.texture, nullptr, &animal.rect);
        }
    }
}

int findClickedAnimal(int x, int y) {
    for (int i = 0; i < static_cast<int>(gAnimals.size()); i++) {
        SDL_Point tmpPoint = {x, y};
        if (gAnimals[i].visible && SDL_PointInRect(&tmpPoint, &gAnimals[i].rect)) {
            return i;
        }
    }
    return -1;
}

bool checkWin() {
    for (const auto &animal : gAnimals) {
        if (animal.visible) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *args[]) {
    if (!init()) {
        std::cerr << "Failed to initialize!" << std::endl;
        return 1;
    }

    bool quit = false;
    bool gameStarted = false;
    bool gameWon = false;
    SDL_Event e;

    int firstClickedAnimal = -1;
    int secondClickedAnimal = -1;
    gBackgroundTexture = loadTexture("bgroud.jpg");
    generateAnimalRects();
    loadAnimalTextures();

    SDL_Texture *startTexture = loadTexture(START_IMAGE);
    SDL_Texture *winTexture = loadTexture(WIN_IMAGE);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (!gameStarted) {
                    gameStarted = true;
                } else if (!gameWon) {
                    int clickedAnimal = findClickedAnimal(x, y);
                    if (clickedAnimal != -1) {
                        if (firstClickedAnimal == -1) {
                            firstClickedAnimal = clickedAnimal;
                        } else if (secondClickedAnimal == -1) {
                            if (clickedAnimal != firstClickedAnimal) {
                                secondClickedAnimal = clickedAnimal;
                                if (gAnimals[firstClickedAnimal].animalId == gAnimals[secondClickedAnimal].animalId) {
                                    gAnimals[firstClickedAnimal].visible = false;
                                    gAnimals[secondClickedAnimal].visible = false;
                                }
                                firstClickedAnimal = -1;
                                secondClickedAnimal = -1;
                            } else {
                                firstClickedAnimal = -1;
                            }
                        }
                    }
                }
            }
        }

        SDL_RenderClear(gRenderer);

        if (!gameStarted) {
            SDL_RenderCopy(gRenderer, startTexture, nullptr, nullptr);
        } else if ((gameWon = checkWin())) {
            SDL_RenderCopy(gRenderer, winTexture, nullptr, nullptr);
        } else {
            renderAnimals();
        }

        SDL_RenderPresent(gRenderer);
    }

    SDL_DestroyTexture(startTexture);
    SDL_DestroyTexture(winTexture);
    SDL_DestroyTexture(gBackgroundTexture);
    close();

    return 0;
}