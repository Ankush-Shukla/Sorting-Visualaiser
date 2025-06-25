**Sorting Visualizer**

A simple and interactive **Sorting Visualizer** built with C++ and SFML. Visualize how various sorting algorithms work in real-time and compare their performance on random datasets.

---

## 📋 Table of Contents

1. [Features](#-features)
2. [Algorithms Included](#-algorithms-included)
3. [Demo](#-demo)
4. [Prerequisites](#-prerequisites)
5. [Installation & Build](#-installation--build)
6. [Usage](#-usage)

   * [Controls](#controls)
   * [Customizing Array Size & Speed](#customizing-array-size--speed)
7. [Project Structure](#-project-structure)
8. [Contributing](#-contributing)
9. [License](#-license)

---

## 🔥 Features

* Visual simulation of popular sorting algorithms
* Adjustable array size and animation speed
* Pause, resume, and reset functionality
* Real-time comparison of algorithm performance
* Modular codebase, easy to extend with new algorithms

## 📊 Algorithms Included

* Bubble Sort
* Selection Sort
* Insertion Sort
* Merge Sort
* Quick Sort

## 🎬 Demo

> *Note: Replace with your own GIF or screenshot in the **********`assets/`********** directory.*

## ⚙️ Prerequisites

* C++ compiler with C++17 support
* [SFML 3.0.0](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library)

## 🚀 Installation & Build

1. **Clone the repository**

   ```bash
   git clone https://github.com/Ankush-Shukla/Sorting-Visualizer.git
   cd Sorting-Visualizer
   ```

2. **Install SFML**

   * On Ubuntu/Debian:

     ```bash
     sudo apt-get update
     sudo apt-get install libsfml-dev
     ```

   * On Windows:

     * Download the SFML SDK and follow the [official tutorial](https://www.sfml-dev.org/tutorials/3.0/start-vc.php) for Visual Studio.

3. **Build the project**

   * Using CMake (recommended):

     ```bash
     mkdir build && cd build
     cmake ..
     make    # or cmake --build .
     ```

   * Without CMake:

     ```bash
     g++ -std=c++17 -I<path_to_SFML>/include \
         src/*.cpp \
         -L<path_to_SFML>/lib -lsfml-graphics -lsfml-window -lsfml-system \
         -o SortingVisualizer
     ```

## ▶️ Usage

1. Run the executable generated during build:

   ```bash
   ./SortingVisualizer
   ```

### Controls

All interactions are via the on-screen buttons and sliders—there are no keyboard shortcuts

## 📁 Project Structure

```
Sorting-Visualizer/
├── assets/            # Images, GIFs, and other media
├── include/           # Header files
│   ├── Sorting.hpp    # Algorithms and utility functions
│   └── ...
├── src/               # Source files
│   ├── main.cpp       # Entry point and UI logic
│   ├── draw.hpp       # Rendering functions
│   └── logic.hpp      # Core visualization logic
├── build/             # CMake build directory (gitignored)
├── CMakeLists.txt     # CMake build script
└── README.md          # Project overview and instructions
```

## 🤝 Contributing

Contributions are welcome! To propose changes:

1. Fork the repository
2. Create your feature branch (`git checkout -b feature-name`)
3. Commit your changes (`git commit -m "Add feature"`)
4. Push to the branch (`git push origin feature-name`)
5. Open a Pull Request

Please ensure code clarity, add comments, and update tests or documentation if necessary.

## 📝 License

This project is licensed under the **MIT License**. See `LICENSE` for details.
