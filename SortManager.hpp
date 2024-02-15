#ifndef SORT_MANAGER_HPP
#define SORT_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class SortManager
{
public:
    static constexpr int ARR_LEN = 100;
    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;
    static constexpr int SLEEP_MILLIS = 1;
    static constexpr int ITEM_WIDTH = WINDOW_WIDTH / ARR_LEN;
    static constexpr int ITEM_HEIGHT_DIFF = WINDOW_HEIGHT / ARR_LEN;

    SortManager();

    void createShuffled(sf::RenderWindow &window, sf::RectangleShape items[]);
    void swap(sf::RectangleShape &a, sf::RectangleShape &b);
};

#endif