#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

// Calculate a pitch value for sound based on the height of a rectangle
float generatePitch(std::vector<sf::RectangleShape>& rectangles, int j) {
    float max_height = 0;
    float relative_height = 0;
    for (const auto& rect : rectangles) {
        max_height = std::max(max_height, rect.getSize().y);
        relative_height = rectangles[j].getSize().y / max_height;
    }
    return 0.5f + 0.5f * relative_height;
}

// Bubble Sort with visualization and sound
void bubble_sort(int arr[], std::vector<sf::RectangleShape>& rectangles, sf::RenderWindow& window, float win_height, sf::Sound& sorting, int speed) {
    int n = rectangles.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            while (std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                    return;
                }
            }
            rectangles[j].setFillColor(sf::Color::Red);
            rectangles[j + 1].setFillColor(sf::Color::Green);
            float pitch = generatePitch(rectangles, j);
            sorting.setPitch(pitch);
            sorting.setVolume(50);
            sorting.play();
            sf::sleep(sf::milliseconds(speed));
            window.clear();
            for (const auto& rect : rectangles) {
                window.draw(rect);
            }
            window.display();
            rectangles[j].setFillColor(sf::Color::White);
            rectangles[j + 1].setFillColor(sf::Color::White);
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                float temp_height = rectangles[j].getSize().y;
                rectangles[j].setSize({ rectangles[j].getSize().x, rectangles[j + 1].getSize().y });
                rectangles[j + 1].setSize({ rectangles[j + 1].getSize().x, temp_height });
                rectangles[j].setPosition({ rectangles[j].getPosition().x, win_height - rectangles[j].getSize().y });
                rectangles[j + 1].setPosition({ rectangles[j + 1].getPosition().x, win_height - rectangles[j + 1].getSize().y });
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// Selection Sort with visualization and sound
void selection_sort(int arr[], std::vector<sf::RectangleShape>& rectangles, sf::RenderWindow& window, float win_height, sf::Sound& sorting, int speed) {
    int n = rectangles.size();
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        bool swapped = false;
        rectangles[min_index].setFillColor(sf::Color::Red);
        for (int j = i + 1; j < n; j++) {
            while (std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                    return;
                }
            }
            rectangles[j].setFillColor(sf::Color::Green);
            float pitch = generatePitch(rectangles, j);
            sorting.setPitch(generatePitch(rectangles, j));
            sorting.setVolume(50);
            sorting.play();
            sf::sleep(sf::milliseconds(speed));
            window.clear();
            for (const auto& rect : rectangles) {
                window.draw(rect);
            }
            window.display();
            sf::sleep(sf::milliseconds(50));
            if (arr[j] < arr[min_index]) {
                min_index = j;
                rectangles[min_index].setFillColor(sf::Color::Red);
                swapped = true;
            }
            rectangles[j].setFillColor(sf::Color::White);
        }
        std::swap(arr[i], arr[min_index]);
        float temp_height = rectangles[i].getSize().y;
        rectangles[i].setSize({ rectangles[i].getSize().x, rectangles[min_index].getSize().y });
        rectangles[min_index].setSize({ rectangles[min_index].getSize().x, temp_height });
        rectangles[i].setPosition({ rectangles[i].getPosition().x, win_height - rectangles[i].getSize().y });
        rectangles[min_index].setPosition({ rectangles[min_index].getPosition().x, win_height - rectangles[min_index].getSize().y });
        rectangles[i].setFillColor(sf::Color::White);
    }
    rectangles[n - 1].setFillColor(sf::Color::Blue);
}

// Insertion Sort with visualization and sound
void insertion_sort(int arr[], std::vector<sf::RectangleShape>& rectangles, sf::RenderWindow& window, float win_height, sf::Sound& sorting, int speed) {
    int n = rectangles.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        float key_height = rectangles[i].getSize().y;
        int j = i - 1;
        rectangles[i].setFillColor(sf::Color::Red);
        while (j >= 0 && arr[j] > key) {
            while (std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                    return;
                }
            }
            rectangles[j].setFillColor(sf::Color::Green);
            float pitch = generatePitch(rectangles, j);
            sorting.setPitch(pitch);
            sorting.setVolume(50);
            sorting.play();
            arr[j + 1] = arr[j];
            rectangles[j + 1].setSize({rectangles[j + 1].getSize().x, rectangles[j].getSize().y});
            rectangles[j + 1].setPosition({rectangles[j + 1].getPosition().x, win_height - rectangles[j + 1].getSize().y});
            window.clear();
            for (const auto& rect : rectangles) {
                window.draw(rect);
            }
            window.display();
            sf::sleep(sf::milliseconds(speed));
            rectangles[j].setFillColor(sf::Color::White);
            j--;
        }
        arr[j + 1] = key;
        rectangles[j + 1].setSize({rectangles[j + 1].getSize().x, key_height});
        rectangles[j + 1].setPosition({rectangles[j + 1].getPosition().x, win_height - key_height});
        rectangles[j + 1].setFillColor(sf::Color::White);
    }
}

// Merge Sort visualization with sound
void merge_sort_visualization(int arr[], std::vector<sf::RectangleShape>& rectangles, sf::RenderWindow& window, float win_height, int left, int right, sf::Sound& sorting, int speed) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_visualization(arr, rectangles, window, win_height, left, mid, sorting, speed);
        merge_sort_visualization(arr, rectangles, window, win_height, mid + 1, right, sorting, speed);
        int n1 = mid - left + 1;
        int n2 = right - mid;
        std::vector<int> L(n1), R(n2);
        std::vector<float> L_heights(n1), R_heights(n2);
        for (int i = 0; i < n1; i++) {
            L[i] = arr[left + i];
            L_heights[i] = rectangles[left + i].getSize().y;
        }
        for (int i = 0; i < n2; i++) {
            R[i] = arr[mid + 1 + i];
            R_heights[i] = rectangles[mid + 1 + i].getSize().y;
        }
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            while (std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                    return;
                }
            }
            rectangles[k].setFillColor(sf::Color::Red);
            float pitch = generatePitch(rectangles, k);
            sorting.setPitch(pitch);
            sorting.setVolume(50);
            sorting.play();
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                rectangles[k].setSize({rectangles[k].getSize().x, L_heights[i]});
                i++;
            } else {
                arr[k] = R[j];
                rectangles[k].setSize({rectangles[k].getSize().x, R_heights[j]});
                j++;
            }
            rectangles[k].setPosition({rectangles[k].getPosition().x, win_height - rectangles[k].getSize().y});
            window.clear();
            for (const auto& rect : rectangles) {
                window.draw(rect);
            }
            window.display();
            sf::sleep(sf::milliseconds(speed));
            rectangles[k].setFillColor(sf::Color::White);
            k++;
        }
        while (i < n1) {
            arr[k] = L[i];
            rectangles[k].setSize({rectangles[k].getSize().x, L_heights[i]});
            rectangles[k].setPosition({rectangles[k].getPosition().x, win_height - rectangles[k].getSize().y});
            i++;
            k++;
        }
        while (j < n2) {
            arr[k] = R[j];
            rectangles[k].setSize({rectangles[k].getSize().x, R_heights[j]});
            rectangles[k].setPosition({rectangles[k].getPosition().x, win_height - rectangles[k].getSize().y});
            j++;
            k++;
        }
    }
}
