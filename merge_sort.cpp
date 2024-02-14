#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <iostream>
#include <thread>
#include <chrono>

void mergeSort(sf::RenderWindow &window, sf::RectangleShape items[], int start, int end);
void merge(sf::RenderWindow &window, sf::RectangleShape items[], int start, int middle, int end);
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
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Merge sort");

    sf::RectangleShape items[ARR_LEN];

    createShuffled(items);

    mergeSort(window, items, 0, ARR_LEN - 1);

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
            items[i].setSize(sf::Vector2f(ITEM_WIDTH, itemsLeft[left].getSize().y));
            items[i].setPosition(sf::Vector2f(items[i].getPosition().x, itemsLeft[left].getPosition().y));

            left++;
        }
        else
        {
            items[i].setSize(sf::Vector2f(ITEM_WIDTH, itemsRight[right].getSize().y));
            items[i].setPosition(sf::Vector2f(items[i].getPosition().x, itemsRight[right].getPosition().y));

            right++;
        }
        i++;

        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLIS));
        window.clear();
        for (int j = 0; j < ARR_LEN; j++)
            window.draw(items[j]);
        window.display();
    }

    // remaining left
    while (left < leftLength)
    {
        items[i].setSize(sf::Vector2f(ITEM_WIDTH, itemsLeft[left].getSize().y));
        items[i].setPosition(sf::Vector2f(items[i].getPosition().x, itemsLeft[left].getPosition().y));

        left++;
        i++;

        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLIS));
        window.clear();
        for (int j = 0; j < ARR_LEN; j++)
            window.draw(items[j]);
        window.display();
    }

    // remaining right
    while (right < rightLength)
    {
        items[i].setSize(sf::Vector2f(ITEM_WIDTH, itemsRight[right].getSize().y));
        items[i].setPosition(sf::Vector2f(items[i].getPosition().x, itemsRight[right].getPosition().y));

        right++;
        i++;

        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLIS));
        window.clear();
        for (int j = 0; j < ARR_LEN; j++)
            window.draw(items[j]);
        window.display();
    }

    delete[] itemsLeft;
    delete[] itemsRight;
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