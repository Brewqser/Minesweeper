#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int w=10;
int h=10;
int pixel=32;


int main()
{
    RenderWindow app(VideoMode(pixel*(h+2), pixel*(w+2)), "Minesweeper");

    int grid[h+2][w+2];
    int sgrid[h+2][w+2];
    Texture t;
    t.loadFromFile("images/tiles.png");
    Sprite s(t);

    for (int i=1;i<=h;i++) for (int j=1;j<=w;j++) sgrid[i][j]=10;
    for (int i=1;i<=h;i++)
    {
        for (int j=1;j<=w;j++)
        {
            cout << sgrid[i][j] << " ";
        }
        cout << endl;
    }
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
