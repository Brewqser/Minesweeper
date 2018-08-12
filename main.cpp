#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace sf;
using namespace std;

struct point {int i,j;};

vector <point> V;
int grid[100][100]={0};
int sgrid[100][100]={0};
int w=10;
int h=9;
int pixel=32;
int bombs=20;
int marked=0;
int tilesLeft=0;


//////Reviling tiles ///////
void DFS(int x, int y)
{
    if (sgrid[x][y]==10)
    {
        sgrid[x][y]=grid[x][y];
        tilesLeft--;
        if (sgrid[x][y]==0)
        {
            if (sgrid[x+1][y]!=11) DFS(x+1,y);
            if (sgrid[x-1][y]!=11) DFS(x-1,y);
            if (sgrid[x][y+1]!=11) DFS(x,y+1);
            if (sgrid[x][y-1]!=11) DFS(x,y-1);
            if (sgrid[x+1][y+1]!=11) DFS(x+1,y+1);
            if (sgrid[x-1][y+1]!=11) DFS(x-1,y+1);
            if (sgrid[x+1][y-1]!=11) DFS(x+1,y-1);
            if (sgrid[x-1][y-1]!=11) DFS(x-1,y-1);
        }
    }
}

//////Settings//////
void Settings()
{
    tilesLeft=h*w;
    point p;
    for (int i=1;i<=h;i++) for (int j=1;j<=w;j++) sgrid[i][j]=10;
    for (int i=0;i<=h+1;i++)
    {

        sgrid[0][i]=11;
        sgrid[h+1][i]=11;
    }
    for (int i=0;i<=w+1;i++)
    {

        sgrid[i][0]=11;
        sgrid[i][w+1]=11;
    }
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
}

//////Consol chackout ////////
void Debug()
{
    for (int i=0;i<=h+1;i++)
    {
        for (int j=0;j<=w+1;j++)
        {
            cout << sgrid[i][j] << " ";
        }
        cout << endl;
    }

    for (int i=0;i<=h+1;i++)
    {
        for (int j=0;j<=w+1;j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}


int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(pixel*(w+2), pixel*(h+2)), "Minesweeper");
    Texture t;
    t.loadFromFile("images/tiles.png");
    Sprite s(t);

    Settings();
    Debug();

    ////// Main Loop /////
    while (app.isOpen())
    {
        int tmpy;
        int tmpx;
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed) app.close();

            if (e.type == Event::MouseButtonReleased)
            {
                tmpy=e.mouseButton.x/pixel;
                tmpx=e.mouseButton.y/pixel;
                //cout << tmpx << " " << tmpy << endl;
                if (e.mouseButton.button == Mouse::Left)
                {
                    //sgrid[tmpx][tmpy]=grid[tmpx][tmpy];
                    DFS(tmpx,tmpy);
                }
                if (e.mouseButton.button == Mouse::Right)
                {
                    if (sgrid[tmpx][tmpy]==10)
                    {
                        sgrid[tmpx][tmpy]=11;
                        marked++;
                    }
                    else if (sgrid[tmpx][tmpy]==11)
                    {
                        sgrid[tmpx][tmpy]=10;
                        marked--;
                    }
                }
                //cout << "marked == " << marked << endl;
            }

        }
        app.clear(Color::White);

        for (int i=1;i<=h;i++)
        {
            for (int j=1;j<=w;j++)
            {
                s.setTextureRect(IntRect(sgrid[i][j]*pixel,0,pixel,pixel));
                s.setPosition(j*pixel,i*pixel);
                app.draw(s);
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            Vector2i localPosition = Mouse::getPosition(app);
            s.setTextureRect(IntRect(0,0,pixel,pixel));
            tmpx=localPosition.x/pixel;
            tmpy=localPosition.y/pixel;
            cout << tmpx << " " << tmpy << endl;
            if (tmpx <= h && tmpx >=1 && tmpy >=1 && tmpy <=w && sgrid[tmpy][tmpx]==10)
            {
                s.setPosition(tmpx*pixel,tmpy*pixel);
                app.draw(s);
            }
        }

        if (Mouse::isButtonPressed(Mouse::Right))
        {
            Vector2i localPosition = Mouse::getPosition(app);
            s.setTextureRect(IntRect(11*32,0,pixel,pixel));
            tmpx=localPosition.x/pixel;
            tmpy=localPosition.y/pixel;
            cout << tmpx << " " << tmpy << endl;
            if (tmpx <= h && tmpx >=1 && tmpy >=1 && tmpy <=w && sgrid[tmpy][tmpx]==10)
            {
                s.setPosition(tmpx*pixel,tmpy*pixel);
                app.draw(s);
            }
        }

        app.display();
    }
    return 0;
}
