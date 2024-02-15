#include <SFML/Graphics.hpp>

int main()
{
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    const int CUBE_WIDTH = 50;
    const int CUBE_HEIGHT = 50;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bouncing cube");

    sf::RectangleShape cube(sf::Vector2f(CUBE_WIDTH, CUBE_HEIGHT));
    cube.setFillColor(sf::Color::Red);

    sf::Vector2f position(100, 100);
    sf::Vector2f velocity(2, 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        position += velocity;

        if (position.x < 0 || position.x + CUBE_WIDTH > WINDOW_WIDTH)
            velocity.x = -velocity.x;
        if (position.y < 0 || position.y + CUBE_HEIGHT > WINDOW_HEIGHT)
            velocity.y = -velocity.y;

        cube.setPosition(position);

        window.clear();

        window.draw(cube);

        window.display();
    }

    return 0;
}