#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;


const int M = 20;
const int N = 10;

int field[M][N] = {0, };

struct Point
{
    int x, y;
} a[4], b[4];

int colorNum = 0;

/*
    0 1
    2 3
    4 5 
    6 7
*/

int figures[7][4] =
{
    1, 3, 5, 7,
    2, 4, 5, 7, 
    3, 5, 4, 6,
    3, 5, 4, 7,
    2, 3, 5, 7,
    3, 5, 7, 6,
    0, 1, 2, 3
};


bool check()
{
    for (int i = 0; i < 4; i++)
    {
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return false;
        else if (field[a[i].y][a[i].x]) return false;
    }

    return true;
}


bool newOne(bool sameColor = true)
{
    int n = rand() % 7;
    if (sameColor)
        colorNum = n + 1;
    else
        colorNum = 1 + rand() % 7;

    for (int i = 0; i < 4; i++)
    {
        a[i].x = figures[n][i] % 2 + N / 2;
        a[i].y = figures[n][i] / 2;
    }

    return check();
}


int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), "Tetris");

    Texture tt, tb, tf;
    tt.loadFromFile("images/tiles.png");
    tb.loadFromFile("images/background.png");
    tf.loadFromFile("images/frame.png");

    Sprite s(tt);
    Sprite back(tb);
    Sprite frame(tf);

    int dx = 0;
    bool rotate = false;
    float timer = 0.0f;
    float delay = 0.3f;

    newOne();

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (Event::Closed == e.type)
                window.close();

            if (Event::KeyPressed == e.type)
            {
                switch (e.key.code)
                {
                case Keyboard::Up:
                    rotate = true;
                    break;
                case Keyboard::Left:
                    dx = -1;
                    break;
                case Keyboard::Right:
                    dx = 1;
                    break;
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
            delay = 0.05;

        // left right
        for (int i = 0; i < 4; i++)
        {
            b[i] = a[i];    // back it up
            a[i].x += dx;
        }

        // out of screen, rollback
        if (!check())
        {
            for (int i = 0; i < 4; ++i)
                a[i] = b[i];
        }

        // rotate
        if (rotate)
        {
            Point p = a[1];
            for (int i = 0; i < 4; i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }

            if (!check())
            {
                for (int i = 0; i < 4; ++i)
                    a[i] = b[i];
            }
        }

        // tick
        if (timer > delay)
        {
            for (int i = 0; i < 4; i++)
            {
                b[i] = a[i];
                a[i].y += 1;    // down
            }

            if (!check())
            {
                // settle down
                for (int i = 0; i < 4; i++)
                    field[b[i].y][b[i].x] = colorNum;
                
                newOne();
            }

            timer = 0;
        }

        // check lines, from bottom to top
        int k = M - 1;
        for (int i = M - 1; i > 0; i--)
        {
            int count = 0;
            for (int j = 0; j < N; j++)
            {
                if (field[i][j])
                    count++;
                field[k][j] = field[i][j];
            }
            // if filled(count == N),
            // current line will be overwritten by upper line.
            if (count < N) k--;
        }

        dx = 0;
        rotate = 0;
        delay = 0.3;

        // draw
        window.clear(Color::White);
        window.draw(back);

        // draw fallen
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (0 == field[i][j]) continue;
                s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
                s.setPosition(j * 18, i * 18);
                s.move(28, 31);
                window.draw(s);
            }
        }

        // draw falling(current)
        for (int i = 0; i < 4; i++)
        {
            s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            s.setPosition(a[i].x * 18, a[i].y *18);
            s.move(28, 31);
            window.draw(s);
        }

        window.draw(frame);
        window.display();
    }

    return 0;
}