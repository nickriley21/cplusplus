#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "SortManager.hpp"

void insertionSort(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[]);

int main()
{
    SortManager manager;

    sf::RenderWindow window(sf::VideoMode(SortManager::WINDOW_WIDTH, SortManager::WINDOW_HEIGHT), "Insertion sort");

    sf::RectangleShape items[SortManager::ARR_LEN];

    manager.createShuffled(window, items);

    insertionSort(manager, window, items);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (sf::RectangleShape item : items)
        {
            window.draw(item);
        }
        window.display();
    }

    return 0;
}

// green for sorted already
// red for current value being inserted
void insertionSort(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[])
{
    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < SortManager::ARR_LEN; i++)
    {
        // insertion swap as you find where it belongs in the sorted list
        int j = i;
        items[i].setFillColor(sf::Color::Red);
        while (j > 0 && items[j].getSize().y < items[j - 1].getSize().y)
        {
            manager.swap(items[j - 1], items[j]);

            items[j].setFillColor(sf::Color::Green);   // value that is now in order
            items[j - 1].setFillColor(sf::Color::Red); // value that is being inserted further
            j--;

            manager.displayItems(window, items);
        }
        items[j].setFillColor(sf::Color::Green);
        items[i].setFillColor(sf::Color::Green);
    }

    manager.displayItems(window, items);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "Time taken for insertion sort: " << duration.count() << " milliseconds" << std::endl;
}