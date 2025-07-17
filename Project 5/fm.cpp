#include "fm.h"
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

FlightManager::FlightManager() {}
FlightManager::~FlightManager() {}

bool FlightManager::load_flight_data(std::string filename) {
    std::ifstream file(filename);
    if (!file) return false;
    
    std::string input;
    while (std::getline(file, input)) {
        std::istringstream ss(input);
        std::string airline, flightNumStr, source, destination, departureTimeStr, arrivalTimeStr, durationStr;
        
        // Skip badly formatted lines
        if (!getline(ss, airline, ',') ||
            !getline(ss, flightNumStr, ',') ||
            !getline(ss, source, ',') ||
            !getline(ss, destination, ',') ||
            !getline(ss, departureTimeStr, ',') ||
            !getline(ss, arrivalTimeStr, ',') ||
            !getline(ss, durationStr, ',')) continue;
        
        int flightNum = std::stoi(flightNumStr);
        int departureTime = std::stoi(departureTimeStr);
        int duration = std::stoi(durationStr);
        
        m_flightsBySource[source].insert({airline, flightNum, source, destination, departureTime, duration});
    }
    return true;
}


std::vector<FlightSegment> FlightManager::find_flights(std::string source_airport, int start_time, int end_time) const {
    // No data on this aiport
    if (m_flightsBySource.find(source_airport) == m_flightsBySource.end()) {
        return {};
    }
    
    const FlightSegment start("", std::numeric_limits<int>::min(), "", "", start_time, std::numeric_limits<int>::min());
    BSTSet<FlightSegment>::SetIterator it = m_flightsBySource.at(source_airport).find_first_not_smaller(start);
    
    std::vector<FlightSegment> res;
    const FlightSegment* curr;
    while ((curr = it.get_and_advance()) != nullptr && curr->departure_time < end_time) {
        res.push_back(*curr);
    }
    return res;
}
