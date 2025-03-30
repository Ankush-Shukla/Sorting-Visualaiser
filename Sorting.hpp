#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>  
#include <vector>
#include<random>
#include <algorithm>
#include <iostream>  
#include <memory> 
sf::SoundBuffer b("beep.wav");
sf::Sound sorting(b);

float generatePitch(std::vector<sf::RectangleShape>& rectangles, int j) {
    float max_height = 0;
    float relative_height = 0;
    for (const auto& rect : rectangles) {
        max_height = std::max(max_height, rect.getSize().y);
        relative_height = rectangles[j].getSize().y / max_height;


    }
    return 0.5f + 0.5f * relative_height;
}
void bubble_sort(int arr[], std::vector<sf::RectangleShape>& rectangles, sf::RenderWindow& window, float win_height) {
    int n = rectangles.size();




    for (int i = 0; i < n - 1; i++) {
        bool swapped = false; // Track if any swaps happen

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
            sf::sleep(sf::milliseconds(1000 / n + 25));

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

                swapped = true; // A swap occurred
            }
        }

        // If no swaps happened, the array is already sorted
        if (!swapped) {
            break;
        }
    }
}
void selection_sort(int arr[], std::vector<sf::RectangleShape>& rectangles, sf::RenderWindow& window, float win_height) {
    int n = rectangles.size();

    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        bool swapped = false;
        // Keep min_index as RED at start of each pass
        rectangles[min_index].setFillColor(sf::Color::Red);

        for (int j = i + 1; j < n; j++) {
            while (std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                    return;
                }
            }

            // Highlight the current element as GREEN
            rectangles[j].setFillColor(sf::Color::Green);

            float pitch = generatePitch(rectangles, j);

            int delay = std::max(5, 1000 / (n + 1));  // Ensure minimum delay
            sorting.setPitch(generatePitch(rectangles, j));
            sorting.setVolume(50);
            sorting.play();
            sf::sleep(sf::milliseconds(delay));



            // Render
            window.clear();
            for (const auto& rect : rectangles) {
                window.draw(rect);
            }
            window.display();

            sf::sleep(sf::milliseconds(50)); // Delay for visualization

            // If a smaller element is found, update min_index
            if (arr[j] < arr[min_index]) {

                min_index = j; // Update min_index (but keep both RED and GREEN until swap)
                rectangles[min_index].setFillColor(sf::Color::Red);
                swapped = true;
            }

            // Reset the traversing element (j) back to WHITE after comparison
            rectangles[j].setFillColor(sf::Color::White);
        }

        // Swap the found minimum element with the first unsorted element
        std::swap(arr[i], arr[min_index]);

        // Swap rectangle heights
        float temp_height = rectangles[i].getSize().y;
        rectangles[i].setSize({ rectangles[i].getSize().x, rectangles[min_index].getSize().y });
        rectangles[min_index].setSize({ rectangles[min_index].getSize().x, temp_height });

        // Adjust positions
        rectangles[i].setPosition({ rectangles[i].getPosition().x, win_height - rectangles[i].getSize().y });
        rectangles[min_index].setPosition({ rectangles[min_index].getPosition().x, win_height - rectangles[min_index].getSize().y });

        // Mark the sorted element as BLUE
        rectangles[i].setFillColor(sf::Color::White);
        // if (!swapped) {
        //     break;
        // }
    }

    // Mark the last element as sorted
    rectangles[n - 1].setFillColor(sf::Color::Blue);

}


void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[m + 1 + i];
    }
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void  merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}



std::vector<int> rand_array(int n) {
    srand(time(0));
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    std::random_device rd;  // Obtain a random seed
    std::mt19937 g(rd());   // Seed the random number generator
    std::shuffle(arr.begin(), arr.end(), g);
    return arr;
}
