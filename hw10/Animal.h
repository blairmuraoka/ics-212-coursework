#ifndef Animal_h
#define Animal_h

#include <iostream>
#include <vector>

using namespace std;

//Base class
class Animal
{
	public:
		virtual void displayData() = 0;
	protected:
		string sound; // contains "moo", "quack"
		unsigned int numLegs;
};

class Cow : public Animal
{
	public:
		Cow();
		~Cow();
		void displayData();
};

class Duck : public Animal
{
	public:
		Duck();
		~Duck();
		void displayData();
};

class Cat : public Animal
{
	public:
		Cat();
		~Cat();
		void displayData();
};
#endif
