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

const int ITEM_WIDTH = WINDOW_WIDTH / ARR_LEN;
const int ITEM_HEIGHT_DIFF = WINDOW_HEIGHT / ARR_LEN;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Insertion sort");

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
        // red for current value being inserted

        // selection sort
        if (i < ARR_LEN)
        {
            // insertion swap as you find where it belongs in the sorted list
            int j = i;
            items[i].setFillColor(sf::Color::Red);
            while (j > 0 && items[j].getSize().y < items[j - 1].getSize().y)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));

                swap(items[j - 1], items[j]);

                items[j].setFillColor(sf::Color::Green); // value that is now in order
                items[j-1].setFillColor(sf::Color::Red); // value that is being inserted further
                j--;

                window.clear();
                for (sf::RectangleShape item : items)
                    window.draw(item);
                window.display();
            }
            items[j].setFillColor(sf::Color::Green);
            items[i].setFillColor(sf::Color::Green);

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