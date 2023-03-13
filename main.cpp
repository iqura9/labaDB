#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

// Function to print the help message for the db command
void printDbHelp() {
    std::cout << "Usage: db [command]" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  --help        Display this help message" << std::endl;
    std::cout << "  insert-s      Insert a new record with FullName and GroupId" << std::endl;
    std::cout << "  insert-m      Insert a new record with GroupName" << std::endl;
    std::cout << "  ut-s          Show all records of type s" << std::endl;
    std::cout << "  ut-m          Show all records of type m" << std::endl;
    std::cout << "  calc-s        Show the count of records of type s" << std::endl;
    std::cout << "  calc-m        Show the count of records of type m" << std::endl;
    std::cout << "  update-s      Update a record of type s" << std::endl;
    std::cout << "  update-m      Update a record of type m" << std::endl;
    std::cout << "  del-s         Delete a record of type s" << std::endl;
    std::cout << "  del-m         Delete a record of type m" << std::endl;
    std::cout << "  get-s         Get a record of type s by ID" << std::endl;
    std::cout << "  get-m         Get a record of type m by ID" << std::endl;
}

const std::string mFilename = "m_records.txt";
const std::string sFilename = "s_records.txt";
const std::string tempSFilename = "temp_s_records.txt";
const std::string tempMFilename = "temp_m_records.txt";
const std::string garbageFilename = "garbage.txt";

int getNextMId() {
    std::ifstream inFile(mFilename);
    int lastId = 0;
    int id;
    std::string groupName;
    while (inFile >> id >> groupName) {
        if (id > lastId) {
            lastId = id;
        }
    }
    inFile.close();
    return lastId + 1;
}
int getNextSId() {
    std::ifstream inFile(sFilename);
    int lastId = 0;
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        int id;
        ss >> id;
        if (id > lastId) {
            lastId = id;
        }
    }
    inFile.close();
    return lastId + 1;
}

// Function to insert a new record of type s
void insertS() {
    std::string fullName;
    int groupId;
    std::cout << "Enter FullName: ";
    std::getline(std::cin, fullName);
    std::cout << "Enter GroupId: ";
    std::cin >> groupId;

    int id = getNextSId();
    std::ofstream outFile(sFilename, std::ios::app);
    outFile << id << " " << fullName << " " << groupId << "\n";
    outFile.close();

    std::cout << "Student record added with ID " << id << "\n";
}

struct MRecord {
    int id;
    std::string groupName;
};

// Function to insert a new record of type m
void insertM() {
    MRecord record;

    record.id = getNextMId();

    std::cout << "Please enter the following information:" << std::endl;
    std::cout << "Group Name: ";
    std::getline(std::cin, record.groupName);

    // Save changes to file
    std::ofstream outFile(mFilename, std::ios::app);
    if (outFile) {
        outFile << record.id << " " << record.groupName << std::endl;
        std::cout << "Record inserted successfully" << std::endl;
    } else {
        std::cerr << "Error: Could not open file " << mFilename << " for writing" << std::endl;
    }
}



// Function to show the count of records of type s
void countS() {
    std::ifstream file("s_records.txt");
    if (!file) {
        std::cerr << "Error: Could not open file" << std::endl;
        return;
    }

    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        count++;
    }

    std::cout << "Total number of records of type s: " << count << std::endl;
}

// Function to show the count of records of type m
void countM() {
    std::ifstream file("m_records.txt");
    if (!file) {
        std::cerr << "Error: Could not open file" << std::endl;
        return;
    }

    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        count++;
    }

    std::cout << "Total number of records of type m: " << count << std::endl;
}

void getMById(int id) {


    std::ifstream file("m_records.txt");
    if (!file) {
        std::cerr << "Error: Could not open file" << std::endl;
        return;
    }

    // Search for the record with the given ID and output it
    std::string line;
    bool found = false;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int record_id;
        std::string name, group_id;
        iss >> record_id >> name >> group_id;

        if (record_id == id) {
            found = true;
            std::cout << "Group_Id: " << record_id << std::endl;
            std::cout << "Name: " << name << std::endl;
            break;
        }
    }

    if (!found) {
        std::cout << "Record not found." << std::endl;
    }
}

// Function to retrieve a record of type m
void getM() {
    std::cout << "Enter the ID of the record you want to retrieve: ";
    int id;
    std::cin >> id;

    // Open the file for reading
    std::ifstream file("m_records.txt");
    if (!file) {
        std::cerr << "Error: Could not open file" << std::endl;
        return;
    }

    // Search for the record with the given ID and output it
    std::string line;
    bool found = false;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int record_id;
        std::string name, group_id;
        iss >> record_id >> name >> group_id;

        if (record_id == id) {
            found = true;
            std::cout << "ID: " << record_id << std::endl;
            std::cout << "Name: " << name << std::endl;
            break;
        }
    }

    if (!found) {
        std::cout << "Record not found." << std::endl;
    }
}

void getS() {
    std::cout << "Enter the ID of the record you want to retrieve: ";
    int id;
    std::cin >> id;

    std::ifstream inFile(sFilename);

    if (!inFile) {
        std::cerr << "Error: Could not open file" << std::endl;
        return;
    }
    std::string fullName;
    bool found = false;
    while (getline(inFile, fullName)) {
        std::istringstream iss(fullName);
        int record_id;
        std::string name, group_id, second_name;

        iss >> record_id >> name >> second_name >> group_id;
        if(group_id == "") {
            group_id = second_name;
            second_name = "";
        }
        if (record_id == id) {
            std::cout << "ID: " << record_id << std::endl;
            std::cout << "Full Name: " << name <<" "<< second_name << std::endl;
            std::cout << "Group ID: " << group_id << std::endl;
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) {
        std::cout << "Record with ID " << id << " not found." << std::endl;
    }
}
void ut_m() {


    // Open the file for reading
    std::ifstream file("m_records.txt");
    if (!file) {
        std::cerr << "Error: Could not open file" << std::endl;
        return;
    }

    // Search for the record with the given ID and output it
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int record_id;
        std::string name;
        iss >> record_id >> name;
        std::cout << "ID: " << record_id << std::endl;
        std::cout << "Name: " << name << std::endl;
    }
}
void ut_s() {
    std::ifstream inFile(sFilename);
    if (!inFile) {
        std::cerr << "Error: Could not open file" << std::endl;
        return;
    }
    std::string fullName;
    while (getline(inFile, fullName)) {
        std::istringstream iss(fullName);
        int record_id;
        std::string name, second_name;
        string group_id;

        iss >> record_id >> name >> second_name >> group_id;
        if(group_id == "") {
            group_id = second_name;
            second_name = "";
        }

        std::cout << "ID: " << record_id << std::endl;
        std::cout << "Full Name: " << name <<" "<< second_name << std::endl;
        getMById(stoi(group_id));
    }
    inFile.close();
}

void deleteS(int id) {
    // Open input and output files
    std::ifstream inFile(sFilename);
    std::ofstream outFile(tempSFilename);
    std::ofstream garbageFile(garbageFilename, std::ios::app);

    // Check if files were opened successfully
    if (!inFile) {
        std::cerr << "Error: Could not open input file for reading\n";
        return;
    }
    if (!outFile) {
        std::cerr << "Error: Could not open output file for writing\n";
        return;
    }
    if (!garbageFile) {
        std::cerr << "Error: Could not open garbage file for writing\n";
        return;
    }

    string line;

    bool foundRecord = false;
    while (getline(inFile, line)){
        std::istringstream iss(line);
        int record_id;
        std::string name, group_id, second_name;
        iss >> record_id >> name >> second_name >> group_id;
        if(group_id == "") {
            group_id = second_name;
            second_name = "";
        }
        if (record_id == id) {
            // Record matches the ID to be deleted, add it to garbage file
            garbageFile << record_id << ' ' << name << ' ' << second_name << ' ' << group_id << '\n';
            foundRecord = true;
        } else {
            // Record does not match the ID to be deleted, copy to output file
            outFile << record_id << ' ' << name << ' ' << second_name  << ' ' << group_id << '\n';
        }
    }

    // Close input and output files
    inFile.close();
    outFile.close();
    garbageFile.close();

    // Rename output file to input file
    std::rename(tempSFilename.c_str(), sFilename.c_str());

    // Print message indicating whether record was found and deleted
    if (foundRecord) {
        std::cout << "Record with ID " << id << " deleted successfully\n";
    } else {
        std::cout << "Record with ID " << id << " not found\n";
    }
}

void deleteM() {
    std::cout << "Enter ID to delete: ";
    string id;
    std::cin >> id;

    // Delete record from m_records.txt
    std::ifstream mInFile(mFilename);
    std::ofstream tempMFile("tempM.txt");
    string mId;
    std::string mName;
    while (mInFile >> mId >> mName) {
        if (mId != id) {
            tempMFile << mId << " " << mName << std::endl;
        }
        else {
            // Record is associated with the deleted group, add it to garbage.txt
            std::ofstream garbageFile("garbage.txt", std::ios_base::app);
            garbageFile << mId << " " << mName << std::endl;
            garbageFile.close();
        }
    }
    mInFile.close();
    tempMFile.close();
    std::remove(mFilename.c_str());
    std::rename("tempM.txt", mFilename.c_str());

    // Delete associated records from s_records.txt
    std::ifstream sInFile(sFilename);
    std::ofstream tempSFile("tempS.txt");
    std::string sFullName;
    string sGroupId;
    string line;
    while (getline(sInFile, line)) {
        std::istringstream iss(line);
        string sId;
        std::string name, group_id, second_name;
        iss >> sId >> name >> second_name >> sGroupId;

        if(sGroupId == "") {
            sGroupId = second_name;
            second_name = "";
        }
        string sFullName = name + " " + second_name;
        if (sGroupId != id) {
            tempSFile << sId << " " << sFullName << " " << sGroupId << std::endl;
        } else {
            // Record is associated with the deleted group, add it to garbage.txt
            std::ofstream garbageFile("garbage.txt", std::ios_base::app);
            garbageFile << sId << " " << sFullName << " " << sGroupId << std::endl;
            garbageFile.close();
        }
    }
    sInFile.close();
    tempSFile.close();
    std::remove(sFilename.c_str());
    std::rename("tempS.txt", sFilename.c_str());
    std::cout << "Record deleted successfully!" << std::endl;
}
void updateM() {
    int id;
    std::cout << "Enter ID: ";
    std::cin >> id;

    // Find the record with the specified ID
    std::ifstream inFile(mFilename);
    int currentId;
    std::string name;
    bool recordFound = false;
    while (inFile >> currentId >> name) {
        if (currentId == id) {
            recordFound = true;
            break;
        }
    }
    inFile.close();

    if (!recordFound) {
        std::cout << "Record with ID " << id << " not found." << std::endl;
        return;
    }

    std::cout << "Enter new Name: ";
    std::string newName;
    std::cin >> newName;

    // Update the record with the new name
    std::ifstream tempInFile(mFilename);
    std::ofstream outFile(tempMFilename);
    while (tempInFile >> currentId >> name) {
        if (currentId == id) {
            outFile << currentId << " " << newName<< std::endl;
        } else {
            outFile << currentId << " " << name << std::endl;
        }
    }
    tempInFile.close();
    outFile.close();

    // Rename output file to input file
    std::rename(tempMFilename.c_str(), mFilename.c_str());

    std::cout << "Record with ID " << id << " updated." << std::endl;
}
void updateS() {
    string id;
    std::cout << "Enter ID: ";
    std::cin >> id;

    // Find the record with the specified ID
    std::ifstream inFile(sFilename);
    std::string name;
    string globalGroupId;
    string globalName;
    bool recordFound = false;
    string line;
    while (getline(inFile, line)) {
        std::istringstream iss(line);
        string sId;
        std::string name, group_id, second_name;
        iss >> sId >> name >> second_name >> group_id;
        if (group_id == "") {
            group_id = second_name;
            second_name = "";
        }
        if (sId == id) {
            globalName = name + " " + second_name;
            globalGroupId = group_id;
            recordFound = true;
            break;
        }
    }
    inFile.close();

    if (!recordFound) {
        std::cout << "Record with ID " << id << " not found." << std::endl;
        return;
    }

    std::cout << "Enter new GroupId: "<<"["<<globalGroupId<<"] ";
    std::string newGroupId;
    std::cin >> newGroupId;

    std::cout << "Enter new Name: "<<"["<<globalName<<"] ";
    std::string newName;
    std::cin.ignore();
    std::getline(std::cin, newName);

    // Update the record with the new name
    std::ifstream tempInFile(sFilename);
    std::ofstream outFile(tempSFilename);
    string linex;
    while (getline(tempInFile, linex)) {
        std::istringstream iss(linex);
        string sId;
        std::string name, group_id, second_name;
        iss >> sId >> name >> second_name >> group_id;
        if (group_id == "") {
            group_id = second_name;
            second_name = "";
        }
        string fullName = name + " " + second_name;
        if (sId == id) {
            outFile << sId << " " << newName << " " << newGroupId << std::endl;
        } else {
            outFile << sId << " " << fullName << " " <<group_id<< std::endl;
        }
    }
    tempInFile.clear(); // reset error flags
    tempInFile.seekg(0); // set file pointer to beginning of file
    tempInFile.close();
    outFile.close();

    // Rename output file to input file
    std::rename(tempSFilename.c_str(), sFilename.c_str());

    std::cout << "Record with ID " << id << " updated." << std::endl;
}


int cli(bool &start){
    //args
    string input;
    getline(cin, input);

    stringstream ss(input);
    const int maxArgs = 3;
    std::string argc[maxArgs];
    int argCount = 0;

    std::string token;
    while (std::getline(ss, token, ' ')) {
        if (argCount < maxArgs) {
            argc[argCount++] = token;
        }
    }
    //

    string command = argc[0];
    if(command == "exit") start = false;
    if(command=="db"){
        string subcommand = argc[1];
        if (subcommand == "--help") {
            printDbHelp();
        }
        else if (subcommand == "insert-s") {
            insertS();
        } else if (subcommand == "insert-m") {
            insertM();
        } else if (subcommand == "update-s") {
            updateS();
        } else if (subcommand == "update-m") {
            updateM();
        } else if (subcommand == "get-s") {
            getS();
        } else if (subcommand == "get-m") {
            getM();
        } else if (subcommand == "del-s") {
            std::cout << "Enter the ID of the record you want to retrieve: ";
            int id;
            std::cin >> id;
            deleteS(id);
        } else if (subcommand == "del-m") {
            deleteM();
        } else if (subcommand == "calc-s") {
            countS();
        } else if (subcommand == "calc-m") {
            countM();
        } else if (subcommand == "ut-m") {
            ut_m();
        } else if (subcommand == "ut-s") {
            ut_s();
        } else {
            std::cerr << "Error: Invalid subcommand" << std::endl;
            return 1;
        }
    }
}

int main() {
    bool start = true;
    while(start){
        cout<<">> ";
        cli(start);
        cout<<endl;
    }
    return 0;
}