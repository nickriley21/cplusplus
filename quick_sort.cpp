#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <iostream>
#include <thread>
#include <chrono>
#include "SortManager.hpp"

void quickSort(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int start, int end);
int partition(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int start, int end);

int main()
{
    SortManager manager;

    sf::RenderWindow window(sf::VideoMode(SortManager::WINDOW_WIDTH, SortManager::WINDOW_HEIGHT), "Quick sort");

    sf::RectangleShape items[SortManager::ARR_LEN];

    manager.createShuffled(window, items);

    quickSort(manager, window, items, 0, SortManager::ARR_LEN - 1);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (sf::RectangleShape item : items)
            window.draw(item);
        window.display();
    }

    return 0;
}

void quickSort(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int start, int end)
{
    if (start < end)
    {
        int p = partition(manager, window, items, start, end);

        quickSort(manager, window, items, start, p - 1);
        quickSort(manager, window, items, p + 1, end);
    }
}

// returns index of partition
int partition(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int start, int end)
{
    items[end].setFillColor(sf::Color::Red);
    int low = start - 1;
    for (int i = start; i < end; i++)
    {
        if (items[i].getSize().y < items[end].getSize().y)
        {
            low++;
            manager.swap(items[i], items[low]);
            items[low].setFillColor(sf::Color::Green);
        }
        else
        {
            items[i].setFillColor(sf::Color::Yellow);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(SortManager::SLEEP_MILLIS));
        window.clear();
        for (int j = 0; j < SortManager::ARR_LEN; j++)
            window.draw(items[j]);
        window.display();
    }
    items[end].setFillColor(sf::Color::White);
    manager.swap(items[low + 1], items[end]);

    std::this_thread::sleep_for(std::chrono::milliseconds(SortManager::SLEEP_MILLIS));
    window.clear();
    for (int j = 0; j < SortManager::ARR_LEN; j++)
    {
        window.draw(items[j]);
        if (j <= end && j >= start)
            items[j].setFillColor(sf::Color::White);
    }
    window.display();

    return low + 1;
}