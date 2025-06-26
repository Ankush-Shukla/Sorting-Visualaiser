#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "SortingAlgorithms.hpp"
#include "Sorting.hpp"
#include "Visualization.hpp"
#include "AudioManager.hpp"

enum class SortType {
    Bubble = 1,
    Selection = 2,
    Insertion = 3,
    Merge = 4
};

int main() {
    int n = 50;
    int min_n = 5, max_n = 200;
    int speed = 50;
    int min_speed = 1, max_speed = 500;

    std::vector<int> arr = rand_array(n);

    float win_width = 800;
    float win_height = 600;
    sf::RenderWindow window(sf::VideoMode({ (unsigned int)win_width, (unsigned int)win_height }), "Sorting Visualizer");

    std::vector<sf::RectangleShape> rectangles = draw_rectangles(arr.data(), n, win_width, win_height);

    sf::RectangleShape startButton({ 100, 50 });
    startButton.setFillColor(sf::Color::White);
    startButton.setPosition({ win_width / 2 - 50, win_height - 580 });

    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        std::cerr << "Error: Could not load font file 'arial.ttf'. Please ensure the file exists in the working directory.\n";
        return -1;
    }

    // Start button label
    sf::Text startText(font);
    startText.setString("Start");
    startText.setCharacterSize(26);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition({ win_width / 2 - 30, win_height - 570 });

    sf::SoundBuffer beepBuffer;
    if (!loadBeepSound(beepBuffer, "beep.wav")) {
        std::cerr << "Failed to load beep.wav. Exiting.\n";
        return -1;
    }
    sf::Sound sortingSound(beepBuffer);

    bool sortingStarted = false;
    bool barsVisible = false; // Add this flag
    SortType selectedSort = SortType::Bubble;

    // Sorting algorithm selection buttons
    std::vector<std::pair<sf::RectangleShape, sf::Text>> sortButtons;
    std::vector<std::string> sortNames = { "Bubble", "Selection", "Insertion", "Merge" };
    for (int i = 0; i < 4; ++i) {
        sf::RectangleShape btn({ 120, 40 });
        btn.setFillColor(sf::Color(200, 200, 200));
        btn.setPosition({ win_width / 2 - 60, win_height - 520 + i * 60 });
        sf::Text txt(font);
        txt.setString(sortNames[i] + " Sort");
        txt.setCharacterSize(22);
        txt.setFillColor(sf::Color::Black);
        txt.setPosition({ win_width / 2 - 50, win_height - 510 + i * 60 });
        sortButtons.emplace_back(btn, txt);
    }

    // Reset button
    sf::RectangleShape resetButton({ 100, 40 });
    resetButton.setFillColor(sf::Color(220, 220, 220));
    resetButton.setPosition({ win_width / 2 - 50, win_height - 280 });
    sf::Text resetText(font);
    resetText.setString("Reset");
    resetText.setCharacterSize(22);
    resetText.setFillColor(sf::Color::Black);
    resetText.setPosition({ win_width / 2 - 30, win_height - 270 });

    // Array size controls
    sf::RectangleShape plusSizeBtn({ 30, 30 });
    plusSizeBtn.setFillColor(sf::Color(180, 255, 180));
    plusSizeBtn.setPosition({ win_width - 160, 20 });
    sf::Text plusSizeText(font);
    plusSizeText.setString("+");
    plusSizeText.setCharacterSize(18);
    plusSizeText.setFillColor(sf::Color::Black);
    plusSizeText.setPosition({ win_width - 152, 18 });

    sf::RectangleShape minusSizeBtn({ 30, 30 });
    minusSizeBtn.setFillColor(sf::Color(255, 180, 180));
    minusSizeBtn.setPosition({ win_width - 200, 20 });
    sf::Text minusSizeText(font);
    minusSizeText.setString("-");
    minusSizeText.setCharacterSize(18);
    minusSizeText.setFillColor(sf::Color::Black);
    minusSizeText.setPosition({ win_width - 192, 18 });

    sf::Text sizeLabel(font);
    sizeLabel.setString("Size: " + std::to_string(n));
    sizeLabel.setCharacterSize(18);
    sizeLabel.setFillColor(sf::Color::Black);
    sizeLabel.setPosition({ win_width - 250, 22 });

    // Speed controls
    sf::RectangleShape plusSpeedBtn({ 30, 30 });
    plusSpeedBtn.setFillColor(sf::Color(180, 180, 255));
    plusSpeedBtn.setPosition({ win_width - 160, 60 });
    sf::Text plusSpeedText(font);
    plusSpeedText.setString("+");
    plusSpeedText.setCharacterSize(18);
    plusSpeedText.setFillColor(sf::Color::Black);
    plusSpeedText.setPosition({ win_width - 152, 58 });

    sf::RectangleShape minusSpeedBtn({ 30, 30 });
    minusSpeedBtn.setFillColor(sf::Color(255, 220, 180));
    minusSpeedBtn.setPosition({ win_width - 200, 60 });
    sf::Text minusSpeedText(font);
    minusSpeedText.setString("-");
    minusSpeedText.setCharacterSize(18);
    minusSpeedText.setFillColor(sf::Color::Black);
    minusSpeedText.setPosition({ win_width - 192, 58 });

    sf::Text speedLabel(font);
    speedLabel.setString("Speed: " + std::to_string(speed));
    speedLabel.setCharacterSize(18);
    speedLabel.setFillColor(sf::Color::Black);
    speedLabel.setPosition({ win_width - 250, 62 });

    // Slider settings
    float sliderWidth = 300.f;
    float sliderHeight = 8.f;
    float sliderY1 = win_height - 60;
    float sliderY2 = win_height - 30;
    float knobRadius = 12.f;

    // For dragging
    bool draggingSize = false, draggingSpeed = false;

    // Helper to get value from slider position
    auto sliderValue = [](float pos, float min, float max, float x, float width) {
        float t = std::clamp((pos - x) / width, 0.f, 1.f);
        return static_cast<int>(min + t * (max - min));
    };

    while (window.isOpen()) {
        // Modern SFML 3.x event loop
        while (const std::optional event = window.pollEvent()) {
            // Window closed or escape key pressed: exit
            if (event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() &&
                 event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)) {
                window.close();
            }

            // Mouse button pressed
            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (int i = 0; i < 4; ++i) {
                        if (sortButtons[i].first.getGlobalBounds().contains({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) })) {
                            selectedSort = static_cast<SortType>(i + 1);
                        }
                    }
                    if (startButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) })) {
                        sortingStarted = true;
                    }
                    if (resetButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) })) {
                        arr = rand_array(n);
                        rectangles = draw_rectangles(arr.data(), n, win_width, win_height);
                        barsVisible = false; // Hide bars again on reset
                    }
                    if (plusSizeBtn.getGlobalBounds().contains({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) })) {
                        if (n < max_n) {
                            ++n;
                            arr = rand_array(n);
                            rectangles = draw_rectangles(arr.data(), n, win_width, win_height);
                            barsVisible = false;
                        }
                    }
                    if (minusSizeBtn.getGlobalBounds().contains({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) })) {
                        if (n > min_n) {
                            --n;
                            arr = rand_array(n);
                            rectangles = draw_rectangles(arr.data(), n, win_width, win_height);
                            barsVisible = false;
                        }
                    }
                    if (plusSpeedBtn.getGlobalBounds().contains({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) })) {
                        if (speed < max_speed) {
                            speed += 5;
                        }
                    }
                    if (minusSpeedBtn.getGlobalBounds().contains({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) })) {
                        if (speed > min_speed) {
                            speed -= 5;
                        }
                    }
                    // Size slider knob
                    float sizeKnobX = 80 + ((n - min_n) / float(max_n - min_n)) * sliderWidth;
                    if (std::hypot(mousePos.x - (80 + sizeKnobX), mousePos.y - sliderY1) < knobRadius + 2)
                        draggingSize = true;
                    // Speed slider knob
                    float speedKnobX = 80 + ((speed - min_speed) / float(max_speed - min_speed)) * sliderWidth;
                    if (std::hypot(mousePos.x - (80 + speedKnobX), mousePos.y - sliderY2) < knobRadius + 2)
                        draggingSpeed = true;
                }
            }

            // Mouse button released
            if (const auto* mouse = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (mouse->button == sf::Mouse::Button::Left) {
                    draggingSize = draggingSpeed = false;
                }
            }

            // Mouse moved
            if (const auto* mouse = event->getIf<sf::Event::MouseMoved>()) {
                sf::Vector2i mousePos(mouse->position.x, mouse->position.y);
                if (draggingSize) {
                    // Calculate relative mouse X to slider start
                    float pos = std::clamp(float(mousePos.x) - 80.0f, 0.0f, sliderWidth);
                    int new_n = sliderValue(pos, min_n, max_n, 0, sliderWidth);
                    if (new_n != n) {
                        n = new_n;
                        arr = rand_array(n);
                        rectangles = draw_rectangles(arr.data(), n, win_width, win_height);
                        barsVisible = false;
                    }
                }
                if (draggingSpeed) {
                    float pos = std::clamp(float(mousePos.x) - 80.0f, 0.0f, sliderWidth);
                    int new_speed = sliderValue(pos, min_speed, max_speed, 0, sliderWidth);
                    if (new_speed != speed) {
                        speed = new_speed;
                    }
                }
            }

            // Mouse wheel scrolled
            if (event->is<sf::Event::MouseWheelScrolled>()) {
                if (event->getIf<sf::Event::MouseWheelScrolled>()->delta > 0) {
                    if (n < max_n) {
                        ++n;
                        arr = rand_array(n);
                        rectangles = draw_rectangles(arr.data(), n, win_width, win_height);
                        barsVisible = false;
                    }
                }
                else {
                    if (n > min_n) {
                        --n;
                        arr = rand_array(n);
                        rectangles = draw_rectangles(arr.data(), n, win_width, win_height);
                        barsVisible = false;
                    }
                }
            }
        }

        window.clear(sf::Color(20, 20, 30));

        // --- Draw UI panels and controls (unchanged) ---
        sf::RectangleShape controlPanel({ 320, 420 });
        controlPanel.setFillColor(sf::Color(40, 40, 60, 220));
        controlPanel.setOutlineColor(sf::Color(100, 200, 255, 180));
        controlPanel.setOutlineThickness(2);
        controlPanel.setPosition({ win_width / 2 - 160, 40 });
        window.draw(controlPanel);

        sf::Text title(font);
        title.setString("Sorting Visualizer");
        title.setCharacterSize(32);
        title.setFillColor(sf::Color(100, 200, 255));
        title.setStyle(sf::Text::Bold);
        title.setPosition({ win_width / 2 - title.getLocalBounds().size.x / 2, 55 });
        window.draw(title);

        startButton.setSize({ 180, 50 });
        startButton.setPosition({ win_width / 2 - 90, 110 });
        startButton.setFillColor(sf::Color(255, 255, 255, 230));
        startButton.setOutlineThickness(2);
        startButton.setOutlineColor(sf::Color(100, 200, 255));
        window.draw(startButton);

        startText.setFillColor(sf::Color(30, 30, 30));
        startText.setPosition({ win_width / 2 - 40, 122 });
        window.draw(startText);

        for (int i = 0; i < 4; ++i) {
            auto& btn = sortButtons[i].first;
            auto& txt = sortButtons[i].second;
            btn.setSize({ 180, 40 });
            btn.setPosition({ win_width / 2 - 90, 180 + i * 55 });
            btn.setFillColor(selectedSort == static_cast<SortType>(i + 1)
                ? sf::Color(100, 200, 255, 220)
                : sf::Color(220, 220, 220, 220));
            btn.setOutlineThickness(1);
            btn.setOutlineColor(sf::Color(180, 180, 180));
            window.draw(btn);

            txt.setFillColor(sf::Color(30, 30, 30));
            txt.setPosition({ win_width / 2 - 70, 190 + i * 55 });
            window.draw(txt);
        }

        resetButton.setSize({ 180, 40 });
        resetButton.setPosition({ win_width / 2 - 90, 410 });
        resetButton.setFillColor(sf::Color(255, 220, 220, 220));
        resetButton.setOutlineThickness(1);
        resetButton.setOutlineColor(sf::Color(180, 180, 180));
        window.draw(resetButton);

        resetText.setFillColor(sf::Color(30, 30, 30));
        resetText.setPosition({ win_width / 2 - 35, 420 });
        window.draw(resetText);

        sf::RectangleShape sizePanel({ 170, 70 });
        sizePanel.setFillColor(sf::Color(30, 30, 40, 200));
        sizePanel.setOutlineColor(sf::Color(100, 200, 255, 120));
        sizePanel.setOutlineThickness(1);
        sizePanel.setPosition({ win_width - 190, 15 });
        window.draw(sizePanel);

        window.draw(plusSizeBtn);
        window.draw(plusSizeText);
        window.draw(minusSizeBtn);
        window.draw(minusSizeText);
        sizeLabel.setString("Size: " + std::to_string(n));
        sizeLabel.setFillColor(sf::Color(220, 220, 255));
        sizeLabel.setPosition({ win_width - 180, 22 });
        window.draw(sizeLabel);

        window.draw(plusSpeedBtn);
        window.draw(plusSpeedText);
        window.draw(minusSpeedBtn);
        window.draw(minusSpeedText);
        speedLabel.setString("Speed: " + std::to_string(speed));
        speedLabel.setFillColor(sf::Color(220, 220, 255));
        speedLabel.setPosition({ win_width - 180, 62 });
        window.draw(speedLabel);

        // --- Draw Size Slider ---
        sf::RectangleShape sizeSliderBg({sliderWidth, sliderHeight});
        sizeSliderBg.setFillColor(sf::Color(80, 80, 120));
        sizeSliderBg.setPosition({80, sliderY1 - sliderHeight / 2});
        window.draw(sizeSliderBg);

        float sizeKnobX = 80 + ((n - min_n) / float(max_n - min_n)) * sliderWidth;
        sf::CircleShape sizeKnob(knobRadius);
        sizeKnob.setFillColor(sf::Color(100, 200, 255));
        sizeKnob.setOrigin({knobRadius, knobRadius});
        sizeKnob.setPosition({sizeKnobX, sliderY1});
        window.draw(sizeKnob);

        sf::Text sizeSliderLabel(font);
        sizeSliderLabel.setString("Array Size: " + std::to_string(n));
        sizeSliderLabel.setCharacterSize(18);
        sizeSliderLabel.setFillColor(sf::Color(220, 220, 255));
        sizeSliderLabel.setPosition({80, sliderY1 - 32});
        window.draw(sizeSliderLabel);

        // --- Draw Speed Slider ---
        sf::RectangleShape speedSliderBg({sliderWidth, sliderHeight});
        speedSliderBg.setFillColor(sf::Color(80, 80, 120));
        speedSliderBg.setPosition({80, sliderY2 - sliderHeight / 2});
        window.draw(speedSliderBg);

        float speedKnobX = 80 + ((speed - min_speed) / float(max_speed - min_speed)) * sliderWidth;
        sf::CircleShape speedKnob(knobRadius);
        speedKnob.setFillColor(sf::Color(180, 120, 255));
        speedKnob.setOrigin({knobRadius, knobRadius});
        speedKnob.setPosition({speedKnobX, sliderY2});
        window.draw(speedKnob);

        sf::Text speedSliderLabel(font);
        speedSliderLabel.setString("Speed: " + std::to_string(speed));
        speedSliderLabel.setCharacterSize(18);
        speedSliderLabel.setFillColor(sf::Color(220, 220, 255));
        speedSliderLabel.setPosition({80, sliderY2 - 32});
        window.draw(speedSliderLabel);

        // --- Only draw bars if visible ---
        if (barsVisible) {
            for (const auto& rect : rectangles) {
                window.draw(rect);
            }
        }

        window.display();

        if (sortingStarted) {
            barsVisible = true; // Show bars after Start is pressed
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