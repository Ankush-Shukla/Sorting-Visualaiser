# 🎨 Sorting Visualizer

An interactive and educational **Sorting Visualizer** built with **C++** and **SFML 3.0.0**. This tool allows users to observe how various sorting algorithms operate in real-time, with audio feedback and dynamic control over speed and data size.

---

## 📋 Table of Contents

1. [Features](#-features)
2. [Algorithms Included](#-algorithms-included)
3. [Demo](#-demo)
4. [Prerequisites](#-prerequisites)
5. [Installation & Build](#-installation--build)
6. [Usage](#-usage)

   * [Controls](#controls)
7. [Project Structure](#-project-structure)
8. [Contributing](#-contributing)
9. [License](#-license)
10. [Acknowledgments](#-acknowledgments)

---

## 🔥 Features

* 🎮 Real-time visual simulation of sorting steps
* 🎚 Adjustable array size and animation speed
* 🎛 On-screen buttons and sliders for interaction
* 🔁 Reset and replay capabilities
* 🔊 Audio feedback synced with data values
* 🧹 Modular C++17 code, easy to extend and maintain

---

## 📊 Algorithms Included

* Bubble Sort
* Selection Sort
* Insertion Sort
* Merge Sort
* Quick Sort

---

## 🎬 Demo

![Sorting Visualizer Demo](assets/demo.gif)

---

## ⚙️ Prerequisites

* C++17 or newer compiler
* [SFML 3.0.0](https://www.sfml-dev.org/) (Graphics, Window, System, Audio modules)
* `beep.wav` (sound feedback file)
* `arial.ttf` (font for text rendering)

---

## 🚀 Installation & Build

### 1. Clone the repository

```bash
git clone https://github.com/Ankush-Shukla/Sorting-Visualizer.git
cd Sorting-Visualizer
```

### 2. Install SFML

**Ubuntu/Debian:**

```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

**Windows:**

Download the SFML SDK and follow the [official Visual Studio tutorial](https://www.sfml-dev.org/tutorials/3.0/start-vc.php).

### 3. Place required assets

Ensure the following files are in the project root:

* `beep.wav`
* `arial.ttf`

### 4. Build the project

**Using CMake (recommended):**

```bash
mkdir build && cd build
cmake ..
make
```

**Without CMake:**

```bash
g++ -std=c++17 -I<path_to_SFML>/include \
    src/*.cpp \
    -L<path_to_SFML>/lib \
    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio \
    -o SortingVisualizer
```

> Replace `<path_to_SFML>` with your SFML installation directory.

---

## ▶️ Usage

Run the executable:

```bash
./SortingVisualizer
```

---

### Controls

* All interactions are via **on-screen buttons and sliders**
* No keyboard controls
* Use the GUI to:

  * Select a sorting algorithm
  * Adjust array size and animation speed
  * Start, pause, or reset the visualization

---

## 📁 Project Structure

```
Sorting-Visualizer/
├── assets/              # Images and demo media
├── include/             
│   ├── Sorting.hpp      # Sorting algorithms & utilities
│   ├── draw.hpp         # Rendering helpers
│   └── logic.hpp        # Visualization logic
├── src/                 
│   └── main.cpp         # Application entry point and UI logic
├── beep.wav             # Audio file for feedback
├── arial.ttf            # Font file for text
├── CMakeLists.txt       # CMake build script
├── build/               # CMake build output (gitignored)
└── README.md            # Project documentation
```

---

## 🤝 Contributing

1. Fork the repository

2. Create a feature branch:

   ```bash
   git checkout -b feature-name
   ```

3. Commit your changes:

   ```bash
   git commit -m "Add feature"
   ```

4. Push to the branch:

   ```bash
   git push origin feature-name
   ```

5. Open a Pull Request

> Please follow clean coding practices and document your code where necessary.

---

## 📝 License

This project is licensed under the **MIT License**.
See [`LICENSE`](LICENSE) for details.

---

## 🙌 Acknowledgments

* [SFML](https://www.sfml-dev.org/) for the multimedia framework
* The open-source community for inspiration
* Everyone using this visualizer to learn and teach sorting algorithms!
