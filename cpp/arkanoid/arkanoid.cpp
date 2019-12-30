#include <SFML/Graphics.hpp>
#include <time.h>


using namespace sf;


const int W = 520;
const int H = 450;


bool isCollide(Sprite &s1, Sprite &s2)
{
    return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}


int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(W, H), "Arkanoid");
    window.setFramerateLimit(60);

    Texture tBlock, tBack, tBall, tPaddle;
    tBlock.loadFromFile("images/block01.png");
    tBack.loadFromFile("images/background.jpg");
    tBall.loadFromFile("images/ball.png");
    tPaddle.loadFromFile("images/paddle.png");

    Sprite back(tBack), ball(tBall), paddle(tPaddle);
    paddle.setPosition(300, 440);
    ball.setPosition(300, 420);

    Sprite block[1000];
    int n = 0;
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            block[n].setTexture(tBlock);
            block[n].setPosition(i * 42, j * 20);
            n++;
        }
    }

    float dx = 6;
    float dy = -5;

    bool dead = false;

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (Event::Closed == e.type)
            {
                window.close();
            }
        }

        if (!dead)
        {
            ball.move(dx, 0);
            for (int i =0; i < n; i++)
            {
                if (isCollide(ball, block[i]))
                {
                    block[i].setPosition(-100, 0);
                    dx = -dx;
                    break;
                }
            }

            ball.move(0, dy);
            for (int i =0; i < n; i++)
            {
                if (isCollide(ball, block[i]))
                {
                    block[i].setPosition(-100, 0);
                    dy = -dy;
                    break;
                }
            }

            Vector2f b = ball.getPosition();
            if (b.x < 0 || b.x > W)
                dx = -dx;
            if (b.y < 0)// || b.y > H)
                dy = -dy;
            if (b.y >= H)
                dead = true;

            if (Keyboard::isKeyPressed(Keyboard::Right))
                paddle.move(6, 0);
            if (Keyboard::isKeyPressed(Keyboard::Left))
                paddle.move(-6, 0);

            if (isCollide(paddle, ball))
                dy = -(rand() % 5 + 2);

            window.clear();
            window.draw(back);
            window.draw(ball);
            window.draw(paddle);
            for (int i = 0; i < n; i++)
            {
                window.draw(block[i]);
            }

            window.display();
        }
    }

    return 0;
}