#ifndef _GRAPHICS__H
#define _GRAPHICS__H
#define INITIAL_SPEED 20

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "game.h"
int board[5][5];
struct Block {
    float x, y;
    float dx = 0, dy = 0;
    int w;
    int h;
    int speed = INITIAL_SPEED;
    SDL_Texture *img;
    void move() {
        x += dx;
        y += dy;
    }
    void turnNorth() {
        dy = -speed;
        dx = 0;
    }
    void turnSouth() {
        dy = speed;
        dx = 0;
    }
    void turnWest() {
        dy = 0;
        dx = -speed;
    }
    void turnEast() {
        dy = 0;
        dx = speed;
    }
};
Block block[5][5];
struct Graphics {
    SDL_Renderer *renderer;
	SDL_Window *window;
    SDL_Texture *score_word, *go_word,*go_theme, *again_word, *again_theme, *sc_theme, *sc_word, *sc_num[15], *cell[19], *back_1, *back_all;
	void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

	void initSDL(){
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                   SDL_WINDOW_SHOWN);
        if (window == nullptr)
                   logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1,
                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        //renderer =
                  SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr)
             logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    void init() {
        initSDL();
        cell[0] = loadTexture("img//2.jpg");
        cell[1] = loadTexture("img//2.jpg");
        cell[2] = loadTexture("img//4.jpg");
        cell[3] = loadTexture("img//8.jpg");
        cell[4] = loadTexture("img//16.jpg");
        cell[5] = loadTexture("img//32.jpg");
        cell[6] = loadTexture("img//64.jpg");
        cell[7] = loadTexture("img//128.jpg");
        cell[8] = loadTexture("img//256.jpg");
        cell[9] = loadTexture("img//512.jpg");
        cell[10] = loadTexture("img//1024.jpg");
        cell[11] = loadTexture("img//2048.jpg");
        cell[12] = loadTexture("img//4096.jpg");
        cell[13] = loadTexture("img//8192.jpg");
        cell[14] = loadTexture("img//16384.jpg");
        cell[15] = loadTexture("img//32768.jpg");
        cell[16] = loadTexture("img//65536.jpg");
        cell[17] = loadTexture("img//131072.jpg");
        back_1 = loadTexture("img//back1.jpg");
        sc_num[0] = loadTexture("img//0.png");
        sc_num[1] = loadTexture("img//1.png");
        sc_num[2] = loadTexture("img//2.png");
        sc_num[3] = loadTexture("img//3.png");
        sc_num[4] = loadTexture("img//4.png");
        sc_num[5] = loadTexture("img//5.png");
        sc_num[6] = loadTexture("img//6.png");
        sc_num[7] = loadTexture("img//7.png");
        sc_num[8] = loadTexture("img//8.png");
        sc_num[9] = loadTexture("img//9.png");
        sc_theme = loadTexture("img//scoreboard_theme.jpg");
        sc_word = loadTexture("img//scoreboard_word.png");
        back_all = loadTexture("img//background.jpg");
        go_word = loadTexture("img//game_over.png");
        go_theme = loadTexture("img//game_over_theme.jpg");
        again_word = loadTexture("img//again.jpg");
        again_theme = loadTexture("img//yellow.jpg");
        score_word = loadTexture("img//score_word.png");
        for (int i = 1;i <= 4;i++)
        {
            for (int j = 1;j <= 4;j++)
            {
                    block[i][j].x = 78 + 80 * (j - 1);
                    block[i][j].y = 151 + 80 * (i - 1);
            }
        }
        /*for (int i = 0;i < 3;i++)
        {
            for (int j = 0;j < 3;j++)
            {
                board[i][j] = 0;
            }
        }*/
    }
    void prepareScene()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
	void prepareScene(SDL_Texture * background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
    }
    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }
    void quit()
    {
        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};
#endif // _GRAPHICS__H
