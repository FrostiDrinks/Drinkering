#pragma once
#include <vector>

namespace Drink {

	class Bottle;

	class Water {
		Bottle* _bottles;
		int _size;
	public:
		Water();
		~Water();
		void menu();
		void display();
		void addBottle();
		int getRand() const;
	};

	class Bottle{
		char* _name;
		int _vol;
		int _abv;
	public:
		Bottle();
		~Bottle();
		void display();
		const char* getName() const { return _name; }
		void getValues();
		void setValues(const char* name, int vol, float abv);
		int takeShot();
		bool isEmpty() const { return !_vol; }
	};
}