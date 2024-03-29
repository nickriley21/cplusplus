#include <SFML/Graphics.hpp>
#include "SortManager.hpp"

void select(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int i);

int main()
{
    SortManager manager;

    sf::RenderWindow window(sf::VideoMode(SortManager::WINDOW_WIDTH, SortManager::WINDOW_HEIGHT), "Selection sort");

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

        // selection sort
        if (i < SortManager::ARR_LEN)
        {
            select(manager, window, items, i);
            i++;
        }

        manager.displayItems(window, items);
    }

    return 0;
}

// green for sorted already
// red for current minimum
// yellow for being checked against current minimum
void select(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int i)
{
    int min = items[i].getSize().y;
    int min_index = i;

    // first value is current min, so make it red
    items[i].setFillColor(sf::Color::Red);

    for (int j = i + 1; j < SortManager::ARR_LEN; j++)
    {
        items[j].setFillColor(sf::Color::Yellow); // current item being checked is yellow

        if (items[j - 1].getFillColor() != sf::Color::Red) // change previous back to white from yellow, unless it is a red
        {
            items[j - 1].setFillColor(sf::Color::White);
        }

        if (items[j].getSize().y < min)
        {
            items[min_index].setFillColor(sf::Color::White);
            min = items[j].getSize().y;
            min_index = j;
            items[min_index].setFillColor(sf::Color::Red);
        }

        manager.displayItems(window, items);
    }

    manager.swap(items[i], items[min_index]);                       // swap them
    items[min_index].setFillColor(sf::Color::White);                // minimum index spot is now swapped. go back to white
    items[SortManager::ARR_LEN - 1].setFillColor(sf::Color::White); // change from yellow back to white.
    items[i].setFillColor(sf::Color::Green);                        // sorted, change to green!
}