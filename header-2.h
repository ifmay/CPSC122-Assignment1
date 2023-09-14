/*
Name: Izzy May
Class: CPSC 122, Fall 2023
Programming Assignment 1
Notes: Not completed but will work on this more before Wednesday.
*/

// Guard code to prevent code being used more than once
#ifndef HEADER_H

#define HEADER_H


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <ctime>


using namespace std;


struct PetData{
string petStore;
string petName;
string petType;
int daysAtStore;
};


// Function Prototypes
bool openInputFile(const string& filename, ifstream& inputFile);
bool openOutputFile(string filename, ofstream& outputFile);
void parseFileData(ifstream& inputFile, vector<PetData>& petDataList);
void listPetStores(const vector<PetData>& petDataList, ofstream& outputFile);
int findTotalNumberOfPets(const vector<PetData>& petDataList);
string findStoreWithMostPets(const vector<PetData>& petDataList);
void findPetsAtMostFrequentStore(const vector<PetData>& petDataList, ofstream& outputFile);
double calculateAverageDays(const vector<PetData>& petDataList);
PetData pickRandomPet(const vector<PetData>& petDataList);

#endif // !HEADER_H
