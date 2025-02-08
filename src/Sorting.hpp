#include<iostream>
#include <algorithm>  // For std::shuffle
#include <random>     // For std::random_device and std::mt19937
#include <vector>
void bubble_sort(int arr[], std::vector<sf::RectangleShape>& rectangles, sf::RenderWindow& window, float win_height) {
    int n = rectangles.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap values in array
                std::swap(arr[j], arr[j + 1]);

                // Swap corresponding rectangles' heights
                float temp_height = rectangles[j].getSize().y;
                rectangles[j].setSize({rectangles[j].getSize().x, rectangles[j + 1].getSize().y});
                rectangles[j + 1].setSize({rectangles[j + 1].getSize().x, temp_height});

                // Update rectangle positions to align from the bottom
                rectangles[j].setPosition(sf::Vector2<float>(rectangles[j].getPosition().x, win_height - rectangles[j].getSize().y));
                rectangles[j + 1].setPosition(sf::Vector2<float>(rectangles[j + 1].getPosition().x, win_height - rectangles[j + 1].getSize().y));

                // Clear and redraw window after each swap
                window.clear();
                for (const auto& rect : rectangles) {
                    window.draw(rect);
                }
                window.display();

                // **Increase delay here** to slow down sorting
                sf::sleep(sf::milliseconds(500));  // Try 200ms or higher for a slower effect
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

