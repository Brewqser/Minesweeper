#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace sf;
using namespace std;

struct point {int i,j;};

vector <point> V;
int w=10;
int h=10;
int pixel=32;
int bombs=20;

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(pixel*(h+2), pixel*(w+2)), "Minesweeper");

    int grid[h+2][w+2]={0};
    int sgrid[h+2][w+2]={0};
    Texture t;
    t.loadFromFile("images/tiles.png");
    Sprite s(t);

    /////settings//////
    point p;
    for (int i=1;i<=h;i++) for (int j=1;j<=w;j++) sgrid[i][j]=10;
    for (int i=1;i<=h;i++)
    {
        for (int j=1;j<=w;j++)
        {
            p.i=j;
            p.j=i;
            V.push_back(p);
        }
    }
    random_shuffle (V.begin(), V.end());
    //for (unsigned int i=0;i<V.size();i++) cout << V[i].y << " " << V[i].x << endl;
    for (int i=0;i<bombs;i++) grid[V[i].i][V[i].j]=9;
    for (int i=1;i<=h;i++)
    {
        for (int j=1;j<=w;j++)
        {
            if (grid[i][j]!=9)
            {
                if(grid[i+1][j]==9)grid[i][j]++;
                if(grid[i-1][j]==9)grid[i][j]++;
                if(grid[i][j+1]==9)grid[i][j]++;
                if(grid[i][j-1]==9)grid[i][j]++;
                if(grid[i+1][j+1]==9)grid[i][j]++;
                if(grid[i+1][j-1]==9)grid[i][j]++;
                if(grid[i-1][j+1]==9)grid[i][j]++;
                if(grid[i-1][j-1]==9)grid[i][j]++;
            }
        }
    }


    ////// Consol chackout ////////
    for (int i=1;i<=h;i++)
    {
        for (int j=1;j<=w;j++)
        {
            cout << sgrid[i][j] << " ";
        }
        cout << endl;
    }

    for (int i=1;i<=h;i++)
    {
        for (int j=1;j<=w;j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }


    ////// Main Loop /////
    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed) app.close();
        }

        app.clear(Color::White);

        for (int i=1;i<=h;i++)
        {
            for (int j=1;j<=w;j++)
            {
                s.setTextureRect(IntRect(sgrid[i][j]*pixel,0,pixel,pixel));
                s.setPosition(i*pixel,j*pixel);
                app.draw(s);
            }
        }

        app.display();
    }
    return 0;
}
