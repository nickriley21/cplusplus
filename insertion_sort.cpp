#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <iostream>
#include <thread>
#include <chrono>
#include "SortManager.hpp"

int main()
{
    SortManager manager;

    sf::RenderWindow window(sf::VideoMode(SortManager::WINDOW_WIDTH, SortManager::WINDOW_HEIGHT), "Insertion sort");

    sf::RectangleShape items[SortManager::ARR_LEN];

    manager.createShuffled(window, items);

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
        if (i < SortManager::ARR_LEN)
        {
            // insertion swap as you find where it belongs in the sorted list
            int j = i;
            items[i].setFillColor(sf::Color::Red);
            while (j > 0 && items[j].getSize().y < items[j - 1].getSize().y)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(SortManager::SLEEP_MILLIS));

                manager.swap(items[j - 1], items[j]);

                items[j].setFillColor(sf::Color::Green);   // value that is now in order
                items[j - 1].setFillColor(sf::Color::Red); // value that is being inserted further
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