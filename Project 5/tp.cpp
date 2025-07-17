#include "tp.h"
#include "support.h"
#include <string>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iostream>

TravelPlanner::TravelPlanner(const FlightManagerBase& flight_manager, const AirportDB& airport_db)
 : TravelPlannerBase(flight_manager, airport_db) {}

TravelPlanner::~TravelPlanner() {}

void TravelPlanner::add_preferred_airline(std::string airline) {
    m_prefAirlines.insert(airline);
}

struct State {
    int m_time;
    std::string m_airport;
    int m_g;
    int m_f;
    std::vector<FlightSegment> m_path;
    std::unordered_set<std::string> m_visited;
    
    State(int time, std::string airport, int g, int f, std::vector<FlightSegment> path, std::unordered_set<std::string> visited)
     : m_time(time), m_airport(airport), m_g(g), m_f(f), m_path(path), m_visited(visited) {}
};

struct CompareState {
    bool operator()(const State& a, const State& b) const {
        return a.m_f > b.m_f;
    }
};

int TravelPlanner::heuristic(const std::string& source_airport, const std::string& destination_airport) const {
    double distance = 0;
    if (!get_airport_db().get_distance(source_airport, destination_airport, distance)) {
        return 0;
    }
    return std::ceil(distance * SEC_PER_MILE);
}

bool TravelPlanner::plan_travel(std::string source_airport, std::string destination_airport, int start_time, Itinerary& itinerary) const {
    std::priority_queue<State, std::vector<State>, CompareState> pq;
    pq.push({start_time, source_airport, 0, heuristic(source_airport, destination_airport), {}, {source_airport}});
    
    std::unordered_map<std::string, int> airportWindow;
    while (!pq.empty()) {
        auto [currTime, currAirport, g, f, currPath, currVisited] = pq.top();
        pq.pop();
        
        if (currAirport == destination_airport) {
            itinerary.source_airport = source_airport;
            itinerary.destination_airport = destination_airport;
            itinerary.flights = currPath;
            itinerary.total_duration = currTime - start_time;
            return true;
        }
        
        int minDeparture = currTime + get_min_connection_time();
        if (currAirport == source_airport) {
            minDeparture = currTime;
        }
        int maxDeparture = currTime + get_max_layover();
        
        std::vector<FlightSegment> flights = get_flight_manager().find_flights(currAirport, minDeparture, maxDeparture);
        for (FlightSegment& flight : flights) {
            // Only use preferred airlines, if there are any
            if (!m_prefAirlines.empty() && m_prefAirlines.find(flight.airline) == m_prefAirlines.end()) {
                continue;
            }
            
            // Check that after we take this flight, the total duration of the trip will fit constraints
            int arrivalTime = flight.departure_time + flight.duration_sec;
            if (arrivalTime - start_time > get_max_duration()) {
                continue;
            }
            
            std::string nextAirport = flight.destination_airport;
            if (currVisited.find(nextAirport) != currVisited.end()) {
                continue;
            }
            
            if (airportWindow.find(nextAirport) == airportWindow.end() || arrivalTime + get_max_layover() > airportWindow[nextAirport]) {
                airportWindow[nextAirport] = arrivalTime + get_max_layover();
                
                int ng = arrivalTime - start_time;
                int nf = ng + heuristic(nextAirport, destination_airport);
                
                std::vector<FlightSegment> nextPath = currPath;
                nextPath.push_back(flight);
            
                std::unordered_set<std::string> nextVisited = currVisited;
                nextVisited.insert(nextAirport);

                pq.push({arrivalTime, nextAirport, ng, nf, nextPath, nextVisited});
            }
        }
    }
    return false;
}
