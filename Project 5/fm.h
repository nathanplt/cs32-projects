#ifndef FM_H_
#define FM_H_

#include "provided.h"
#include "bstset.h"
#include <unordered_map>

inline bool operator<(const FlightSegment& a, const FlightSegment& b) {
    if (a.departure_time != b.departure_time) {
        return a.departure_time < b.departure_time;
    }
    if (a.duration_sec != b.duration_sec) {
        return a.duration_sec < b.duration_sec;
    }
    if (a.flight_no != b.flight_no) {
        return a.flight_no < b.flight_no;
    }
    if (a.source_airport != b.source_airport) {
        return a.source_airport < b.source_airport;
    }
    if (a.destination_airport != b.destination_airport) {
        return a.destination_airport < b.destination_airport;
    }
    return a.airline < b.airline;
}

class FlightManager : public FlightManagerBase {
public:
    FlightManager();
    ~FlightManager();
    
    bool load_flight_data(std::string filename);
    std::vector<FlightSegment> find_flights(std::string source_airport, int start_time, int end_time) const;
    
private:
    std::unordered_map<std::string, BSTSet<FlightSegment>> m_flightsBySource;
};


#endif // FM_H_
