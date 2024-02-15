#include <SFML/Graphics.hpp>
#include "SortManager.hpp"

void bubble(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int i);

int main()
{
    SortManager manager;

    sf::RenderWindow window(sf::VideoMode(SortManager::WINDOW_WIDTH, SortManager::WINDOW_HEIGHT), "Bubble sort");

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

        // bubble sort
        if (i < SortManager::ARR_LEN)
        {
            bubble(manager, window, items, i);
            i++;
        }

        manager.displayItems(window, items);
    }

    return 0;
}

// green for sorted already
// red for current value being bubbled up
void bubble(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int i)
{
    for (int j = 0; j < SortManager::ARR_LEN - i - 1; j++)
    {
        // bubble the larger one up the list
        if (items[j].getSize().y > items[j + 1].getSize().y)
        {
            manager.swap(items[j], items[j + 1]);
        }

        items[j].setFillColor(sf::Color::White);   // smaller goes to j, it is white
        items[j + 1].setFillColor(sf::Color::Red); // larger gies to j + 1, it is red

        manager.displayItems(window, items);
    }
    // this part is sorted, so green
    items[SortManager::ARR_LEN - i - 1].setFillColor(sf::Color::Green);
}