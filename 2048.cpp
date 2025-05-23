
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "game.h"
#include "graphics.h"
#include "animation.h"
#define ii std::pair<int,int>
using namespace std;
int combined[5][5],sum_score,cnt_step;
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
bool check_game()
{
    if (cnt_step < 0)
    {
        return false;
    }
    if (sum_score < 0)
    {
        return false;
    }
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            if (board[i][j] == 0)
            {
                return true;
            }
        }
    }
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            if ((board[i][j] == board[i][j + 1]) || (board[i][j] == board[i + 1][j]) || (board[i][j] == board[i][j - 1]) || (board[i][j] == board[i - 1][j]))
            {
                return true;
            }
        }
    }
    return false;
}
void set_up_board(Graphics &graphics)
{
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            if (board[i][j] != 0)
            {
                block[i][j].img = graphics.cell[board[i][j]];
                block[i][j].x = 78 + 80 * (j - 1);
                block[i][j].y = 151 + 80 * (i - 1);
                block[i][j].w = 80;
                block[i][j].h = 80;
            }
            else
            {
                block[i][j].img = 0;
                block[i][j].x = 78 + 80 * (j - 1) + 40;
                block[i][j].y = 151 + 80 * (i - 1) + 40;
                block[i][j].w = 0;
                block[i][j].h = 0;
            }
        }
    }
}
string make_string(int score)
{
    string s;
    for (int i = 1;i <= 8;i++)
    {
        char num = max(0,score % 10) + '0';
        s = num + s;
        score /= 10;
    }
    return s;
}
string make_string2(int step)
{
    string s;
    while(step > 0)
    {
        char num = step % 10 + '0';
        s = num + s;
        step /= 10;
    }
    return s;
}
void find_available(int &i2,int &j2,int i,int j,char request)
{
    int old_i = i;
    int old_j = j;
    if (request == 'U')
    {
        i--;
        while (i >= 1)
        {
            if ((combined[i][j] != 0) || ((board[i][j] != 0) && (board[i][j] != board[old_i][old_j])))
            {
                break;
            }
            i--;
        }
        i++;
    }
    if (request == 'D')
    {
        i++;
        while (i <= 4)
        {
            if ((combined[i][j] != 0) || ((board[i][j] != 0) && (board[i][j] != board[old_i][old_j])))
            {
                break;
            }
            i++;
        }
        i--;
    }
    if (request == 'L')
    {
        j--;
        while (j >= 1)
        {
            if ((combined[i][j] != 0) || ((board[i][j] != 0) && (board[i][j] != board[old_i][old_j])))
            {
                break;
            }
            j--;
        }
        j++;
    }
    if (request == 'R')
    {
        j++;
        while (j <= 4)
        {
            if ((combined[i][j] != 0) || ((board[i][j] != 0) && (board[i][j] != board[old_i][old_j])))
            {
                break;
            }
            j++;
        }
        j--;
    }
    i2 = i;
    j2 = j;
}
void handle(vector <pair <ii,ii> > v,Graphics &graphics,char request)
{
    string s = make_string(sum_score);
    string s2 = make_string2(cnt_step);
    animation_move(s2,s,v,graphics,request);
    set_up_board(graphics);
}
void turnUp(bool &check,Graphics &graphics)
{
    int score = 0;
    vector <pair <ii,ii> > v;
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            combined[i][j] = 0;
        }
    }
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            if (board[i][j] != 0)
            {
                int i2,j2;
                find_available(i2,j2,i,j,'U');
                if ((i2 != i) || (j2 != j))
                {
                    check = true;
                    v.push_back({{i,j},{i2,j2}});
                    if (board[i2][j2] != 0)
                    {
                        board[i2][j2] = board[i][j] + 1;
                        score += pow(2,board[i2][j2]);
                        combined[i2][j2] = 1;
                    }
                    else
                    {
                        board[i2][j2] = board[i][j];
                    }
                    board[i][j] = 0;
                }
            }
        }
    }
    sum_score += score;
    handle(v,graphics,'U');
}
void turnDown(bool &check,Graphics &graphics)
{
    vector <pair <ii,ii> > v;
    int score = 0;
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            combined[i][j] = 0;
        }
    }
    for (int i = 4;i >= 1;i--)
    {
        for (int j = 1;j <= 4;j++)
        {
            if (board[i][j] != 0)
            {
                int i2,j2;
                find_available(i2,j2,i,j,'D');
                if ((i2 != i) || (j2 != j))
                {
                    check = true;
                    v.push_back({{i,j},{i2,j2}});
                    if (board[i2][j2] != 0)
                    {
                        board[i2][j2] = board[i][j] + 1;
                        score += pow(2,board[i2][j2]);
                        combined[i2][j2] = 1;
                    }
                    else
                    {
                        board[i2][j2] = board[i][j];
                    }
                    board[i][j] = 0;
                }
            }
        }
    }
    sum_score += score;
    handle(v,graphics,'D');
}
void turnLeft(bool &check,Graphics &graphics)
{
    vector <pair <ii,ii> > v;
    int score = 0;
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            combined[i][j] = 0;
        }
    }
    for (int j = 1;j <= 4;j++)
    {
        for (int i = 1;i <= 4;i++)
        {
            if (board[i][j] != 0)
            {
                int i2,j2;
                find_available(i2,j2,i,j,'L');
                if ((i2 != i) || (j2 != j))
                {
                    check = true;
                    v.push_back({{i,j},{i2,j2}});
                    if (board[i2][j2] != 0)
                    {
                        board[i2][j2] = board[i][j] + 1;
                        score += pow(2,board[i2][j2]);
                        combined[i2][j2] = 1;
                    }
                    else
                    {
                        board[i2][j2] = board[i][j];
                    }
                    board[i][j] = 0;
                }
            }
        }
    }
    sum_score += score;
    handle(v,graphics,'L');
}
void turnRight(bool &check,Graphics &graphics)
{
    vector <pair <ii,ii> > v;
    int score = 0;
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            combined[i][j] = 0;
        }
    }
    for (int j = 4;j >= 1;j--)
    {
        for (int i = 1;i <= 4;i++)
        {
            if (board[i][j] != 0)
            {
                int i2,j2;
                find_available(i2,j2,i,j,'R');
                if ((i2 != i) || (j2 != j))
                {
                    check = true;
                    v.push_back({{i,j},{i2,j2}});
                    if (board[i2][j2] != 0)
                    {
                        board[i2][j2] = board[i][j] + 1;
                        score += pow(2,board[i2][j2]);
                        combined[i2][j2] = 1;
                    }
                    else
                    {
                        board[i2][j2] = board[i][j];
                    }
                    board[i][j] = 0;
                }
            }
        }
    }
    sum_score += score;
    handle(v,graphics,'R');
}
int find_max_pow()
{
    int max_val = 0;
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            max_val = max(max_val,board[i][j]);
        }
    }
    return max_val;
}
int find_min_pow()
{
    int min_val = 100;
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            min_val = min(min_val,board[i][j]);
        }
    }
    return min_val;
}
void new_block(Graphics &graphics)
{
    int max_pow = find_max_pow();
    int new_i = rand() % 4 + 1;
    int new_j = rand() % 4 + 1;
    while (board[new_i][new_j] != 0)
    {
        new_i = rand() % 4 + 1;
        new_j = rand() % 4 + 1;
    }
    board[new_i][new_j] = 1;
    block[new_i][new_j].img = graphics.cell[board[new_i][new_j]];
    block[new_i][new_j].x = 78 + 80 * (new_j - 1);
    block[new_i][new_j].y = 151 + 80 * (new_i - 1);
    block[new_i][new_j].w = 80;
    block[new_i][new_j].h = 80;
    string s = make_string(sum_score);
    string s2 = make_string2(cnt_step);
    render_all(s2,s,graphics,0);
    graphics.presentScene();
}
void shrink_random(string s2,string s,Graphics &graphics)
{
    int i = rand() % 4 + 1;
    int j = rand() % 4 + 1;
    while (board[i][j] == 0)
    {
        i = rand() % 4 + 1;
        j = rand() % 4 + 1;
    }
    vector<ii>v;
    v.push_back({i,j});
    sum_score -= board[i][j] * pow(2,board[i][j]);
    shrink_block(s2,s,v,graphics);
    board[i][j] = 0;
    block[i][j].img = 0;
}
void zoom_random(string s2,string s,Graphics &graphics)
{
    int i = rand() % 4 + 1;
    int j = rand() % 4 + 1;
    while (board[i][j] != 0)
    {
        i = rand() % 4 + 1;
        j = rand() % 4 + 1;
    }
    vector<ii>v;
    v.push_back({i,j});
    board[i][j] = 1;
    block[i][j].img = graphics.cell[board[i][j]];
    zoom_block(s2,s,v,graphics);
}
bool check_board_full()
{
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            if (board[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}
void running_game(Graphics &graphics)
{
    string s2 = make_string2(cnt_step);
    string s = make_string(sum_score);
    board[rand() % 4 + 1][rand() % 4 + 1] = 1;
    set_up_board(graphics);
    SDL_RenderClear(graphics.renderer);
    render_all(s2,s,graphics,0);
    graphics.presentScene();
    int dem = 0;
    int cnt = 5;
    int k = 6;
    bool kt = false;
    while (check_game() == true)
    {
        bool check = false;
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            break;
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (dem == 5)
        {
            s = make_string(sum_score);
            int p = rand() % 125 + 1;
            if ((p >= 1) && (p <= 25))
            {
                if (kt == true)
                {
                    cnt_step -= cnt;
                    int t = pow(2,(sum_score / 1000));
                    cnt += (k + (sum_score / 400)) * max(t,1);
                    s2 = make_string2(cnt_step);
                    shrink_random(s2,s,graphics);
                }
                else
                {
                    while (p <= 25)
                    {
                        p = rand() % 125 + 1;
                    }
                }
            }
            if (p > 75)
            {
                kt = true;
                if (check_board_full() == false)
                {
                    cnt_step += 4 * find_max_pow();
                    s2 = make_string2(cnt_step);
                    zoom_random(s2,s,graphics);
                }
            }
            if ((p >= 26) && (p <= 75))
            {
                kt = true;
                vector<ii> v;
                for (int i = 1;i <= 4;i++)
                {
                    for (int j = 1;j <= 4;j++)
                    {
                        if (board[i][j] != 0)
                        {
                            v.push_back({i,j});
                        }
                    }
                }
                cnt_step += 4 * find_max_pow();
                s2 = make_string2(cnt_step);
                shuffle_game(s2,s,v,graphics);
            }
            dem = 0;
            continue;
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_UP) turnUp(check,graphics);
            if (event.key.keysym.sym == SDLK_DOWN) turnDown(check,graphics);
            if (event.key.keysym.sym == SDLK_LEFT) turnLeft(check,graphics);
            if (event.key.keysym.sym == SDLK_RIGHT) turnRight(check,graphics);
        }
        if (check == true)
        {
            cnt_step--;
            dem++;
            new_block(graphics);
        }
    }
}
void reset(Graphics &graphics)
{
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            board[i][j] = 0;
            SDL_SetTextureAlphaMod(block[i][j].img, 250);
        }
    }
    SDL_SetTextureAlphaMod(graphics.back_all,250);
    SDL_SetTextureAlphaMod(graphics.back_1,250);
    SDL_SetTextureAlphaMod(graphics.sc_theme,250);
    for (int i = 0;i <= 9;i++)
    {
        SDL_SetTextureAlphaMod(graphics.sc_num[i],250);
    }
    SDL_SetTextureAlphaMod(graphics.sc_word,250);
}
bool game_over(Graphics &graphics)
{
    SDL_Event event;
    string s = make_string(sum_score);
    string s2 = make_string2(cnt_step);
    SDL_RenderClear(graphics.renderer);
    render_all(s2,s,graphics,1);
    graphics.presentScene();
    int x,y;
    while (true)
    {
        SDL_GetMouseState(&x, &y);
        SDL_PollEvent(&event);
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if ((x >= 330) && (x <= 380) && (y >= 350) && (y <= 400))
            {
                return true;
            }
        }
        if (event.type == SDL_QUIT)
        {
            return false;
        }
    }
    return false;
}
int main(int argc, char* argv[])
{
    srand(time(0));
    Graphics graphics;
    graphics.init();
    int start = 0;
    int p = 0;
    SDL_Event event;
    while ((start == 0) || (game_over(graphics) == true))
    {
        sum_score = 0;
        cnt_step = 10;
        reset(graphics);
        start = 1;
        running_game(graphics);
    }
    graphics.quit();
    return 0;
}
