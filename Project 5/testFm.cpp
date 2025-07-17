#include "fm.h"
#include <iostream>
#include <vector>
using namespace std;

const string FILE_PATH = "/Users/nathan/CS32 Projects/Project 5/Project 5/";

void printFlight(const FlightSegment &fs) {
    cout << fs.airline << ", " << fs.flight_no << ", "
         << fs.source_airport << ", " << fs.destination_airport << ", "
         << fs.departure_time << ", " << fs.duration_sec << endl;
}

void runTest(FlightManager &fm, const string &source, int start_time, int end_time, const string &testName) {
    cout << "\n" << testName << " – Querying " << source << " from " << start_time << " to " << end_time << ":\n";
    vector<FlightSegment> flights = fm.find_flights(source, start_time, end_time);
    if (flights.empty()) {
        cout << "No flights found." << endl;
    } else {
        for (const auto &fs : flights) {
            printFlight(fs);
        }
    }
}

int main() {
    FlightManager fm;
    if (!fm.load_flight_data(FILE_PATH + "all_flights.txt")) {
        cerr << "Failed to load flight data." << endl;
        return 1;
    }
    cout << "Flight data loaded successfully." << endl;

    // Test Case 1: HRL
    runTest(fm, "HRL", 1736230000, 1736231000, "Test Case 1 (HRL)");

    // Test Case 2: CVG
    runTest(fm, "CVG", 1736250000, 1736270000, "Test Case 2 (CVG)");

    // Test Case 3: MIA
    runTest(fm, "MIA", 1736280000, 1736290000, "Test Case 3 (MIA)");

    // Test Case 4: SFO (early departure)
    runTest(fm, "SFO", 1736220000, 1736230000, "Test Case 4 (SFO early)");

    // Test Case 5: SFO (later departure)
    runTest(fm, "SFO", 1736300000, 1736310000, "Test Case 5 (SFO later)");

    // Test Case 6: LAX
    runTest(fm, "LAX", 1736300000, 1736310000, "Test Case 6 (LAX)");

    // Test Case 7: Nonexistent source "XYZ"
    runTest(fm, "XYZ", 1736200000, 1736300000, "Test Case 7 (XYZ)");

    // Test Case 8: SCK
    runTest(fm, "SCK", 1736170000, 1736200000, "Test Case 8 (SCK)");

    // Test Case 9: BWI
    runTest(fm, "BWI", 1736360000, 1736380000, "Test Case 9 (BWI)");

    // Test Case 10: (For flights stored under SCK that lead to RFD)
    // Note: If your implementation uses the SCK key for flights to RFD, then querying SCK with a wide window:
    runTest(fm, "SCK", 1736170000, 1736400000, "Test Case 10 (SCK all flights)");

    return 0;
}
