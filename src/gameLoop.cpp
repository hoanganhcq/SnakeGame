#include "gameLoop.h"
#include "collision.h"
#include <iostream>

GameLoop::GameLoop() {
    window = NULL;
    renderer = NULL;
    running = false;

    snake = NULL;
    food = NULL;
    terrain = NULL;
    gameData = NULL;
    hud = NULL;
    player = NULL;
    globalFont = NULL;
    menu = NULL;
    pauseButton = NULL;
    homeButton = NULL;
    resumeButton = NULL;
}

bool GameLoop::initialize() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(
        "Snake Game", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WIDTH, HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        running = false;
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    

    // Load all Images
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (!TextureManager::Instance()->loadFromList(renderer, "assets/data/textures.txt")) {
        std::cout << "Failed to load textures!" << std::endl;
        return false;
    }

    // Load Sound Effects
    if (!SoundManager::Instance()->loadFromList("assets/data/sounds.txt")) {
        std::cout << "Failed to load sounds!" << std::endl;
        return false;
    }


    if (TTF_Init() == - 1) {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
    }

    globalFont = TTF_OpenFont("assets/font/PressStart2P-Regular.ttf", 18);
    if (globalFont == NULL) {
        std::cout << "Failed to load globalFont! Error: " << TTF_GetError() << std::endl;
        return false;
    }

    terrain = new Terrain();

    snake = new Snake();

    gameData = new GameData();

    hud = new HUD(globalFont);

    food = new Food();
    food->respawn(terrain, snake);

    player = new Player("Guest", 0);

    menu = new Menu(renderer, WIDTH, HEIGHT, globalFont);

    pauseButton = new Button(renderer, 
                            TextureManager::Instance()->getTexture("btn_pause"),
                            TextureManager::Instance()->getTexture("btn_pause_hover"), 
                            WIDTH - 70, 25, 45, 45
    );

    homeButton = new Button(renderer,
                            TextureManager::Instance()->getTexture("btn_home"),
                            TextureManager::Instance()->getTexture("btn_home_hover"),
                            WIDTH / 2 - 75, HEIGHT / 2 + 40, 45, 45
    );

    resumeButton = new Button(renderer,
                            TextureManager::Instance()->getTexture("btn_resume"),
                            TextureManager::Instance()->getTexture("btn_resume_hover"),
                            WIDTH / 2 + 30, HEIGHT / 2 + 40, 45, 45              
    );


    currentState = GameState::MENU;

    running = true;
    return true;
}


void GameLoop::handleEvents() {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        running = false;
        return;
    }
    
    switch (currentState) {
        case GameState::MENU: 
        {
            int action = menu->handleEvent(&event, renderer);
            playerName = menu->getPlayerName();
            if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) || action == 1) { // Start Game: press ENTER or click Start button
                if (player) delete player;
                player = new Player(playerName, 0);
                std::cout << playerName << " is playing SnakeGame" << std::endl;
                currentState = GameState::PLAYING;
            } 
            else if (action == 2) { // Exit
                running = false;
            }

            break;
        }
        case GameState::PLAYING:
        {
            if (pauseButton->handleEvent(&event)) {
                currentState = GameState::PAUSE;
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_p) {
                    currentState = GameState::PAUSE;
                }
                snake->handleInput(event);
            }
            break;
        }
        case GameState::PAUSE:
        {
            if (homeButton->handleEvent(&event)) {
                currentState = GameState::MENU;
                reset();
            }

            if (resumeButton->handleEvent(&event)) {
                currentState = GameState::PLAYING;
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_p || event.key.keysym.sym == SDLK_RETURN) {
                    currentState = GameState::PLAYING;
                }
            }
            break;
        }
        case GameState::GAME_OVER:
        {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r || event.key.keysym.sym == SDLK_RETURN) {
                    reset();
                    currentState = GameState::PLAYING;
                }
            }
            break;
        }
    }

}


void GameLoop::update() {

    if (currentState == GameState::PLAYING) {

        snake->update();

        if (Collision::check(snake, food)) {
            snake->grow();
            food->respawn(terrain, snake);
            player->setScore(player->getScore() + 10);
            SoundManager::Instance()->playSFX("eat");
        }

        if (Collision::checkSelf(snake)) {
            std::cout << "Game Over: Bitting tail!\n";
            currentState = GameState::GAME_OVER;
            SoundManager::Instance()->playSFX("lose");
        }

        if (Collision::checkTerrain(snake, terrain)) {
            std::cout << "Game Over\n";
            currentState = GameState::GAME_OVER;
            SoundManager::Instance()->playSFX("lose");
        }

        hud->update(player->getScore(), gameData->getBestScore(), renderer);
    }

    if (currentState == GameState::GAME_OVER) {
        if (!player->isSaved()) {
            gameData->updateLeaderBoard(*player);
            player->savedPlayer();
            std::cout << "Attempt recorded: " << player->getName() << ", score: " << std::to_string(player->getScore()) << std::endl;
        }
    }
}


void GameLoop::render() {
    // Clear Screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (terrain) terrain->render(renderer);
    if (snake) snake->render(renderer);
    if (food) food->render(renderer);
    if (hud) hud->render(renderer);

    switch (currentState) {
    case GameState::MENU:
        SDL_RenderClear(renderer);
        menu->render(renderer);
        break;
    case GameState::PLAYING:
        if (pauseButton) pauseButton->render(renderer);
        break;
    case GameState::PAUSE: 
    {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
        SDL_Rect fullscreen_rect = { 0, 0, WIDTH, HEIGHT };
        SDL_RenderFillRect(renderer, &fullscreen_rect);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        homeButton->render(renderer);
        resumeButton->render(renderer);
        break;
    }
    case GameState::GAME_OVER:
        break;
    }

    SDL_RenderPresent(renderer);
}


void GameLoop::reset() {
    delete snake;
    delete food;
    delete player;

    snake = new Snake();
    food = new Food();
    player = new Player(playerName, 0);

    food->respawn(terrain, snake);
    std::cout << "Replay" << std::endl;
}


bool GameLoop::isRunning() {
    return running;
}

void GameLoop::clean() {

    if (globalFont) TTF_CloseFont(globalFont);

    if (snake) {
        delete snake;
        snake = NULL;
    }

    if (terrain) {
        delete terrain;
        terrain = NULL;
    }

    if (gameData) {
        delete gameData;
        gameData = NULL;
    }

    if (hud) {
        delete hud;
        hud = NULL;
    }

    if (player) {
        delete player;
        player = NULL;
    }

    if (menu) {
        delete menu;
        menu = NULL;
    }

    if (pauseButton) {
        delete pauseButton;
        pauseButton = NULL;
    }

    if (homeButton) {
        delete homeButton;
        homeButton = NULL;
    }

    if (resumeButton) {
        delete resumeButton;
        resumeButton = NULL;
    }

    TextureManager::Instance()->clean();

    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    renderer = NULL;
    window   = NULL;

    IMG_Quit();
    SDL_Quit();
}