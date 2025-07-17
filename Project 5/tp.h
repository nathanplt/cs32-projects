#ifndef TP_H_
#define TP_H_

#include "provided.h"
#include <string>
#include <unordered_set>

class TravelPlanner : public TravelPlannerBase {
public:
    TravelPlanner(const FlightManagerBase& flight_manager, const AirportDB& airport_db);
    ~TravelPlanner();
    
    void add_preferred_airline(std::string airline);
    bool plan_travel(std::string source_airport, std::string destination_airport, int start_time, Itinerary& itinerary) const;
    
private:
    std::unordered_set<std::string> m_prefAirlines;
    int heuristic(const std::string& source_airport, const std::string& destination_airport) const;
};

#endif // TP_H_
