#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <iostream>
#include <thread>
#include <chrono>

void createShuffled(sf::RectangleShape items[]);
void swap(sf::RectangleShape &a, sf::RectangleShape &b);

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int ARR_LEN = 50;

const int SLEEP_MILLIS = 1;

const int ITEM_WIDTH = WINDOW_WIDTH / ARR_LEN;
const int ITEM_HEIGHT_DIFF = WINDOW_HEIGHT / ARR_LEN;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Selection sort");

    sf::RectangleShape items[ARR_LEN];

    createShuffled(items);

    int i = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // green for sorted already
        // red for current minimum
        // yellow for being checked against current minimum

        // selection sort
        if (i < ARR_LEN)
        {
            int min = items[i].getSize().y;
            int min_index = i;

            // first value is current min, so make it red
            items[i].setFillColor(sf::Color::Red);

            for (int j = i + 1; j < ARR_LEN; j++)
            {
                items[j].setFillColor(sf::Color::Yellow); // current item being checked is yellow

                if (items[j - 1].getFillColor() != sf::Color::Red) // change previous back to white from yellow, unless it is a red
                {
                    items[j - 1].setFillColor(sf::Color::White);
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLIS));

                if (items[j].getSize().y < min)
                {
                    items[min_index].setFillColor(sf::Color::White);
                    min = items[j].getSize().y;
                    min_index = j;
                    items[min_index].setFillColor(sf::Color::Red);
                }

                window.clear();
                for (sf::RectangleShape item : items)
                    window.draw(item);
                window.display();
            }

            swap(items[i], items[min_index]);                  // swap them
            items[min_index].setFillColor(sf::Color::White);   // minimum index spot is now swapped. go back to white
            items[ARR_LEN - 1].setFillColor(sf::Color::White); // change from yellow back to white.
            items[i].setFillColor(sf::Color::Green);           // sorted, change to green!

            i++;
        }

        window.clear();
        for (sf::RectangleShape item : items)
            window.draw(item);
        window.display();
    }

    return 0;
}

void createShuffled(sf::RectangleShape items[])
{
    // create list
    for (int i = 0; i < ARR_LEN; i++)
    {
        int item_height = (i + 1) * ITEM_HEIGHT_DIFF;
        items[i] = sf::RectangleShape(sf::Vector2f(ITEM_WIDTH, item_height));
        items[i].setPosition(sf::Vector2f(i * ITEM_WIDTH, WINDOW_HEIGHT - item_height));
        items[i].setFillColor(sf::Color::White);
    }

    // shuffle using Fisher-Yates
    srand(time(0));
    for (int i = ARR_LEN - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(items[i], items[j]);
    }
}

void swap(sf::RectangleShape &a, sf::RectangleShape &b)
{
    // swap sizes
    int temp = a.getSize().y;
    a.setSize(sf::Vector2f(ITEM_WIDTH, b.getSize().y));
    b.setSize(sf::Vector2f(ITEM_WIDTH, temp));

    // re-adjust heights
    a.setPosition(sf::Vector2f(a.getPosition().x, WINDOW_HEIGHT - a.getSize().y));
    b.setPosition(sf::Vector2f(b.getPosition().x, WINDOW_HEIGHT - b.getSize().y));
}