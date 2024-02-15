#include <SFML/Graphics.hpp>
#include "SortManager.hpp"

void heapSort(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[]);
void heapify(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int i, int n);

int main()
{
    SortManager manager;

    sf::RenderWindow window(sf::VideoMode(SortManager::WINDOW_WIDTH, SortManager::WINDOW_HEIGHT), "Heap sort");

    sf::RectangleShape items[SortManager::ARR_LEN];

    manager.createShuffled(window, items);

    heapSort(manager, window, items);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        manager.displayItems(window, items);
    }

    return 0;
}

// in sorted position is green
void heapSort(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[])
{
    // for second second lowest layer and above, heapify
    for (int i = SortManager::ARR_LEN / 2 - 1; i >= 0; i--)
        heapify(manager, window, items, i, SortManager::ARR_LEN);

    for (int i = SortManager::ARR_LEN - 1; i > 0; i--)
    {
        // largest item at top of the heap. put in sorted position at end.
        manager.swap(items[0], items[i]);

        items[i].setFillColor(sf::Color::Green);

        heapify(manager, window, items, 0, i);
    }
    // don't forget the last guy
    items[0].setFillColor(sf::Color::Green);
}

// for index i >= 0,
// left child at index 2*(i+1) - 1 = 2*i + 1
// right child at index 2*(i+1)    = 2*i + 2
// largest gets changed to red. set back to white when it is done.
void heapify(SortManager manager, sf::RenderWindow &window, sf::RectangleShape items[], int i, int n)
{
    int largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n)
    {
        if (items[left].getSize().y > items[largest].getSize().y)
        {
            largest = left;
        }
    }

    if (right < n)
    {
        if (items[right].getSize().y > items[largest].getSize().y)
        {
            largest = right;
        }
    }

    items[largest].setFillColor(sf::Color::Red);

    if (largest != i)
    {
        manager.swap(items[i], items[largest]);

        heapify(manager, window, items, largest, n);
    }
    manager.displayItems(window, items);

    items[largest].setFillColor(sf::Color::White);
}