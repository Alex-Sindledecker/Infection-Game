#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>

#define W_WIDTH 900
#define W_HEIGHT 600

#define Z_AXIS 0
#define Y_AXIS 1
#define X_AXIS 2

#define PI 3.141592654f

template<class N>
inline void print(N x) {
	std::cout << x << std::endl;
}

inline void pause() {
	int _x;
	std::cin >> _x;
}

inline float radians(float deg) {
	return (PI / 180) * deg;
}

struct mat2 {
public:
	mat2(float scale) {
		data[0][0] = scale;
		data[1][1] = scale;
	}
	mat2() {}
	mat2& rotate(float theta, int axis) {
		if (axis == Z_AXIS) {
			mat2 rotationMatrix;
			rotationMatrix[0][0] = cos(radians(theta));
			rotationMatrix[0][1] = -sin(radians(theta));
			rotationMatrix[1][0] = sin(radians(theta));
			rotationMatrix[1][1] = cos(radians(theta));
			return rotationMatrix * *this;
		}
		else if (axis == Y_AXIS) {

		}
		else if (axis == Z_AXIS) {

		}
	}
	float* operator[](int value) {
		return data[value];
	}
	mat2& operator*(mat2& data) {
		mat2 dotProduct(1.f);
		dotProduct[0][0] = this->data[0][0] * data[0][0] + this->data[0][1] * data[1][0];
		dotProduct[0][1] = this->data[0][0] * data[0][1] + this->data[0][1] * data[1][1];
		dotProduct[1][0] = this->data[1][0] * data[0][0] + this->data[1][1] * data[1][0];
		dotProduct[1][1] = this->data[1][0] * data[0][1] + this->data[1][1] * data[1][1];
		return dotProduct;
	}
private:
	float data[2][2] = { { 0, 0 }, { 0, 0 } };
};