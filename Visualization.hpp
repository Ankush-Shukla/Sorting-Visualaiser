#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

inline std::vector<sf::RectangleShape> draw_rectangles(int arr[], int count, float win_width, float win_height) {
    std::vector<sf::RectangleShape> rectangles;
    float rect_width = win_width / count;
    float spacing = rect_width;
    float max_height = *std::max_element(arr, arr + count);
    float max_bar_height = win_height * 0.8f;
    for (int i = 0; i < count; i++) {
        float scaled_height = (arr[i] / max_height) * max_bar_height;
        sf::RectangleShape rect({rect_width - 2, scaled_height});
        rect.setFillColor(sf::Color::White);
        float x_position = i * spacing;
        rect.setPosition({x_position, win_height - scaled_height});
        rectangles.push_back(rect);
    }
    return rectangles;
}
