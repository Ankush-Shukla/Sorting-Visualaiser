#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

inline bool loadBeepSound(sf::SoundBuffer& buffer, const std::string& filename) {
    if (!buffer.loadFromFile(filename)) {
        std::cerr << "Error loading sound file: " << filename << std::endl;
        return false;
    }
    return true;
}
