/**
 * Name:        Blair Muraoka
 * Homework:    10
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        12-08-2016
 * File:        main.cpp
 * 
 * Description: This file contains the driver function and a function "displayAnimalData" to 
 *				demonstrate polymorphism.
 */
#include "Animal.h"

// Prototypes
void displayAnimalData(Animal *);


// Functions
/** 
 * Function name:   displayAnimalData 
 * Description:     Takes an animal object and calls it's respective displayData() method.
 * Parameters:		a - animal being printed to console
 */
void displayAnimalData(Animal * a)
{
	a-> displayData();
}

/** 
 * Function name:   main 
 * Description:     Driver function. Creates a vector of type Animal* as a container to store instances of
 *					the Animal class in. Iterates through the vector to print all data to console, then iterates
 *					n times when deleting those instances.
 */
int main(int argc, char * argv[])
{
	int i;
	vector<Animal *> blaireVector;
	
	blaireVector.reserve(3);
	
	blaireVector.push_back(new Cow());
	blaireVector.push_back(new Duck());
	blaireVector.push_back(new Cat());
	
	for (i = 0; i < blaireVector.size(); i++)
	{
		displayAnimalData(blaireVector[i]);
		cout << "\n";
	}
	
	// Cleanup
	while (blaireVector.size() != 0)
	{
		delete blaireVector[0];
		blaireVector.erase(blaireVector.begin());
	}
	cout << "size: " << blaireVector.size() << "\n";
	
	return 0;
}
