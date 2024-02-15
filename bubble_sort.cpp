#include <SFML/Graphics.hpp>
#include "SortManager.hpp"

void bubbleSort(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[]);

int main()
{
    SortManager manager;

    sf::RenderWindow window(sf::VideoMode(SortManager::WINDOW_WIDTH, SortManager::WINDOW_HEIGHT), "Bubble sort");

    sf::RectangleShape items[SortManager::ARR_LEN];

    manager.createShuffled(window, items);

    bubbleSort(manager, window, items);

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
// red for current value being bubbled up
void bubbleSort(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[])
{
    for (int i = 0; i < SortManager::ARR_LEN; i++)
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

    manager.displayItems(window, items);
}
