#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include "SortManager.hpp"

constexpr int SortManager::SLEEP_MILLIS;

SortManager::SortManager()
{
    srand(time(0)); // seeding random number generator
}

void SortManager::createShuffled(sf::RenderWindow &window, sf::RectangleShape items[])
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
    for (int i = ARR_LEN - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(items[i], items[j]);

        displayItems(window, items);
    }
}

void SortManager::swap(sf::RectangleShape &a, sf::RectangleShape &b)
{
    // swap sizes
    int temp = a.getSize().y;
    a.setSize(sf::Vector2f(ITEM_WIDTH, b.getSize().y));
    b.setSize(sf::Vector2f(ITEM_WIDTH, temp));

    // re-adjust heights
    a.setPosition(sf::Vector2f(a.getPosition().x, WINDOW_HEIGHT - a.getSize().y));
    b.setPosition(sf::Vector2f(b.getPosition().x, WINDOW_HEIGHT - b.getSize().y));
}

void SortManager::displayItems(sf::RenderWindow &window, sf::RectangleShape items[])
{
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLIS));
    window.clear();
    for (int j = 0; j < ARR_LEN; j++)
        window.draw(items[j]);
    window.display();
}
void SortManager::displayAndWhiteItemsInRange(sf::RenderWindow &window, sf::RectangleShape items[], int start, int end)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLIS));
    window.clear();
    for (int j = 0; j < ARR_LEN; j++)
    {
        window.draw(items[j]);
        if (j <= end && j >= start)
            items[j].setFillColor(sf::Color::White);
    }
    window.display();
}
