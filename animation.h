#ifndef ANIMATION_H
#define ANIMATION_H
#include "graphics.h"
#include "game.h"
#include "vector"
#define ii std::pair<int,int>
void animation_move(std::string s2,std::string s,std::vector <std::pair <ii,ii> > v,Graphics &graphics,char request)
{
    ii end_block[20];
    int visited[20];
    int len = v.size();
    if (request == 'U')
    {
        for (int i = 0;i < len;i++)
        {
            int x = v[i].first.first;
            int y = v[i].first.second;
            block[x][y].turnNorth();
        }
    }
    if (request == 'D')
    {
        for (int i = 0;i < len;i++)
        {
            int x = v[i].first.first;
            int y = v[i].first.second;
            block[x][y].turnSouth();
        }
    }
    if (request == 'L')
    {
        for (int i = 0;i < len;i++)
        {
            int x = v[i].first.first;
            int y = v[i].first.second;
            block[x][y].turnWest();
        }
    }
    if (request == 'R')
    {
        for (int i = 0;i < len;i++)
        {
            int x = v[i].first.first;
            int y = v[i].first.second;
            block[x][y].turnEast();
        }
    }
    for (int i = 0;i < len;i++)
    {
        visited[i] = 0;
        int x2 = v[i].second.first;
        int y2 = v[i].second.second;
        end_block[i].first = block[x2][y2].x;
        end_block[i].second = block[x2][y2].y;
        if (block[x2][y2].w == 0)
        {
            end_block[i].first -= 40;
            end_block[i].second -= 40;
        }
    }
    bool check = true;
    while (check == true)
    {
        graphics.prepareScene();
        check = false;
        for (int i = 0;i < len;i++)
        {
            int x = v[i].first.first;
            int y = v[i].first.second;
            int x2 = v[i].second.first;
            int y2 = v[i].second.second;
            int block1_x = block[x][y].x;
            int block1_y = block[x][y].y;
            if (block[x][y].w == 0)
            {
                block1_x -= 40;
                block1_y -= 40;
            }
            if (visited[i] == 0)
            {
                check = true;
                if ((block1_x != end_block[i].first) || (block1_y != end_block[i].second))
                {
                    block[x][y].move();
                }
                else
                {
                    visited[i] = 1;
                    block[x2][y2].img = graphics.cell[board[x2][y2]];
                    block[x2][y2].x = 78 + 80 * (y2 - 1);
                    block[x2][y2].y = 151 + 80 * (x2 - 1);
                    block[x2][y2].w = 80;
                    block[x2][y2].h = 80;
                    block[x][y].x = 78 + 80 * (y - 1) + 40;
                    block[x][y].y = 151 + 80 * (x - 1) + 40;
                    block[x][y].w = 0;
                    block[x][y].h = 0;
                    block[x][y].img = 0;
                }
            }
        }
        render_all(s2,s,graphics,0);
        graphics.presentScene();
    }
}
void shrink_block(std::string s2,std::string s,std::vector<ii> v,Graphics &graphics)
{
    int len = v.size();
    //std::cout << block[v[2].first][v[2].second].w << "\n";
    while (block[v[0].first][v[0].second].w > 0)
    {
        for (int pos = 0;pos < len;pos++)
        {
            int i = v[pos].first;
            int j = v[pos].second;
            if ((block[i][j].w > 0) && (block[i][j].h > 0))
            {
                block[i][j].w -= 5;
                block[i][j].h -= 5;
                block[i][j].x += 2.5;
                block[i][j].y += 2.5;
            }
        }
        render_all(s2,s,graphics,0);
        SDL_Delay(35);
        graphics.presentScene();
    }
    //std::cout << block[v[2].first][v[2].second].w << "\n";
}
void zoom_block(std::string s2,std::string s,std::vector<ii> v,Graphics &graphics)
{
    int len = v.size();
    while (block[v[0].first][v[0].second].w < 80)
    {
        for (int pos = 0;pos < len;pos++)
        {
            int i = v[pos].first;
            int j = v[pos].second;
            if ((block[i][j].w < 80) && (block[i][j].h < 80))
            {
                block[i][j].w += 5;
                block[i][j].h += 5;
                block[i][j].x -= 2.5;
                block[i][j].y -= 2.5;
            }
        }
        render_all(s2,s,graphics,0);
        SDL_Delay(35);
        graphics.presentScene();
    }
    //std::cout << block[v[2].first][v[2].second].x << "\n";
}
void shuffle_game(std::string s2,std::string s,std::vector<ii> v,Graphics& graphics)
{
    std::vector<int> v2;
    shrink_block(s2,s,v,graphics);
    int len = v.size();
    for (int i = 0;i < len;i++)
    {
        v2.push_back(board[v[i].first][v[i].second]);
    }
    bool kt = true;
    for (int i = 1;i <= 4;i++)
    {
        for (int j = 1;j <= 4;j++)
        {
            if (board[i][j] != 0)
            {
                int len2 = v2.size();
                int pos = rand() % len2;
                board[i][j] = v2[pos];
                block[i][j].img = graphics.cell[board[i][j]];
                if (len2 > 1)
                {
                    v2.erase(v2.begin() + pos,v2.begin() + pos + 1);
                }
                else
                {
                    kt = false;
                    break;
                }
            }
        }
        if (kt == false)
        {
            break;
        }
    }
    zoom_block(s2,s,v,graphics);

}
#endif
