#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const int WIDTH = 800, HEIGHT = 800, MAX_IT = 100, DEG = 1;
const double MAX_LEN = 2.0;
double x1 = -1.6, y1 = -1.6, x2 = 1.6, y2 = 1.6;
const int R = 255, G = 204, B = 204;
const int dR = 63, dG = 7, dB = 63;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

struct _complex
{
    double a, b;
    _complex(double _a = 0, double _b = 0)
    {
        a = _a;
        b = _b;
    }
    _complex operator * (_complex cur)
    {
        double c = cur.a;
        double d = cur.b;
        double _a = a * d + b * c;
        double _b = b * d - a * c;
        return _complex(_a, _b);
    }
    _complex operator + (_complex cur)
    {
        return _complex(a + cur.a, b + cur.b);
    }
    double get_len()
    {
        return sqrt(a * a + b * b);
    }
};

double get_x(int x)
{
    double res = (double) x * (x2 - x1);
    res /= WIDTH;
    return res + x1;
}

double get_y(int y)
{
    double res = (double) y * (y2 - y1);
    res /= HEIGHT;
    return res + y1;
}

void draw_point(int x, int y, int r, int g, int b){
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(x, y), Color(r, g, b)),
        sf::Vertex(sf::Vector2f(x, y + 1), Color(r, g, b))
    };
    window.draw(line, 2, sf::Lines);
}

void draw_fractal()
{
    for (int i = 0; i < WIDTH; ++i)
        for (int j = 0; j < HEIGHT; ++j)
        {
            int cnt = MAX_IT;
            double x = get_x(i);
            double y = get_y(j);
            _complex z(0, 0), c(y, x);
            for (int it = 0; it < MAX_IT; ++it)
            {
                _complex t = z;
                for (int p = 0; p < DEG; ++p)
                    t = t * z;
                z = t + c;
                if (z.get_len() >= MAX_LEN)
                {
                    cnt = it;
                    break;
                }
            }
            /*if (cnt == MAX_IT)
            {
                draw_point(i, j, 0, 0, 0);
                continue;
            }*/
            int r = (dR - R) * cnt / MAX_IT + R;
            int g = (dG - G) * cnt / MAX_IT + G;
            int b = (dB - B) * cnt / MAX_IT + B;
            draw_point(i, j, r, g, b);
        }
}

int main()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        draw_fractal();
        window.display();
        while (!Mouse::isButtonPressed(Mouse::Left))
        {

        }
        Vector2i position = Mouse::getPosition(window);
        Vector2i position1;
        while (Mouse::isButtonPressed(Mouse::Left))
        {
            position1 = Mouse::getPosition(window);
        }
        double _x1 = get_x(position.x);
        double _y1 = get_y(position.y);
        double _x2 = get_x(position1.x);
        double _y2 = get_y(position1.y);
        x1 = min(_x1, _x2);
        y1 = min(_y1, _y2);
        x2 = max(_x1, _x2);
        y2 = max(_y1, _y2);

    }
    return 0;
}
