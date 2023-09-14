/*
 Name: Izzy May
 Class: CPSC 122, Fall 2023
 Programming Assignment 1
*/

/* Software Development Method
1. Specify problem requirements
2. Analyze the problem
3. Design an algorithm to solve the problem
4. Implement the algorithm
5. Test and verify the completed program
6. Maintain and update the program
*/

#include "header.h"

int main() {
vector<PetData> parsedDataList;

ifstream inputFile;
ofstream outputFile;

if (openInputFile("petstoredata.csv", inputFile)) {
    parseFileData(inputFile, parsedDataList);
    inputFile.close();
    }

cout << "Generating summary report... " << endl << endl;

string mostFrequentStore = findStoreWithMostPets(parsedDataList);

if (openOutputFile("petreport.txt", outputFile)) {
outputFile << "Pet Store CSV Summary Report" << endl;
outputFile << "----------------------------" << endl;
outputFile << " " << endl;

listPetStores(parsedDataList, outputFile);
int totalPets = findTotalNumberOfPets(parsedDataList);
outputFile << "Total number of pets: " << totalPets << endl;

outputFile << " " << endl;
outputFile << " " << endl;

outputFile << "Pet store with the most pets: " << mostFrequentStore << endl;
findPetsAtMostFrequentStore(parsedDataList, outputFile);

outputFile << " " << endl;
outputFile << " " << endl;

double averageDays = calculateAverageDays(parsedDataList);
outputFile << "Pet average days on site across all stores: " << static_cast<int>(averageDays) << endl;

PetData randomPet = pickRandomPet(parsedDataList);
outputFile << "Employee pet of the month choice: " << "\"" << randomPet.petName << "\"" << endl;

outputFile.close();

cout << "Done!" << endl;

}
}



