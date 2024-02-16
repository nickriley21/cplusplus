#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "SortManager.hpp"

void radixSort(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[]);
int getMax(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[]);
void countingSort(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int exp);

int main()
{
    SortManager manager;

    sf::RenderWindow window(sf::VideoMode(SortManager::WINDOW_WIDTH, SortManager::WINDOW_HEIGHT), "Radix sort");

    sf::RectangleShape items[SortManager::ARR_LEN];

    manager.createShuffled(window, items);

    auto startTime = std::chrono::high_resolution_clock::now();

    radixSort(manager, window, items);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "Time taken for radix sort: " << duration.count() << " milliseconds" << std::endl;

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

void radixSort(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[])
{
    // get max number
    int max = getMax(manager, window, items);

    // counting sort for each digit
    for (int i = 1; max / i > 0; i *= 10)
        countingSort(manager, window, items, i);
}

// set value being inserted to red
// exp is the digit being sorted upon
void countingSort(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int exp)
{
    int i;
    sf::RectangleShape output[SortManager::ARR_LEN];
    int count[10] = {0};

    // store occurences
    for (i = 0; i < SortManager::ARR_LEN; i++)
    {
        count[static_cast<int>(items[i].getSize().y / exp) % 10]++;

        items[i].setFillColor(sf::Color::Red);
        manager.displayItems(window, items);
        items[i].setFillColor(sf::Color::White);
    }

    // store where each value should go in output
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // store values in output
    for (i = SortManager::ARR_LEN - 1; i >= 0; i--)
    {
        int r = static_cast<int>(items[i].getSize().y / exp) % 10;
        count[r]--;
        output[count[r]] = items[i];

        items[i].setFillColor(sf::Color::Red);
        manager.displayItems(window, items);
        items[i].setFillColor(sf::Color::White);
    }

    // store output into items
    for (i = 0; i < SortManager::ARR_LEN; i++)
    {
        // store size and position
        items[i].setSize(sf::Vector2f(SortManager::ITEM_WIDTH, output[i].getSize().y));
        items[i].setPosition(sf::Vector2f(items[i].getPosition().x, output[i].getPosition().y));

        items[i].setFillColor(sf::Color::Red);
        manager.displayItems(window, items);
        items[i].setFillColor(sf::Color::White);
    }
}

// set max to red
int getMax(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[])
{
    int max_index = 0;
    int max = items[0].getSize().y;
    items[0].setFillColor(sf::Color::Red);

    manager.displayItems(window, items);

    for (int i = 0; i < SortManager::ARR_LEN; i++)
    {
        if (items[i].getSize().y > max)
        {
            items[max_index].setFillColor(sf::Color::White);
            max = items[i].getSize().y;

            max_index = i;
            items[max_index].setFillColor(sf::Color::Red);
            manager.displayItems(window, items);
        }
    }
    items[max_index].setFillColor(sf::Color::White);
    return max;
}
