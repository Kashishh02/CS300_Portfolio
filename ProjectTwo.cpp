#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

void loadCourses(string fileName, map<string, Course>& courses) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    courses.clear();

    string line;

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            continue;
        }

        Course course;
        course.courseNumber = toUpperCase(tokens[0]);
        course.courseTitle = tokens[1];

        for (unsigned int i = 2; i < tokens.size(); i++) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(
                    toUpperCase(tokens[i])
                );
            }
        }

        courses[course.courseNumber] = course;
    }

    file.close();

    cout << "Course data loaded successfully." << endl;
}

void printCourseList(const map<string, Course>& courses) {

    if (courses.empty()) {
        cout << "No course data loaded." << endl;
        return;
    }

    cout << endl;
    cout << "Here is a sample schedule:" << endl;
    cout << endl;

    for (const auto& coursePair : courses) {
        cout << coursePair.second.courseNumber
             << ", "
             << coursePair.second.courseTitle
             << endl;
    }
}

void printCourseInformation(const map<string, Course>& courses) {

    if (courses.empty()) {
        cout << "No course data loaded." << endl;
        return;
    }

    string courseNumber;

    cout << "What course do you want to know about? ";
    cin >> courseNumber;

    courseNumber = toUpperCase(courseNumber);

    auto it = courses.find(courseNumber);

    if (it == courses.end()) {
        cout << "Course not found." << endl;
        return;
    }

    const Course& course = it->second;

    cout << endl;
    cout << course.courseNumber
         << ", "
         << course.courseTitle
         << endl;

    cout << "Prerequisites: ";

    if (course.prerequisites.empty()) {
        cout << "None";
    }
    else {

        for (unsigned int i = 0;
             i < course.prerequisites.size();
             i++) {

            string prereqNumber =
                course.prerequisites[i];

            auto prereq =
                courses.find(prereqNumber);

            if (prereq != courses.end()) {
                cout << prereq->second.courseNumber
                     << " ("
                     << prereq->second.courseTitle
                     << ")";
            }
            else {
                cout << prereqNumber;
            }

            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
    }

    cout << endl;
}

int main() {

    map<string, Course> courses;

    int choice = 0;

    cout << "Welcome to the ABCU Advising Assistance Program."
         << endl;

    while (choice != 9) {

        cout << endl;
        cout << "Menu:" << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input." << endl;
            continue;
        }

        switch (choice) {

        case 1:
        loadCourses(
            "CS 300 ABCU Advising Program input.csv",
            courses
        );
            break;

        case 2:
            printCourseList(courses);
            break;

        case 3:
            printCourseInformation(courses);
            break;

        case 9:
            cout << "Thank you for using the course planner!"
                 << endl;
            break;

        default:
            cout << "Please enter a valid menu option."
                 << endl;
            break;
        }
    }

    return 0;
}