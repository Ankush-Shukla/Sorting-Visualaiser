#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <Sorting.hpp>

// Function declaration for bubble_sort


// Function to create rectangles that fully spread across the window
std::vector<sf::RectangleShape> draw_rectangles(int arr[], int count, float win_width, float win_height) {
    std::vector<sf::RectangleShape> rectangles;
    float rect_width = win_width / count;
    float spacing = rect_width;
//Finding max height and adjusting the height of the bars
    float max_height = *std::max_element(arr, arr + count);
    float max_bar_height = win_height * 0.8;

    for (int i = 0; i < count; i++) {
        // Scale height dynamically
        float scaled_height = (arr[i] / max_height) * max_bar_height;

        sf::RectangleShape rect(sf::Vector2f(rect_width - 2, scaled_height));
        rect.setFillColor(sf::Color::Red);
        float x_position = i * spacing;
        rect.setPosition({x_position, win_height - scaled_height});
        rectangles.push_back(rect);
    }

    return rectangles;
}


int main() {
    std::srand(std::time(0)); // Seed random values

    // User input for number of elements
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    std::vector<int> arr = rand_array(n); // Generate random heights

    std::cout << "Generated heights: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    unsigned int win_width = 800;
    unsigned int win_height = 600;
    sf::RenderWindow window(sf::VideoMode({win_width, win_height}), "Sorting Visualizer");

    // Generate rectangles
    std::vector<sf::RectangleShape> rectangles = draw_rectangles(arr.data(), n, win_width, win_height);
    bubble_sort(arr.data(), rectangles, window, win_height);
    while (window.isOpen()) {
       
        while (const std::optional event=window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();



        // Draw all rectangles
        for (const auto& rect : rectangles) {
            window.draw(rect);
        }

        window.display();
    }

    
    return 0;
}