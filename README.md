# cs300

## Project Overview
This repository contains my work from CS 300, focusing on data structures and algorithms analysis for ABCU's course advising program. The project demonstrates my understanding of different data structures, runtime analysis, and practical software implementation.
## Problem Statement
The challenge was to design and implement a course advising program for ABCU (American British Continental University) that could efficiently:

- Load course data from a CSV file
- Display all courses in alphanumeric order
- Search for specific course information including prerequisites
- Handle data validation and error checking

The program needed to be efficient, scalable, and user-friendly for academic advisors helping students plan their coursework.

## My Approach to the Problem
### Understanding Data Structures Importance
Data structures are fundamental to efficient software design because they directly impact:

- Performance: How quickly operations execute
- Memory Usage: How efficiently data is stored
- Scalability: How well the program handles growing datasets
- Maintainability: How easy the code is to modify and extend

I analyzed three different data structures for this project:

1. Vector: Simple linear structure with O(n) search time
2. Hash Table: Key-value mapping with O(1) average search time
3. Binary Search Tree: Hierarchical structure with O(log n) search time

### Runtime Analysis Summary

| Data      |          |          |  Sorted     |
| Structure | Loading  | Search   |             |
|           |          |          |             |
| Vector    | O(n)     | O(n)     | O(n^2)      |
|           |          |          |             |
|Hash Table | O(n)     | O(1)     | O(n^2)      |
|           |          |          |             |
| Binar     |O(n log n)| O(log    | O(n)        |
|Search tree|          |  n)      |             |
|           |          |          |             |

### Design Decision
I chose the Hash Table implementation because:

- The primary use case (individual course lookups) benefits from O(1) average-case performance
- Academic advisors will search for specific courses frequently during student meetings
- The trade-off of O(n²) for sorted display is acceptable since this operation is less frequent
- It provides the best scalability as the course catalog grows

## Overcoming Roadblocks
### Challenge 1: Data Validation
Problem: Ensuring prerequisite courses exist before adding them to a course's prerequisite list.
Solution: Implemented a two-pass file reading approach:

1. First pass: Collect all valid course numbers
2. Second pass: Validate prerequisites against the collected course numbers

### Challenge 2: Case-Insensitive Search
Problem: Users might enter course numbers in different cases (e.g., "cs300" vs "CS300").
Solution: Created helper functions to normalize input:
cppstring toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}
### Challenge 3: Robust Error Handling
Problem: Handling malformed CSV data and file access issues gracefully.
Solution: Added comprehensive validation:

File existence checks
Line format validation
Empty field handling
User-friendly error messages

## Impact on My Software Design Approach
This project fundamentally changed how I approach software design:
### Performance-First Thinking
I now consider the runtime complexity of operations from the beginning of design, not as an afterthought. Understanding Big O notation helps me make informed decisions about data structure selection.
### User-Centered Design
Working on the advising program taught me to prioritize the most common use cases. The hash table choice prioritized fast course lookups over fast sorted display because that's what users need most.
### Defensive Programming
I learned to anticipate and handle edge cases:

- Invalid file formats
- Missing prerequisites
- Empty input fields
- File access errors

## Evolution of My Programming Practices
### Maintainable Code Structure

- Modular Functions: Each function has a single, well-defined purpose
- Clear Naming: Function and variable names clearly indicate their purpose
- Comprehensive Comments: Code is documented for future developers

## Readable Implementation

cpp
// Example of clear, readable function design
bool loadDataStructure(string fileName) {
    // Clear validation with early returns
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return false;
    }
    
    // Self-documenting variable names
    vector<string> allCourseNumbers;
    
    // Two-pass approach with clear comments
    // First pass: collect all course numbers for validation
    // Second pass: parse and store course data
}
### Adaptable Design
The hash table implementation can easily be extended:

- Adding new course fields (credits, instructor, etc.)
- Implementing additional search criteria
- Supporting different file formats
- Adding course modification capabilities

##Key Takeaways

1. Data Structure Choice Matters: The right data structure can dramatically improve performance for specific use cases.
2. Real-World Constraints: Academic considerations like user workflow and common operations should drive technical decisions.
3. Robust Error Handling: Production software must gracefully handle unexpected inputs and edge cases.
4. Code Quality: Writing maintainable, readable code is as important as algorithmic efficiency.
5. Analysis Before Implementation: Understanding the problem thoroughly through runtime analysis leads to better design decisions.

## Repository Contents

- Runtime Analysis: Comprehensive analysis of Vector, Hash Table, and Binary Search Tree implementations
- Working Code: Complete C++ implementation of the course advising program using hash table data structure
- Documentation: This README with detailed reflection on the development process

This project demonstrates my ability to analyze complex problems, evaluate multiple solutions, and implement efficient, maintainable software solutions.
