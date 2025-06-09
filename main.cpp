#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Sorting.hpp"
#include <SFML/Audio.hpp>
std::vector<sf::RectangleShape> draw_rectangles(int arr[], int count, float win_width, float win_height) {
    std::vector<sf::RectangleShape> rectangles;
    float rect_width = win_width / count;
    float spacing = rect_width;

    float max_height = *std::max_element(arr, arr + count);
    float max_bar_height = win_height * 0.8;

    for (int i = 0; i < count; i++) {
        float scaled_height = (arr[i] / max_height) * max_bar_height;

        sf::RectangleShape rect(sf::Vector2f(rect_width - 2, scaled_height));
        rect.setFillColor(sf::Color::White);
        float x_position = i * spacing;
        rect.setPosition({x_position, win_height - scaled_height});
        rectangles.push_back(rect);
    }

    return rectangles;
}

int main() {
  
       

    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    std::vector<int> arr = rand_array(n);

    std::cout << "Generated heights: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

     float win_width = 800;
     float win_height = 600;
    sf::RenderWindow window(sf::VideoMode({(unsigned int)win_width, (unsigned int)win_height}), "Sorting Visualizer");

    std::vector<sf::RectangleShape> rectangles = draw_rectangles(arr.data(), n, win_width, win_height);

    // Start button setup
    sf::RectangleShape startButton(sf::Vector2f(100, 50));
    startButton.setFillColor(sf::Color::White);
    startButton.setPosition({win_width / 2 - 50, win_height - 580});

    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    sf::Text startText(font);
    startText.setFont(font);
    startText.setString("Start");
    startText.setFillColor(sf::Color::Black);
    startText.setPosition({win_width / 2 - 30, win_height- 570});

    bool sortingStarted = false;

    while (window.isOpen()) {
       
        while ( std::optional event=window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (startButton.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    sortingStarted = true;
                }
            }
        }

       
         window.clear();

        // Draw rectangles
        for (const auto& rect : rectangles) {
            window.draw(rect);
        }

        // Draw start button and text
        window.draw(startButton);
        window.draw(startText);
      
        window.display();

        // Start sorting if button was clicked
        if (sortingStarted) {
            //implementing switch to choose sorting algorithm
            std::cout << "Choose sorting algorithm:\n1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Merge Sort\n";
            int choice;
            std::cin >> choice;
  
            switch (choice) {
                case 1:
                    std::cout << "Bubble Sort selected\n";
                    bubble_sort(arr.data(), rectangles, window, win_height);
                    break;
                case 2:
                    std::cout << "Selection Sort selected\n";
                    selection_sort(arr.data(), rectangles, window, win_height);
                    break;
                case 3:
                    std::cout << "Insertion Sort selected\n";
                    insertion_sort(arr.data(), rectangles, window, win_height);    
                    break;
                case 4:
                    std::cout << "Merge Sort selected\n";
                    merge_sort_visualization(arr.data(), rectangles, window, win_height, 0, n - 1);
                    break;
                default:
                    std::cout << "Invalid choice, defaulting to Bubble Sort\n";
                    
            }
        

            sortingStarted = false;
        }
      
    }


    return 0;
}
