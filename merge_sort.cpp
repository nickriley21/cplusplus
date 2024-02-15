#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <iostream>
#include <thread>
#include <chrono>
#include "SortManager.hpp"

void mergeSort(sf::RenderWindow &window, sf::RectangleShape items[], int start, int end);
void merge(sf::RenderWindow &window, sf::RectangleShape items[], int start, int middle, int end);

int main()
{
    SortManager manager;

    sf::RenderWindow window(sf::VideoMode(SortManager::WINDOW_WIDTH, SortManager::WINDOW_HEIGHT), "Merge sort");

    sf::RectangleShape items[SortManager::ARR_LEN];

    manager.createShuffled(window, items);

    mergeSort(window, items, 0, SortManager::ARR_LEN - 1);

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

void mergeSort(sf::RenderWindow &window, sf::RectangleShape items[], int start, int end)
{
    if (start < end)
    {
        int middle = (start + end) / 2;
        mergeSort(window, items, start, middle);
        mergeSort(window, items, middle + 1, end);
        merge(window, items, start, middle, end);
    }
}

void merge(sf::RenderWindow &window, sf::RectangleShape items[], int start, int middle, int end)
{
    int leftLength = middle - start + 1;
    int rightLength = end - middle;

    items[middle].setFillColor(sf::Color::Red);

    auto *itemsLeft = new sf::RectangleShape[leftLength];
    auto *itemsRight = new sf::RectangleShape[rightLength];

    // copy values into new arrays
    for (int i = 0; i < leftLength; i++)
    {
        itemsLeft[i] = items[start + i];
    }
    for (int i = 0; i < rightLength; i++)
    {
        itemsRight[i] = items[middle + 1 + i];
    }

    int left = 0;
    int right = 0;
    int i = start;

    // merge until you run out of one of the lists
    while (left < leftLength && right < rightLength)
    {
        // current left is smaller, do that one
        if (itemsLeft[left].getSize().y < itemsRight[right].getSize().y)
        {
            items[i].setSize(sf::Vector2f(SortManager::ITEM_WIDTH, itemsLeft[left].getSize().y));
            items[i].setPosition(sf::Vector2f(items[i].getPosition().x, itemsLeft[left].getPosition().y));
            items[i].setFillColor(sf::Color::Yellow);

            left++;
        }
        else
        {
            items[i].setSize(sf::Vector2f(SortManager::ITEM_WIDTH, itemsRight[right].getSize().y));
            items[i].setPosition(sf::Vector2f(items[i].getPosition().x, itemsRight[right].getPosition().y));
            items[i].setFillColor(sf::Color::Green);

            right++;
        }
        i++;

        std::this_thread::sleep_for(std::chrono::milliseconds(SortManager::SLEEP_MILLIS));
        window.clear();
        for (int j = 0; j < SortManager::ARR_LEN; j++)
            window.draw(items[j]);
        window.display();
    }

    // remaining left
    while (left < leftLength)
    {
        items[i].setSize(sf::Vector2f(SortManager::ITEM_WIDTH, itemsLeft[left].getSize().y));
        items[i].setPosition(sf::Vector2f(items[i].getPosition().x, itemsLeft[left].getPosition().y));
        items[i].setFillColor(sf::Color::Yellow);

        left++;
        i++;

        std::this_thread::sleep_for(std::chrono::milliseconds(SortManager::SLEEP_MILLIS));
        window.clear();
        for (int j = 0; j < SortManager::ARR_LEN; j++)
            window.draw(items[j]);
        window.display();
    }

    // remaining right
    while (right < rightLength)
    {
        items[i].setSize(sf::Vector2f(SortManager::ITEM_WIDTH, itemsRight[right].getSize().y));
        items[i].setPosition(sf::Vector2f(items[i].getPosition().x, itemsRight[right].getPosition().y));
        items[i].setFillColor(sf::Color::Green);

        right++;
        i++;

        std::this_thread::sleep_for(std::chrono::milliseconds(SortManager::SLEEP_MILLIS));
        window.clear();
        for (int j = 0; j < SortManager::ARR_LEN; j++)
            window.draw(items[j]);
        window.display();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(SortManager::SLEEP_MILLIS));
    window.clear();
    for (int j = 0; j < SortManager::ARR_LEN; j++)
    {
        window.draw(items[j]);
        if (j <= end && j >= start)
            items[j].setFillColor(sf::Color::White);
    }
    window.display();

    delete[] itemsLeft;
    delete[] itemsRight;
}