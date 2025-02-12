#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>  
#include <vector>
#include<random>
#include <algorithm>
#include <iostream>  
#include <memory>  // ✅ Required for std::unique_ptr

void generateTone(sf::SoundBuffer &buffer, float frequency, float duration = 0.2f, int sampleRate = 44100) {
    int sampleCount = static_cast<int>(sampleRate * duration);
    std::vector<std::int16_t> samples(sampleCount);

    for (int i = 0; i < sampleCount; i++) {
        float amplitude = 30000; // Volume
        samples[i] = static_cast<std::int16_t>(amplitude * std::sin(2 * 3.14159265 * frequency * i / sampleRate));
    }

    unsigned int channelCount = 2;  
    std::vector<sf::SoundChannel> channelMap = {sf::SoundChannel::FrontLeft, sf::SoundChannel::FrontRight};

    if (!buffer.loadFromSamples(samples.data(), sampleCount, channelCount, sampleRate, channelMap)) {
        std::cerr << "Error loading sound buffer!\n";
    }
}

void bubble_sort(int arr[], std::vector<sf::RectangleShape>& rectangles, sf::RenderWindow& window, float win_height) {
    std::srand(std::time(0));
    int n = rectangles.size();

    // ✅ Fix: Use unique_ptr to store sounds
    std::vector<std::unique_ptr<sf::Sound>> sounds;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            while (std::optional<sf::Event> event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }

            // Generate a tone based on height
            float frequency = 200 + (rectangles[j].getSize().y / win_height) * 800;
            sf::SoundBuffer buffer;
            generateTone(buffer, frequency);

            // ✅ Fix: Use unique_ptr for sf::Sound
            sounds.emplace_back(std::make_unique<sf::Sound>(buffer));
            sounds.back()->play();

            std::cout << "Playing sound with frequency: " << frequency << " Hz\n";

            rectangles[j].setFillColor(sf::Color::Red);
            rectangles[j + 1].setFillColor(sf::Color::Red);

            window.clear();
            for (const auto& rect : rectangles) window.draw(rect);
            window.display();

            sf::sleep(sf::milliseconds(1000 / n));

            rectangles[j].setFillColor(sf::Color::White);
            rectangles[j + 1].setFillColor(sf::Color::White);

            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);

                float temp_height = rectangles[j].getSize().y;
                rectangles[j].setSize({rectangles[j].getSize().x, rectangles[j + 1].getSize().y});
                rectangles[j + 1].setSize({rectangles[j + 1].getSize().x, temp_height});

                rectangles[j].setPosition({rectangles[j].getPosition().x, win_height - rectangles[j].getSize().y});
                rectangles[j + 1].setPosition({rectangles[j + 1].getPosition().x, win_height - rectangles[j + 1].getSize().y});
            }
        }
    }
}


void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
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

