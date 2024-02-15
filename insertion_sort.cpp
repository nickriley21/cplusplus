#include <SFML/Graphics.hpp>
#include "SortManager.hpp"

void insert(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int i);

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

        // insertion sort
        if (i < SortManager::ARR_LEN)
        {
            insert(manager, window, items, i);
            i++;
        }

        manager.displayItems(window, items);
    }

    return 0;
}

// green for sorted already
// red for current value being inserted
void insert(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int i)
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