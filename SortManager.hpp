#ifndef SORT_MANAGER_HPP
#define SORT_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class SortManager
{
public:
    static constexpr int ARR_LEN = 50;
    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;
    static constexpr int SLEEP_MILLIS = 1;
    static constexpr int ITEM_WIDTH = WINDOW_WIDTH / ARR_LEN;
    static constexpr int ITEM_HEIGHT_DIFF = WINDOW_HEIGHT / ARR_LEN;
    static constexpr bool DISPLAY = true;

    SortManager();

    void createShuffled(sf::RenderWindow &window, sf::RectangleShape items[]);
    void swap(sf::RectangleShape &a, sf::RectangleShape &b);
    void displayItems(sf::RenderWindow &window, sf::RectangleShape items[]);
    void displayAndWhiteItemsInRange(sf::RenderWindow &window, sf::RectangleShape items[], int start, int end);
};

#endif