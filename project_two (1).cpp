/*
 * CS 300 Project Two: ABCU Advising Program
 * Hamad Alghaithi
 * 06/22/2025
 *
 * This program implements a course advising system using a hash table
 * data structure to store and manage course information for ABCU's
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>

using namespace std;

/**
 * Course structure to hold course information
 * Contains course number, title, and list of prerequisites
 */
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
    
    // Default constructor
    Course() {}
    
    // Parameterized constructor
    Course(string number, string courseTitle) {
        courseNumber = number;
        title = courseTitle;
    }
};

/**
 * Global hash table to store all courses
 * Key: course number (string)
 * Value: Course object
 */
unordered_map<string, Course> courseTable;

/**
 * Function to convert string to uppercase for case-insensitive comparisons
 * @param str The string to convert
 * @return Uppercase version of the string
 */
string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

/**
 * Function to trim whitespace from beginning and end of string
 * @param str The string to trim
 * @return Trimmed string
 */
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

/**
 * Function to load course data from CSV file into hash table
 * Validates file format and prerequisite integrity
 * @param fileName Name of the CSV file to load
 * @return true if data loaded successfully, false otherwise
 */
bool loadDataStructure(string fileName) {
    ifstream file(fileName);
    
    // Check if file can be opened
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        cout << "Please make sure the file exists and try again." << endl;
        return false;
    }
    
    // Clear any existing data
    courseTable.clear();
    
    string line;
    int lineCount = 0;
    vector<string> allCourseNumbers; // For prerequisite validation
    
    // First pass: collect all course numbers for validation
    while (getline(file, line)) {
        lineCount++;
        if (line.empty()) continue;
        
        stringstream ss(line);
        string courseNumber;
        
        if (getline(ss, courseNumber, ',')) {
            courseNumber = trim(courseNumber);
            if (!courseNumber.empty()) {
                allCourseNumbers.push_back(toUpperCase(courseNumber));
            }
        }
    }
    
    // Reset file for second pass
    file.clear();
    file.seekg(0, ios::beg);
    lineCount = 0;
    
    // Second pass: parse and store course data
    while (getline(file, line)) {
        lineCount++;
        if (line.empty()) continue;
        
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        // Parse CSV line
        while (getline(ss, token, ',')) {
            tokens.push_back(trim(token));
        }
        
        // Validate minimum required fields
        if (tokens.size() < 2) {
            cout << "Warning: Line " << lineCount << " has insufficient data, skipping." << endl;
            continue;
        }
        
        // Extract course information
        string courseNumber = toUpperCase(tokens[0]);
        string courseTitle = tokens[1];
        
        if (courseNumber.empty() || courseTitle.empty()) {
            cout << "Warning: Line " << lineCount << " has empty course number or title, skipping." << endl;
            continue;
        }
        
        // Create course object
        Course course(courseNumber, courseTitle);
        
        // Process prerequisites (tokens 2 and beyond)
        for (size_t i = 2; i < tokens.size(); i++) {
            string prereq = trim(tokens[i]);
            if (!prereq.empty()) {
                prereq = toUpperCase(prereq);
                
                // Validate prerequisite exists
                bool prereqExists = false;
                for (const string& validCourse : allCourseNumbers) {
                    if (validCourse == prereq) {
                        prereqExists = true;
                        break;
                    }
                }
                
                if (prereqExists) {
                    course.prerequisites.push_back(prereq);
                } else {
                    cout << "Warning: Prerequisite " << prereq << " for course " 
                         << courseNumber << " not found in course list." << endl;
                }
            }
        }
        
        // Store course in hash table
        courseTable[courseNumber] = course;
    }
    
    file.close();
    
    if (courseTable.empty()) {
        cout << "Error: No valid courses were loaded from the file." << endl;
        return false;
    }
    
    cout << "Data loaded successfully! " << courseTable.size() << " courses loaded." << endl;
    return true;
}

/**
 * Function to print all courses in alphanumeric order
 * Extracts courses from hash table, sorts them, and displays
 */
void printCourseList() {
    if (courseTable.empty()) {
        cout << "No courses loaded. Please load data first using option 1." << endl;
        return;
    }
    
    // Extract courses into vector for sorting
    vector<Course> courses;
    for (const auto& pair : courseTable) {
        courses.push_back(pair.second);
    }
    
    // Sort courses alphanumerically by course number
    sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
    });
    
    // Display sorted course list
    cout << "\nHere is a sample schedule:\n" << endl;
    for (const Course& course : courses) {
        cout << course.courseNumber << ", " << course.title << endl;
    }
    cout << endl;
}

/**
 * Function to search for and print information about a specific course
 * @param courseNumber The course number to search for
 */
void printCourseInformation(string courseNumber) {
    if (courseTable.empty()) {
        cout << "No courses loaded. Please load data first using option 1." << endl;
        return;
    }
    
    // Convert to uppercase for case-insensitive search
    courseNumber = toUpperCase(trim(courseNumber));
    
    // Search for course in hash table
    auto it = courseTable.find(courseNumber);
    if (it != courseTable.end()) {
        const Course& course = it->second;
        
        // Print course information
        cout << course.courseNumber << ", " << course.title << endl;
        
        // Print prerequisites
        if (course.prerequisites.empty()) {
            cout << "Prerequisites: None" << endl;
        } else {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); i++) {
                if (i > 0) cout << ", ";
                
                // Look up prerequisite details
                auto prereqIt = courseTable.find(course.prerequisites[i]);
                if (prereqIt != courseTable.end()) {
                    cout << prereqIt->second.courseNumber;
                } else {
                    cout << course.prerequisites[i];
                }
            }
            cout << endl;
        }
    } else {
        cout << "Course " << courseNumber << " not found." << endl;
        cout << "Please verify the course number and try again." << endl;
    }
}

/**
 * Function to display the main menu options
 */
void displayMenu() {
    cout << "\nWelcome to the course planner.\n" << endl;
    cout << "  1. Load Data Structure." << endl;
    cout << "  2. Print Course List." << endl;
    cout << "  3. Print Course." << endl;
    cout << "  9. Exit" << endl;
    cout << "\nWhat would you like to do? ";
}

/**
 * Function to get and validate user input
 * @return User's menu choice as integer
 */
int getUserChoice() {
    string input;
    getline(cin, input);
    
    try {
        return stoi(input);
    } catch (const exception&) {
        return -1; // Invalid input
    }
}

/**
 * Main function - Program entry point
 * Handles menu loop and user interaction
 */
int main() {
    int choice = 0;
    string fileName;
    string courseNumber;
    
    cout << "Welcome to the course planner." << endl;
    
    // Main program loop
    while (choice != 9) {
        displayMenu();
        choice = getUserChoice();
        
        switch (choice) {
            case 1:
                // Load Data Structure
                cout << "Enter the file name: ";
                getline(cin, fileName);
                if (fileName.empty()) {
                    fileName = "ABCU_Advising_Program_Input.csv"; // Default filename
                    cout << "Using default filename: " << fileName << endl;
                }
                loadDataStructure(fileName);
                break;
                
            case 2:
                // Print Course List
                printCourseList();
                break;
                
            case 3:
                // Print Course Information
                cout << "What course do you want to know about? ";
                getline(cin, courseNumber);
                if (!courseNumber.empty()) {
                    printCourseInformation(courseNumber);
                } else {
                    cout << "Please enter a valid course number." << endl;
                }
                break;
                
            case 9:
                // Exit
                cout << "Thank you for using the course planner!" << endl;
                break;
                
            default:
                // Invalid option
                cout << choice << " is not a valid option." << endl;
                break;
        }
    }
    
    return 0;
}
