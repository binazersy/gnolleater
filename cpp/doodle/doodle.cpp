#include <SFML/Graphics.hpp>
#include <time.h>


using namespace sf;


const int W = 400;
const int H = 533;

struct point
{
    int x, y;
};


int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(W, H), "Doodle");
    window.setFramerateLimit(60);

    Texture tb, tp, td;
    tb.loadFromFile("images/background.png");
    tp.loadFromFile("images/platform.png");
    td.loadFromFile("images/doodle.png");

    Sprite sb(tb), sp(tp), sd(td);

    point platform[20];
    for (int i = 0; i <10; i++)
    {
        platform[i].x = rand() % W;
        platform[i].y = rand() % H;
    }

    int x = 100;
    int y = 100;
    int h = 100;
    float dx = 0.0f;
    float dy = 0.0f;

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (Event::Closed == e.type)
                window.close();
            
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;
        
        if (y < h)
        {
            for (int i = 0; i < 10; i++)
            {
                y = h;
                platform[i].y = platform[i].y - dy;
                if (platform[i].y > H - 1)
                {
                    platform[i].y = 0;
                    platform[i].x = rand() % W;
                }
            }
        }


        dy += 0.2f;
        y += dy;
        if (y > 500)
        {
            dy = 0;
            //dy = -10;
        }

        for (int i = 0; i < 10; i++)
        {
            if ((x + 50 > platform[i].x) && (x + 20 < platform[i].x + 68)
                && (y + 70 > platform[i].y) && (y + 70 < platform[i].y + 14) && (dy > 0))
                dy = -10;
        }


        sd.setPosition(x, y);

        window.draw(sb);
        window.draw(sd);
        for (int i = 0; i < 10; i++)
        {
            sp.setPosition(platform[i].x, platform[i].y);
            window.draw(sp);
        }

        window.display();
    }

    return 0;
}