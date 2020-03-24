#include <iostream>
#include <cstdlib>
#include <string>
#include "Drink.h"

namespace Drink {

	template<typename Box>
	Box getNumeral() {
		Box val;
		for (;;) {
			std::cin >> val;
			std::cin.ignore(1000, '\n');

			if (!std::cin) {
				std::cin.clear();
				std::cout << "Please enter a valid number: ";
				std::cin.ignore(1000, '\n');
			}
			else break;
		}
		return val;
	}

	Water::Water() {
		_bottles = new Bottle[10];
		_size = 0;
	}

	Water::~Water() {
		delete[] _bottles;
		_bottles = nullptr;
	}

	void Water::menu() {
		bool looper = false;
		for (;;) {
			std::cout << "What would you like to do?" << std::endl
					  << "1) Add a bottle" << std::endl
					  << "2) Take a shot" << std::endl
					  << "3) View the collection" << std::endl
					  << "4) Exit the program" << std::endl << std::endl;

			switch (getNumeral<int>()) {
			case 1:
				addBottle();
				break;

			case 2: {
				int i = getRand();
				if (i == -1) break;

				int shot = _bottles[i].takeShot();
				const char* name = _bottles[i].getName();

				if (!shot) {
					std::cout << "You have nothing left to drink!" << std::endl;
					break;
				}
				std::cout << "The gods have decided for you to drink "
					<< shot << "ml of " << name << ", good luck!"
					<< std::endl << std::endl
					<< "Press Enter to continue";

				std::cin.get();
				std::cout << std::endl;
				if (_bottles[i].isEmpty())
					std::cout << "Wow, you finished the whole bottle!" << std::endl;
				break;
			}
			case 3:
				if (!_size) std::cout << "Please add a bottle first." << std::endl;
				else display();
				break;

			case 4:
				looper = true;
				break;
			}
			std::cout << std::endl;
			if (looper) break;
		}
	}

	void Water::display() {
		for (int i = 0; i < _size; _bottles[i].display(), i++);
	}

	void Water::addBottle() {
		_bottles[_size] = Bottle();
		_bottles[_size++].getValues();
	}

	int Water::getRand() const {
		if (!_size) { 
			std::cout << "You can't take a shot from nothing, can you?" << std::endl; 
			return -1; 
		}
		else return rand() % _size;
	}

	Bottle::Bottle() {
		_name = nullptr;
		_vol = 0;
		_abv = 0;
	}

	Bottle::~Bottle() {
		delete[] _name;
		_name = nullptr;
	}

	void Bottle::display() {
		std::cout << "===========================" << std::endl;
		std::cout << _name << " | ";
		std::cout << _vol << "ml | ";
		std::cout << _abv << " %" << std::endl;
	}

	void Bottle::getValues() {
		char temp[128];
		std::cout << "Enter bottle name: ";

		std::cin.getline(temp, 128);
		_name = new char[strlen(temp) + 1];
		strcpy_s(_name, strlen(temp) + 1, temp);

		std::cout << "Enter volume in ml: ";
		_vol = getNumeral<int>();

		std::cout << "Enter ABV: ";
		_abv = getNumeral<float>();
	}

	void Bottle::setValues(const char* name, int vol, float abv) {
		if (!name) _name = nullptr;
		else {
			_name = new char[strlen(name) + 1];
			strcpy_s(_name, strlen(name) + 1, name);
		}
		_vol = vol;
		_abv = abv;
	}

	int Bottle::takeShot() {
		int vol = rand() % 40 + 30;
		if (vol >= _vol) vol = _vol;
		_vol -= vol;
		return vol;
	}
}

int main() {
	std::cout << "Welcome to the epic drinking game!" << std::endl;
	Drink::Water a = Drink::Water();
	a.menu();

	std::cout << "Goodbye my alcoholic friend!" << std::endl;
	return 0;
}
