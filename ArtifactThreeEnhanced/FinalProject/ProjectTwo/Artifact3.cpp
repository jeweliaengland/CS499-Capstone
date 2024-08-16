//============================================================================
// Name        : Artifact3.cpp
// Author      : Jewelia England
// Version     : 1.0
// Copyright   : Copyright © 2024 SNHU COCE
// Description : Artifact3
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "sqlite3.h"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold course information
struct Course {
    string courseId; // unique identifier
    string title;
    string prerequisites;
    double amount;
    Course() {
        amount = 0.0;
    }
};
vector<Course> courses;
//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    std::cout << course.title << ": " << course.courseId << " | " << course.amount << " | "
        << course.prerequisites << endl;
    return;
}
/**
* Search for the specified bidId
*
* @param bidId The bid id to search for
*/
Course SearchCourse(string courseId) {
    Course course;
    unsigned int idx = 0;

    //Iterate the loop
    for (int i = 0; i < courses.size(); ++i) {
        if (courses[i].courseId._Equal(courseId))
        {
            return courses[i];
        }
    }
    return course;
}

vector<Course> loadCoursesFromDatabase() {
    vector<Course> courses;
    sqlite3_stmt* sqlStatement;
    sqlite3* Database;

    int rc = sqlite3_open("D:\\repos\\CS499\\ArtifactThree\\FinalProject\\ProjectTwo\\courses.db", &Database);
    if (rc) 
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(Database) << endl;
        return courses;
    }
    else 
    {
        cout << "Database opened successfully" << endl;
    }

    string sql = "SELECT ID, TITLE, PREREQ FROM Courses;";
    rc = sqlite3_prepare_v2(Database, sql.c_str(), -1, &sqlStatement, nullptr);

    if (rc != SQLITE_OK) 
    {
        cerr << "Query failed: " << sqlite3_errmsg(Database) << endl;
        sqlite3_close(Database);
        return courses;
    }

    while (sqlite3_step(sqlStatement) == SQLITE_ROW)
    {
        Course course;
        course.courseId = (char* )(sqlite3_column_text(sqlStatement, 0));
        course.title = (char*)(sqlite3_column_text(sqlStatement, 1));
        course.prerequisites = (char*)(sqlite3_column_text(sqlStatement, 2));
        courses.push_back(course);
    }

    sqlite3_finalize(sqlStatement);
    sqlite3_close(Database);
    return courses;
}

/**
 * Partition the vector of courses into two parts, low and high
 *
 * @param courses Address of the vector<course> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Course>& courses, int begin, int end) {
    //set low and high equal to begin and end

    // pick the middle element as pivot point

    // while not done 

        // keep incrementing low index while courses[low] < courses[pivot]

        // keep decrementing high index while courses[pivot] < courses[high]

        /* If there are zero or one elements remaining,
            all courses are partitioned. Return high */
            // else swap the low and high courses (built in vector method)
                 // move low and high closer ++low, --high
         //return high;


         //local variable declaration
    int midPoint;
    string pivot;
    Course tempSwap;
    bool done;

    midPoint = begin + (end - begin) / 2;
    pivot = courses[midPoint].title;
    done = false;

    while (!done) {

        while (courses[begin].title < pivot) {

            begin++;
        }

        while (pivot < courses[end].title) {

            end--;
        }

        if (begin >= end) {

            done = true;
        }

        else {

            //set-up the swaps using a tempSwap variable of type course
            tempSwap = courses[begin];
            courses[begin] = courses[end];
            courses[end] = tempSwap;

            begin++;
            end--;
        }
    }


    return end;
}

/**
 * Perform a quick sort on course title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param courses address of the vector<course> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Course>& courses, int begin, int end) {
    //set mid equal to 0

    /* Base case: If there are 1 or zero courses to sort,
     partition is already sorted otherwise if begin is greater
     than or equal to end then return*/

     /* Partition courses into low and high such that
      midpoint is location of last element in low */

      // recursively sort low partition (begin to mid)

      // recursively sort high partition (mid+1 to end)

    int lowIndex;

    if (begin >= end) {

        return;
    }

    //call the partition function to define the lowIndex
    lowIndex = partition(courses, begin, end);

    //recursive calls to quickSort
    quickSort(courses, begin, lowIndex);
    quickSort(courses, lowIndex + 1, end);

}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

void merge(vector<Course>& courses, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors
    vector<Course> leftVector(n1);
    vector<Course> rightVector(n2);

    // Copy data to temporary vectors
    for (int i = 0; i < n1; i++)
        leftVector[i] = courses[left + i];
    for (int i = 0; i < n2; i++)
        rightVector[i] = courses[mid + 1 + i];

    // Merge the temporary vectors back into courses
    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (leftVector[i].title <= rightVector[j].title) {
            courses[k] = leftVector[i];
            i++;
        }
        else {
            courses[k] = rightVector[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftVector, if any
    while (i < n1) {
        courses[k] = leftVector[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightVector, if any
    while (j < n2) {
        courses[k] = rightVector[j];
        j++;
        k++;
    }
}
void mergeSort(vector<Course>& courses, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(courses, left, mid);
    mergeSort(courses, mid + 1, right);
    merge(courses, left, mid, right);
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string dbPath;
    switch (argc) {
    case 2:
        dbPath = argv[1];
        break;
    default:
        dbPath = "D:\repos\CS499\ArtifactThree\FinalProject\Project2\courses.db";
    }

    // Define a vector to hold all the courses
    //JOE vector<Course> courses;

    // Define a timer variable
    clock_t ticks;

    //add a few local variables for try/catch and usability needs

    const int GLOBAL_SLEEP_VALUE = 5000;
    int choice = 0;
    string anyKey = " ";
    bool goodInput;
    Course course;
    string courseSearch;

    while (choice != 9) {

        std::cout << "Menu:" << endl;
        std::cout << "  1. Load courses" << endl;
        std::cout << "  2. Display All courses" << endl;
        std::cout << "  3. Merge Sort All courses" << endl;
        std::cout << "  4. Quick Sort All courses" << endl;
        std::cout << "  5. Find Course" << endl;
        std::cout << "  9. Exit" << endl;
        std::cout << "Enter choice: ";

        try { //add a try catch to protect against bad input

            std::cin >> choice;

            if ((choice > 0 && choice < 6) || (choice == 9)) {// limit the user menu inputs to good values
                goodInput = true;
            }
            else {//throw error for catch
                goodInput = false;
                throw 1;
            }

            switch (choice) { //create a swtich to allow the menu to work

            case 1:
                // Initialize a timer variable before loading courses
                ticks = clock();

                // Complete the method call to load the courses;
                courses = loadCoursesFromDatabase();

                std::cout << courses.size() << " courses read" << endl;

                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                std::cout << "time: " << ticks << " clock ticks" << endl;
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                Sleep(GLOBAL_SLEEP_VALUE);

                break;

            case 2:
                // Loop and display the courses read
                for (int i = 0; i < courses.size(); ++i) {
                    displayCourse(courses[i]);
                }
                std::cout << "Press any key to continue...";

                std::cin >> anyKey;
                Sleep(GLOBAL_SLEEP_VALUE);

                break;

            case 3:

                //merge sort switch 
                //start the clock with the tick variable and then call the function
                //stop the clock with tick again and then outpout the time it tookto run
                //sleep for some amount of time and then redraw the menu

                ticks = clock();

                mergeSort(courses, 0, courses.size() - 1);
                
                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                std::cout << "time: " << ticks << " clock ticks" << endl;
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                Sleep(GLOBAL_SLEEP_VALUE);

                break;

            case 4:

                //quick sort switch 
                //start the clock with the tick variable and then call the function
                //stop the clock with tick again and then outpout the time it took to run
                //sleep for some amount of time and then redraw the menu

                ticks = clock();

                quickSort(courses, 0, courses.size() - 1);

                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                std::cout << "time: " << ticks << " clock ticks" << endl;
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                Sleep(GLOBAL_SLEEP_VALUE);

                break;

            case 5:
                 
                std::cout << "Enter cource to search for:" << endl;
                std::cin >> courseSearch;
                ticks = clock();
                course = SearchCourse(courseSearch);
                if (!course.courseId._Equal(""))
                {
                    std::cout << course.courseId << ": " << course.title << " | " << course.amount << " | "
                        << course.prerequisites << endl;
                }
                else
                {
                    std::cout << "Could not find course " << course.title << endl;
                }

                std::cout << "Press any key to continue...";

                std::cin >> anyKey;

                break;

            case 9:
                //default case for the exit statement so we don't fail the try catch

                break;

            default:
                throw 2;
            }
        }
        catch (int err) {
            std::cout << "\nPlease check your input." << endl;
            Sleep(GLOBAL_SLEEP_VALUE);
        }

        //need to clear the cin operator of extra input, e.g., 9 9, or any errors generated by bad input, e.g., 'a'
        cin.clear();
        cin.ignore();

        //clear the consolse to redraw a fresh menu
        system("cls");
    }

    std::cout << "Good bye." << endl;

    Sleep(GLOBAL_SLEEP_VALUE);

    return 0;
}