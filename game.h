#ifndef GAME_H
#define GAME_H

#include "graphics.h"
void render(const Block& block,int i,int j,Graphics &graphics,int check) {
    SDL_Rect filled_rect;
    filled_rect.x = block.x;
    filled_rect.y = block.y;
    filled_rect.w = block.w;
    filled_rect.h = block.h;
    if (check == 1)
    {
        SDL_SetTextureBlendMode(block.img, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(block.img, 50);
    }
    SDL_RenderCopy(graphics.renderer, block.img, nullptr, &filled_rect);
}
void render_back(Graphics &graphics,int check)
{
    if (check == 1)
    {
        SDL_SetTextureBlendMode(graphics.back_all, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(graphics.back_all,50);
    }
    SDL_RenderCopy(graphics.renderer, graphics.back_all, NULL, NULL);
    SDL_Rect filled_rect;
    filled_rect.x = 40;
    filled_rect.y = 110;
    filled_rect.w = 400;
    filled_rect.h = 400;
    if (check == 1)
    {
        SDL_SetTextureBlendMode(graphics.back_1, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(graphics.back_1,50);
    }
    SDL_RenderCopy(graphics.renderer, graphics.back_1, nullptr, &filled_rect);
}
void reset_block(int i,int j,Graphics &graphics)
{
    block[i][j].x = 78 + 80 * (j - 1) + 40;
    block[i][j].y = 151 + 80 * (i - 1) + 40;
    block[i][j].img = 0;
}
void render_score(std::string s,Graphics &graphics,int check)
{
    if (check == 1)
    {
        return;
    }
    SDL_Rect filled_rect;
    filled_rect.x = 545;
    filled_rect.y = 20;
    filled_rect.w = 230;
    filled_rect.h = 130;
    if (check == 1)
    {
        SDL_SetTextureBlendMode(graphics.sc_theme, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(graphics.sc_theme,50);
    }
    SDL_RenderCopy(graphics.renderer, graphics.sc_theme, nullptr, &filled_rect);
    for (int i = 0;i <= 7;i++)
    {
         SDL_Rect filled_rect;
         filled_rect.x = 540 + 28 * i;
         filled_rect.y = 100;
         filled_rect.w = 40;
         filled_rect.h = 40;
         int pos = s[i] - '0';
         if (check == 1)
         {
            SDL_SetTextureBlendMode(graphics.sc_num[pos], SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(graphics.sc_num[pos],50);
         }
         SDL_RenderCopy(graphics.renderer, graphics.sc_num[pos], nullptr, &filled_rect);
    }
    filled_rect.x = 510;
    filled_rect.y = 0;
    filled_rect.w = 300;
    filled_rect.h = 100;
    SDL_RenderCopy(graphics.renderer, graphics.sc_word, nullptr, &filled_rect);
}
void render_game_over(std::string s,Graphics& graphics)
{
    SDL_Rect filled_rect;
    filled_rect.x = 150;
    filled_rect.y = 140;
    filled_rect.w = 420;
    filled_rect.h = 320;
    SDL_RenderCopy(graphics.renderer, graphics.go_theme, nullptr, &filled_rect);
    filled_rect.x = 255;
    filled_rect.y = 150;
    filled_rect.w = 200;
    filled_rect.h = 200;
    SDL_RenderCopy(graphics.renderer, graphics.go_word, nullptr, &filled_rect);
    filled_rect.x = 205;
    filled_rect.y = 306;
    filled_rect.w = 140;
    filled_rect.h = 30;
    SDL_RenderCopy(graphics.renderer, graphics.score_word, nullptr, &filled_rect);
    filled_rect.x = 330;
    filled_rect.y = 350;
    filled_rect.w = 50;
    filled_rect.h = 50;
    SDL_RenderCopy(graphics.renderer, graphics.again_theme, nullptr, &filled_rect);
    filled_rect.x = 330;
    filled_rect.y = 350;
    filled_rect.w = 50;
    filled_rect.h = 50;
    SDL_RenderCopy(graphics.renderer, graphics.again_word, nullptr, &filled_rect);
    for (int i = 0;i <= 7;i++)
    {
         SDL_Rect filled_rect;
         filled_rect.x = 350 + 20 * i;
         filled_rect.y = 310;
         filled_rect.w = 30;
         filled_rect.h = 30;
         int pos = s[i] - '0';
         SDL_RenderCopy(graphics.renderer, graphics.sc_num[pos], nullptr, &filled_rect);
    }
}
void render_step(std::string s2,Graphics graphics,int check)
{
    if (check == 1)
    {
        return;
    }
    int len = s2.size();
    for (int i = 0;i < len;i++)
    {
         SDL_Rect filled_rect;
         filled_rect.x = 28 * i;
         filled_rect.y = 0;
         filled_rect.w = 40;
         filled_rect.h = 40;
         int pos = s2[i] - '0';
         SDL_RenderCopy(graphics.renderer, graphics.sc_num[pos], nullptr, &filled_rect);
    }
}
void render_all(std::string s2,std::string s,Graphics& graphics,int check)
{
    render_back(graphics,check);
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            render(block[i][j],i,j,graphics,check);
        }
    }
    render_score(s,graphics,check);
    render_step(s2,graphics,check);
    if (check == 1)
    {
        render_game_over(s,graphics);
    }
}
#endif // GAME_H
