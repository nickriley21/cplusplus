#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <iostream>
#include <thread>
#include <chrono>

void quickSort(sf::RenderWindow &window, sf::RectangleShape items[], int start, int end);
int partition(sf::RenderWindow &window, sf::RectangleShape items[], int start, int end);
void createShuffled(sf::RectangleShape items[]);
void swap(sf::RectangleShape &a, sf::RectangleShape &b);

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int ARR_LEN = 400;

const int SLEEP_MILLIS = 1;

const int ITEM_WIDTH = WINDOW_WIDTH / ARR_LEN;
const int ITEM_HEIGHT_DIFF = WINDOW_HEIGHT / ARR_LEN;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Quick sort");

    sf::RectangleShape items[ARR_LEN];

    createShuffled(items);

    quickSort(window, items, 0, ARR_LEN - 1);

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

void quickSort(sf::RenderWindow &window, sf::RectangleShape items[], int start, int end)
{
    if (start < end)
    {
        int p = partition(window, items, start, end);

        quickSort(window, items, start, p - 1);
        quickSort(window, items, p + 1, end);
    }
}

// returns index of partition
int partition(sf::RenderWindow &window, sf::RectangleShape items[], int start, int end)
{
    items[end].setFillColor(sf::Color::Red);
    int low = start - 1;
    for (int i = start; i < end; i++)
    {
        if (items[i].getSize().y < items[end].getSize().y)
        {
            low++;
            swap(items[i], items[low]);
            items[low].setFillColor(sf::Color::Green);
        }
        else
        {
            items[i].setFillColor(sf::Color::Yellow);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLIS));
        window.clear();
        for (int j = 0; j < ARR_LEN; j++)
            window.draw(items[j]);
        window.display();
    }
    items[end].setFillColor(sf::Color::White);
    swap(items[low + 1], items[end]);

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLIS));
    window.clear();
    for (int j = 0; j < ARR_LEN; j++)
    {
        window.draw(items[j]);
        if (j <= end && j >= start)
            items[j].setFillColor(sf::Color::White);
    }
    window.display();

    return low + 1;
}

void createShuffled(sf::RectangleShape items[])
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
    srand(time(0));
    for (int i = ARR_LEN - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(items[i], items[j]);
    }
}

void swap(sf::RectangleShape &a, sf::RectangleShape &b)
{
    // swap sizes
    int temp = a.getSize().y;
    a.setSize(sf::Vector2f(ITEM_WIDTH, b.getSize().y));
    b.setSize(sf::Vector2f(ITEM_WIDTH, temp));

    // re-adjust heights
    a.setPosition(sf::Vector2f(a.getPosition().x, WINDOW_HEIGHT - a.getSize().y));
    b.setPosition(sf::Vector2f(b.getPosition().x, WINDOW_HEIGHT - b.getSize().y));
}