#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>

void updatePositionAndVelocity(sf::RectangleShape &cube, sf::Vector2f &velocity, float &deltaTime);
void updateColor(sf::RectangleShape &cube, float freq, int phase1, int phase2, int phase3, int center, int width);

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int CUBE_WIDTH = 50;
const int CUBE_HEIGHT = 50;

const float GRAVITY = 9.81f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gravity cube");

    sf::RectangleShape cube(sf::Vector2f(CUBE_WIDTH, CUBE_HEIGHT));
    cube.setFillColor(sf::Color(255, 0, 0));

    cube.setPosition(sf::Vector2f(0, 0));
    sf::Vector2f velocity(2, 0);

    float freq = 0;
    float deltaTime = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        freq += 0.005f; // change how fast you want the colors to change

        updateColor(cube, freq, 0, 2, 4, 128, 127); // regular rainbow
        // updateColor(cube, freq, 0, 2, 4, 230, 25); // pastels

        deltaTime += 0.0001f;

        updatePositionAndVelocity(cube, velocity, deltaTime);

        std::cout << cube.getPosition().y << " " << velocity.y << " " << deltaTime << std::endl;

        // window.clear(); // getting rid of this for cool drawing effect.

        window.draw(cube);

        window.display();
    }

    return 0;
}

void updatePositionAndVelocity(sf::RectangleShape &cube, sf::Vector2f &velocity, float &deltaTime)
{
    sf::Vector2f position = cube.getPosition();

    position += velocity;

    // if it hits the edge, reverse velocity and move the cube back into frame.
    // x position
    if (position.x < 0)
    {
        velocity.x = -velocity.x;
        position.x = 0;
    }
    else if (position.x + CUBE_WIDTH > WINDOW_WIDTH)
    {
        velocity.x = -velocity.x;
        position.x = WINDOW_WIDTH - CUBE_WIDTH;
    }

    // y position
    // v = acceleration * time_delta
    // reseting time_delta when it hits the floor as we want the effect of
    if (position.y < 0)
    {
        velocity.y = -velocity.y;
        position.y = 0;
    }
    else if (position.y + CUBE_HEIGHT > WINDOW_HEIGHT)
    {
        velocity.y = -velocity.y;
        position.y = WINDOW_HEIGHT - CUBE_HEIGHT;
    }

    velocity.y += GRAVITY * deltaTime;

    cube.setPosition(position);
}

// For basic RGB cycling use center 128 and width 127
// Can change the width and center to cover different ranges.
// Do center 230 and width 25 for pastels.
void updateColor(sf::RectangleShape &cube, float freq, int phase1, int phase2, int phase3, int center, int width)
{
    float red = std::sin(freq + phase1) * width + center;
    float green = std::sin(freq + phase2) * width + center;
    float blue = std::sin(freq + phase3) * width + center;

    // std::cout << red << " " << green << " " << blue << std::endl;

    cube.setFillColor(sf::Color(static_cast<sf::Uint8>(red), static_cast<sf::Uint8>(green), static_cast<sf::Uint8>(blue)));
}