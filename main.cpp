#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "SortingAlgorithms.hpp"
#include "Sorting.hpp" // for rand_array
#include "Visualization.hpp"
#include "AudioManager.hpp"
#include <SFML/Audio.hpp>

// Enum for sorting algorithm selection
enum class SortType {
    Bubble = 1,
    Selection = 2,
    Insertion = 3,
    Merge = 4
};

int main() {
    // Initial array size and speed settings
    int n = 50;
    int min_n = 5, max_n = 200;
    int speed = 50;
    int min_speed = 1, max_speed = 500;

    // Generate the initial random array
    std::vector<int> arr = rand_array(n);

    // Window setup
    float win_width = 800;
    float win_height = 600;
    sf::RenderWindow window(sf::VideoMode({(unsigned int)win_width, (unsigned int)win_height}), "Sorting Visualizer");

    // Create the rectangles for visualization
    std::vector<sf::RectangleShape> rectangles = draw_rectangles(arr.data(), n, win_width, win_height);

    // Start button
    sf::RectangleShape startButton({100, 50});
    startButton.setFillColor(sf::Color::White);
    startButton.setPosition({win_width / 2 - 50, win_height - 580});

    // Load font for UI
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        std::cerr << "Error: Could not load font file 'arial.ttf'. Please ensure the file exists in the working directory.\n";
        return -1;
    }

    // Start button label
    sf::Text startText(font);
    startText.setFont(font);
    startText.setString("Start");
    startText.setFillColor(sf::Color::Black);
    startText.setPosition({win_width / 2 - 30, win_height- 570});

    // Load beep sound for sorting
    sf::SoundBuffer beepBuffer;
    if (!loadBeepSound(beepBuffer, "beep.wav")) {
        std::cerr << "Failed to load beep.wav. Exiting.\n";
        return -1;
    }
    sf::Sound sortingSound(beepBuffer);

    bool sortingStarted = false;
    SortType selectedSort = SortType::Bubble;

    // Sorting algorithm selection buttons
    std::vector<std::pair<sf::RectangleShape, sf::Text>> sortButtons;
    std::vector<std::string> sortNames = {"Bubble", "Selection", "Insertion", "Merge"};
    for (int i = 0; i < 4; ++i) {
        sf::RectangleShape btn({120, 40});
        btn.setFillColor(sf::Color(200, 200, 200));
        btn.setPosition({win_width / 2 - 60, win_height - 520 + i * 60});
        sf::Text txt(font);
        txt.setString(sortNames[i] + " Sort");
        txt.setFillColor(sf::Color::Black);
        txt.setPosition({win_width / 2 - 50, win_height - 510 + i * 60});
        sortButtons.emplace_back(btn, txt);
    }

    // Reset button
    sf::RectangleShape resetButton({100, 40});
    resetButton.setFillColor(sf::Color(220, 220, 220));
    resetButton.setPosition({win_width / 2 - 50, win_height - 280});
    sf::Text resetText(font);
    resetText.setString("Reset");
    resetText.setFillColor(sf::Color::Black);
    resetText.setPosition({win_width / 2 - 30, win_height - 270});

    // Array size controls
    sf::RectangleShape plusSizeBtn({30, 30});
    plusSizeBtn.setFillColor(sf::Color(180, 255, 180));
    plusSizeBtn.setPosition({win_width - 160, 20});
    sf::Text plusSizeText(font);
    plusSizeText.setString("+");
    plusSizeText.setFillColor(sf::Color::Black);
    plusSizeText.setPosition({win_width - 152, 18});

    sf::RectangleShape minusSizeBtn({30, 30});
    minusSizeBtn.setFillColor(sf::Color(255, 180, 180));
    minusSizeBtn.setPosition({win_width - 200, 20});
    sf::Text minusSizeText(font);
    minusSizeText.setString("-");
    minusSizeText.setFillColor(sf::Color::Black);
    minusSizeText.setPosition({win_width - 192, 18});

    sf::Text sizeLabel(font);
    sizeLabel.setFillColor(sf::Color::Black);
    sizeLabel.setCharacterSize(18);
    sizeLabel.setPosition({win_width - 250, 22});

    // Speed controls
    sf::RectangleShape plusSpeedBtn({30, 30});
    plusSpeedBtn.setFillColor(sf::Color(180, 180, 255));
    plusSpeedBtn.setPosition({win_width - 160, 60});
    sf::Text plusSpeedText(font);
    plusSpeedText.setString("+");
    plusSpeedText.setFillColor(sf::Color::Black);
    plusSpeedText.setPosition({win_width - 152, 58});

    sf::RectangleShape minusSpeedBtn({30, 30});
    minusSpeedBtn.setFillColor(sf::Color(255, 220, 180));
    minusSpeedBtn.setPosition({win_width - 200, 60});
    sf::Text minusSpeedText(font);
    minusSpeedText.setString("-");
    minusSpeedText.setFillColor(sf::Color::Black);
    minusSpeedText.setPosition({win_width - 192, 58});

    sf::Text speedLabel(font);
    speedLabel.setFillColor(sf::Color::Black);
    speedLabel.setCharacterSize(18);
    speedLabel.setPosition({win_width - 250, 62});

    // Main event loop
    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                // Check which sort button was clicked
                for (int i = 0; i < 4; ++i) {
                    if (sortButtons[i].first.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        selectedSort = static_cast<SortType>(i + 1);
                    }
                }
                // Check if start button was clicked
                if (startButton.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    sortingStarted = true;
                }
                // Check if reset button was clicked
                if (resetButton.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    arr = rand_array(n);
                    rectangles = draw_rectangles(arr.data(), n, win_width, win_height);
                }
                // Array size + and -
                if (plusSizeBtn.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    if (n < max_n) {
                        ++n;
                        arr = rand_array(n);
                        rectangles = draw_rectangles(arr.data(), n, win_width, win_height);
                    }
                }
                if (minusSizeBtn.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    if (n > min_n) {
                        --n;
                        arr = rand_array(n);
                        rectangles = draw_rectangles(arr.data(), n, win_width, win_height);
                    }
                }
                // Speed + and -
                if (plusSpeedBtn.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    if (speed < max_speed) {
                        speed += 5;
                    }
                }
                if (minusSpeedBtn.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    if (speed > min_speed) {
                        speed -= 5;
                    }
                }
            }
        }

        window.clear();
        // Update the labels for size and speed
        sizeLabel.setString("Size: " + std::to_string(n));
        speedLabel.setString("Speed: " + std::to_string(speed) + " ms");

        // Draw the array bars
        for (const auto& rect : rectangles) {
            window.draw(rect);
        }

        // Draw the UI controls
        window.draw(startButton);
        window.draw(startText);
        for (int i = 0; i < 4; ++i) {
            if (selectedSort == static_cast<SortType>(i + 1))
                sortButtons[i].first.setFillColor(sf::Color(100, 200, 255));
            else
                sortButtons[i].first.setFillColor(sf::Color(200, 200, 200));
            window.draw(sortButtons[i].first);
            window.draw(sortButtons[i].second);
        }
        window.draw(resetButton);
        window.draw(resetText);
        window.draw(plusSizeBtn);
        window.draw(plusSizeText);
        window.draw(minusSizeBtn);
        window.draw(minusSizeText);
        window.draw(sizeLabel);
        window.draw(plusSpeedBtn);
        window.draw(plusSpeedText);
        window.draw(minusSpeedBtn);
        window.draw(minusSpeedText);
        window.draw(speedLabel);

        window.display();

        // Run the selected sort when Start is pressed
        if (sortingStarted) {
            switch (selectedSort) {
                case SortType::Bubble:
                    bubble_sort(arr.data(), rectangles, window, win_height, sortingSound, speed);
                    break;
                case SortType::Selection:
                    selection_sort(arr.data(), rectangles, window, win_height, sortingSound, speed);
                    break;
                case SortType::Insertion:
                    insertion_sort(arr.data(), rectangles, window, win_height, sortingSound, speed);
                    break;
                case SortType::Merge:
                    merge_sort_visualization(arr.data(), rectangles, window, win_height, 0, n - 1, sortingSound, speed);
                    break;
                default:
                    bubble_sort(arr.data(), rectangles, window, win_height, sortingSound, speed);
            }
            sortingStarted = false;
        }
    }

    return 0;
}
