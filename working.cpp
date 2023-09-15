#include <iostream>
#include <sstream>
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

/************************************************************
* Function: openInputFile()
* Date Created: 9/4/23
* Date Last Modified: 9/10/23
* Description: This function opens the input file and 
  returns an error message if it is unsuccessful.
* Input parameters: The file name and object that will read it
* Returns: true if file is opened (code continues) or false if
  unable to open the file (error message).
* Pre: The input file name must be provided.
* Post: The input file is opened.
*************************************************************/

bool openInputFile(const string& filename, ifstream& inputFile){
    inputFile.open(filename);

    if (!inputFile.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return false; 
    }

    return true;
}

/************************************************************
* Function: openOutputFile()
* Date Created: 9/4/23
* Date Last Modified: 9/10/23
* Description: This function opens the output file and 
  returns an error message if it is unsuccessful.
* Input parameters: The file name and object that will read it
* Returns: true if file is opened (code continues) or false if
  unable to open the file (error message).
* Pre: The output file name must be provided.
* Post: The output file is opened.
*************************************************************/

bool openOutputFile(string filename, ofstream& outputFile){
    outputFile.open(filename);

    if (!outputFile.is_open()) {
        cout << "Failed to open output file: " << filename << endl;
        return false; 
    }

    return true;
}

/************************************************************
* Function: parseFileData()
* Date Created: 9/6/23
* Date Last Modified: 9/10/23
* Description: This function parses the pet data from the input 
  file into a vector to be useed in the program.
* Input parameters: File name and pet data from CSV file
* Returns: Does not return anything. Performs task of getting data
  from the input file into the program. 
* Pre: The CSV file must contain pet data in this format:
  Pet Store,Pet Name,Pet Type,Days at Store
* Post: Pet data is stored into vectors to be used later in the
  program.
*************************************************************/

void parseFileData(ifstream& inputFile, vector<PetData>& petDataList){
    // Read in and ignore the header line
    string header;
    getline(inputFile, header); 

    vector<string> petStoreNames;
    vector<string> petNames;
    vector<string> petTypes;
    vector<int> numDaysAtStore;

    // loop to read file line by line and store in a vector
    while (!inputFile.eof()) {
        string line;
        getline(inputFile, line);

        stringstream lineStream(line);
        string storeName, petName, petType;
        int daysAtStore;

        getline(lineStream, storeName, ',');
        getline(lineStream, petName, ',');
        getline(lineStream, petType, ',');
        lineStream >> daysAtStore;

        // Create a PetData struct and store the data in the vector
        PetData petData = { storeName, petName, petType, daysAtStore};
        petDataList.push_back(petData);

        cout << "Processed a " << petType << ", \"" << petName << "\" ... " << daysAtStore << " day(s) on site at store \"" << storeName << "\"" << endl;
    }
    cout << "All pet store data processed!" << endl << endl;
}


/************************************************************
* Function: listPetStores()
* Date Created: 9/6/23
* Date Last Modified: 9/10/23
* Description: This function finds all of the pet store names 
  in the data set and lists them in the output file.
* Input parameters: PetData vector, and output file name
* Returns: Does not return anything. Performs task of finding 
  pet store names from the input file and writing them to the
  output file.
* Pre: The PetData vector must be populated with information.
* Post: The list of pet store names are listed in the output file.
*************************************************************/

void listPetStores(const vector<PetData>& petDataList, ofstream& outputFile) {
    unordered_set<string> uniqueStores;

    // Collect unique store names
   for (int i = 0; i < petDataList.size(); ++i) {
        const PetData& petData = petDataList[i];
        uniqueStores.insert(petData.petStore);
    }

    outputFile << "Pet Stores: ";
    bool firstStore = true; // To handle comma and space formatting

    for (const string& store : uniqueStores) {
        if (!firstStore) {
            outputFile << ", "; // Add comma and space if not the first store
        }
        outputFile << store;
        firstStore = false;
    }

    outputFile << endl;
}

/************************************************************
* Function: findTotalNumberOfPets()
* Date Created: 9/6/23
* Date Last Modified: 9/10/23
* Description: This function counts the total number of pets
  in the input file and returns the integer value.
* Input parameters: PetData vector
* Returns: integer totalPets with the total number of pets
* Pre: The PetData vector must be populated with information.
* Post: The number of pets is returned as an integer
*************************************************************/

int findTotalNumberOfPets(const vector<PetData>& petDataList){
    int totalPets = 0;

    for (const PetData& petData : petDataList) {
        totalPets++;
    }

    return totalPets;
}

/************************************************************
* Function: findStoreWithMostPets()
* Date Created: 9/6/23
* Date Last Modified: 9/10/23
* Description: This function finds the store with the most pets
  in the input file and returns it as a string.
* Input parameters: PetData vector
* Returns: string mostFrequent store with the store with most pets.
* Pre: The PetData vector must be populated with information.
* Post: The store with the most pets is returned as an string.
*************************************************************/

string findStoreWithMostPets(const vector<PetData>& petDataList) {
    if (petDataList.empty()) {
        return "No data available.";
    }

    // Create a map to count pets by store
    unordered_map<string, int> storeCounts;

    // Count pets for each store
    for (const PetData& petData : petDataList) {
        storeCounts[petData.petStore]++;
    }

    // Find the store with the maximum pet count
    string mostFrequentStore;
    int maxCount = 0;

    for (const auto& pair : storeCounts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequentStore = pair.first;
        }
    }

    return mostFrequentStore;
}

/************************************************************
* Function: findPetsAtMostFrequentStore()
* Date Created: 9/6/23
* Date Last Modified: 9/10/23
* Description: This function counts the total number of pets
  at the most frequent store from data in the input file.
* Input parameters: PetData vector
* Returns: void function does not return anything. Rather finds the amount
* of pets at the most frequent store and prints it to the output file.
* Pre: The PetData vector must be populated with information.
* Post: The number of pets at the most frequent store is printed to
* the output file.
*************************************************************/

void findPetsAtMostFrequentStore(const vector<PetData>& petDataList, ofstream& outputFile) {
    string mostFrequentStore = findStoreWithMostPets(petDataList);

    int count = 0;

    for (const PetData& petData : petDataList) {
        if (petData.petStore == mostFrequentStore) {
            count++;
        }
    }

    outputFile << "Number of pets at " << mostFrequentStore << ": " << count << endl;
}

/************************************************************
* Function: calculateAverageDays()
* Date Created: 9/6/23
* Date Last Modified: 9/10/23
* Description: This function calculates the average number of days
* pets are at their respective stores.
* Input parameters: PetData vector
* Returns: average amount of days pets spend at their store as a double
* Pre: The PetData vector must be populated with information.
* Post: The average number of days pets spend at their respective stores
* is calculated and returned as a double.
*************************************************************/

double calculateAverageDays(const vector<PetData>& petDataList){
    if (petDataList.empty()) {
        return 0.0; // Return 0 if the vector is empty
    }

    int sum = 0;
    for (const PetData& petData : petDataList) {
        sum += petData.daysAtStore;
    }

    return static_cast<double>(sum) / petDataList.size();
}

/************************************************************
* Function: pickRandomPet()
* Date Created: 9/6/23
* Date Last Modified: 9/10/23
* Description: This function picks a random pet from the input file 
* Input parameters: PetData vector
* Returns: integer totalPets with the total number of pets
* Pre: The PetData vector must be populated with information.
* Post: The number of pets is returned as an integer to be used in
  succeeding functions.
*************************************************************/

PetData pickRandomPet(const vector<PetData>& petDataList) {
    srand(static_cast<unsigned int>(time(nullptr)));

    int randomIndex = rand() % petDataList.size();

    return petDataList[randomIndex];
}
