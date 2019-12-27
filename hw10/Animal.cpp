/**
 * Name:        Blair Muraoka
 * Homework:    10
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        12-08-2016
 * File:        Animal.cpp
 * 
 * Description: Contains the definitions of the different types of animals. For my code, I chose to use a cow, duck
 *				and cat as the three types. Each has a constructor that initializes the sound/numLegs to their
 *				appropriate values, and have their own displayData method based on the type. All method prototypes
 *				are located in Animal.h.
 */
#include "Animal.h"

Cow::Cow()
{
	sound   = "Moo";
	numLegs = 4;
}

void Cow::displayData()
{
	cout << "Cow: \n";
	cout << "Sound: " << sound << "\n";
	cout << "No. Legs: " << numLegs << "\n";
}


Duck::Duck()
{
	sound   = "Quack";
	numLegs = 2;
}


void Duck::displayData()
{
	cout << "Duck: \n";
	cout << "Sound: " << sound << "\n";
	cout << "No. Legs: " << numLegs << "\n";
}


Cat::Cat()
{
	sound   = "Meow";
	numLegs = 4;
}

void Cat::displayData()
{
	cout << "Cat: \n";
	cout << "Sound: " << sound << "\n";
	cout << "No. Legs: " << numLegs << "\n";
}
