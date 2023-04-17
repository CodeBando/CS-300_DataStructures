//============================================================================
// Name        : Project2_ABCU.cpp
// Author      : Matthew Bandyk
// Version     : 1.0
// Description : Project 2 Vector Data Structure for ABCU
// Last Updated: 4/15/2023 by Matthew Bandyk (MSB)
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes and global methods
//============================================================================

// Struct to hold the course information
struct Course {
    string courseNum;
    string name;
    vector<string> preReq;
    Course() {
    }
};

/* 
*  Method that will validate that a prereq course is part of the avaiable courses
*  Returns true if the course is part of the avaiable courses
*  False if it is not
* 
*  @param vector of parsed course data
*  @param string of the preReg course number to validate
*/
bool preReqValidation(vector<vector<string> > _courseData, string preReq) {
    int i;

    for (i = 0; i < _courseData.size(); ++i) {
        if (preReq == _courseData[i][0]) {
            return true;
        }
    }
    return false;
}

/*
* Method to compare vector index's, returning bool value if index a is less then or equal to b
* utilized by sort function to sort vector alphanumerically
* 
* @param index's of courses vector utilizing the Course Struct
*/
bool compareCourseNum(const Course& a, const Course& b) {
    return a.courseNum.compare(b.courseNum) <= 0;
}

/*
* Method to print the entire course vector in alphanumeric order
* first sorts the vector, then displays each course number and name to screen
* 
* @param courses vector of struct
*/
void printSampleSchedule(vector<Course> courses) {
    sort(courses.begin(), courses.end(), compareCourseNum);

    int size = courses.size();
    int i;
    //int j;

    cout << endl << endl << "Course Information: " << endl;
    cout << "-------------------" << endl;

    // iterate through the vector of struct and displaying each course number and name to the screen
    for (i = 0; i < size; ++i) {
        cout << courses.at(i).courseNum << ", " << courses.at(i).name << endl;
        /*
        * functionality to print preReqs with each course if needed
        */ 

        //if (!courses.at(i).preReq.empty()) {
        //    cout << " || Prerequisites: " << courses.at(i).preReq.at(0);
        //    for (j = 1; j < courses.at(i).preReq.size(); j++) {
        //        cout << ", " << courses.at(i).preReq.at(j);
        //    }
        //}
    }
    cout << endl;
    cout << endl;
}

/*
* Method to display the menu and capture user input for menu choice
*/
int displayMenu() {
    int num = 0;

    cout << "Menu:" << endl;
    cout << "  1. Load Courses" << endl;
    cout << "  2. Display Courses" << endl;
    cout << "  3. Find Course" << endl;
    cout << "  9. Exit" << endl;
    cout << "----------------------" << endl;
    cout << "Enter choice: " << endl;

    cin >> num;

    return num;
}

//============================================================================
// Parser class definition
//============================================================================

class Parser {
public:
    vector<string> _originalFile; // vector to hold un parsed data
    vector<vector<string> > courseData; // vector to hold parsed rows of the data
    Parser();
    virtual ~Parser();
    void Parse(string filePath);
    void ParseRow();
    vector<vector<string> > GetOrig() { // Get method to return vector for loading
        return courseData;
    }
};

// Default constructor
Parser::Parser() {
}

// Destructor
Parser::~Parser() {
}

/*
*  Method to open the file and load each line to a vector
* 
* @param file path
*/
void Parser::Parse(string filePath) {
    ifstream courseFile(filePath);

    // Verifies file has been opened, returns if not
    if (!courseFile.is_open()) {
        cout << "The file failed to open" << endl;
        return;
    }

    string line;

    // loops through every line of the file and if not empty, pushs it into the vector
    while (courseFile.good()) {
        getline(courseFile, line);
        stringstream stream(line);

        if (line != "") {
            _originalFile.push_back(line);
        }
    }

    // Calls the method to parse each row
    ParseRow();

    courseFile.close();
}

/*
* Method to parse out each row of the data file, placing in a vector of vector to input into the vector of struct
*/
void Parser::ParseRow() {
    vector<string>::iterator cur;
    cur = _originalFile.begin();
    string temp;
    bool invalid = false;
    int count = 1;

    // Iterates through each row of the vector
    for (; cur != _originalFile.end(); cur++) {
        vector<string> _row;
        int countStart = 0;
        int i = 0;
        invalid = false;

        // Iterates through each character in the row until "," is found, then pushes character up to that point into temp vector row
        for (; i != cur->length(); i++) {
            if (cur->at(i) == ',') {
                temp = cur->substr(countStart, i - countStart);
                if (temp != "") {
                    _row.push_back(temp);
                }
                countStart = i + 1;
            }
        }
        // pushes final content from data row into row
        temp = cur->substr(countStart, cur->length() - countStart);

        if (temp != "") {
            _row.push_back(temp);
        }

        // Validates that there are atleast 2 data components per row, if now, will skip row
        if (_row.size() < 2) {
            cout << "Missing data in row " << count << ". Row will not be loaded." << endl;
        }

        // else pushes parsed data into vector
        else {
            courseData.push_back(_row);
        }

        count += 1;
        _row.clear();
    }
}

//============================================================================
// Vector structure class definition
//============================================================================

class VectorStructure {
public:
    vector<Course> courses;
    VectorStructure();
    virtual ~VectorStructure();
    void loadCourses(string filePath);
    void printCourseInformation(vector<Course> courses, string courseNum);
    vector<Course> GetCourses() {
        return courses;
    }
};

// Default constructor
VectorStructure::VectorStructure() {
}

// Destructor
VectorStructure::~VectorStructure() {
    courses.clear();
}

/*
* Method to load the courses and all their data into the courses vector of struct
* 
* @param file path
*/
void VectorStructure::loadCourses(string filePath) {
    Parser data;
    string tempString;
    bool invalid = false;
    int loadSize = 0;
    vector<vector<string> > courseData; // temp vector to hold course data
    courses.clear();

    data.Parse(filePath); // Initiate parsing of the file

    courseData = data.GetOrig(); // assign temp vector to hold parsed data

    int vecSize = courseData.size();

    // iterate over the vector, creating a Course object to hold the data, confirm prereqs exist, and push to vector of struct
    for (unsigned i = 0; i < vecSize; ++i) {
        Course course;
        
        // assign course number and name
        course.courseNum = courseData[i][0];
        course.name = courseData[i][1];

        // if row is greater than 2, prereqs exist, iterates over each and confirms course is in the data
        if (courseData.at(i).size() > 2) {
            for (unsigned j = 0; j < courseData[i].size() - 2; ++j) {
                tempString = courseData[i][j + 2];
                invalid = false;
                
                // if prereq is not a valid course, row is invalid and won't be loaded
                if (!preReqValidation(courseData, tempString)) {
                    cout << "Invalid PreReq " << tempString << " assigned with " << course.name << ". Course will not be included." << endl;
                    invalid = true;
                }
                
                // else push prereq to course prereq vector
                else {
                    course.preReq.push_back(tempString);
                }
            }
        }
        
        // if no invalid prereqs, push course object into vector of struct
        if (!invalid) {
            courses.push_back(course);
            loadSize += 1;
        }
    }
    cout << "Loading completed! " << loadSize << " courses have successfully loaded." << endl;

    cout << endl;
}

/*
* Method to search for and print requested course based on course number
* 
* @param courses vector of struct
* @param string of the course number to search
*/
void VectorStructure::printCourseInformation(vector<Course> courses, string courseNum) {
    int i;
    int j;
    int compare;
    
    // Iterates through the vector, comparing the course number provided against course number at iterator
    for (i = 0; i < courses.size(); ++i) {
        compare = courseNum.compare(courses.at(i).courseNum);
        
        // If they match, print course information, including each prereq and return
        if (compare == 0) {
            cout << endl << endl;
            cout << "Course Information:" << endl;
            cout << "-------------------" << endl;
            cout << "Course Number: " << courses.at(i).courseNum << endl;
            cout << "Course Name: " << courses.at(i).name << endl;
            if (!courses.at(i).preReq.empty()) {
                cout << "Prerequisite Course Number/s: " << courses.at(i).preReq.at(0);
                for (j = 1; j < courses.at(i).preReq.size(); j++) {
                    cout << ", " << courses.at(i).preReq.at(j);
                }
            }
            cout << endl;
            cout << endl;
            return;
        }
    }
    
    // if course not found in loop, display message to screen 
    cout << endl << "Course not found." << endl;
    cout << endl;
}


//============================================================================
// Main class definition
//============================================================================

int main() {
    string csvPath;
    string userCourseNum = "";
    int userChoice = 0;
    
    VectorStructure vs; // create Class object
    vector<Course> courses; // create vector to hold course information

    while (userChoice != 9) {
        userChoice = displayMenu();

        switch (userChoice) {
        
        case 1:     // Case 1 will load the file to the vector by calling loadCourses method passing the file path provided
            cout << "Input file path: ";
            cin >> csvPath;
            cout << endl << "Loading file " << csvPath << endl;
            vs.loadCourses(csvPath);
            // assign local vector to be loaded courses vector
            courses = vs.GetCourses();
            vs.~VectorStructure();
            break;
        
        case 2:     // Case 2 will print the courses in alphanumaric order
            printSampleSchedule(courses);
            break;

        case 3:     // Case 3 will search for a specific course and print if found
            cout << "Enter course to search (Case sensitive): ";
            cin >> userCourseNum;
            vs.printCourseInformation(courses, userCourseNum);
            break;

        // End program
        case 9:
            break;

        // If 1, 2, 3, or 9 is not inputted
        default:
            cout << "Invalid input, please try again." << endl;
            break;
        }
    }
}

