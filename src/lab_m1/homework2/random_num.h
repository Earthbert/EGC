#pragma once
#include <random>

class RandomNum {
public:
	RandomNum() {
		std::random_device randomDevice;
		randomEngine = std::mt19937(randomDevice());
	}

	int getRandomInt(int min, int max) {
		std::uniform_int_distribution distribution(min, max);
		return distribution(randomEngine);
	}

	float getRandomFloat(float min, float max) {
		std::uniform_real_distribution distribution(min, max);
		return distribution(randomEngine);
	}

private:
	std::mt19937 randomEngine;
};
