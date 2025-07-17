class Landmark {
public:
    Landmark(string name) : m_name(name) {}
    virtual ~Landmark() {}
    
    string name() const {
        return m_name;
    }
    
    virtual string color() const {
        return "yellow";
    }
    virtual string icon() const = 0;
private:
    string m_name;
};

class Hotel: public Landmark {
public:
    Hotel(string name) : Landmark(name) {}
    virtual ~Hotel() {
        cout << "Destroying the hotel " << name() << "." << endl;
    }
    
    virtual string icon() const {
        return "bed";
    }
};

class Restaurant: public Landmark {
public:
    Restaurant(string name, int capacity) : Landmark(name), m_capacity(capacity) {}
    virtual ~Restaurant() {
        cout << "Destroying the restaurant " << name() << "." << endl;
    }
    
    virtual string icon() const {
        if (m_capacity < 40) {
            return "small knife/fork";
        }
        return "large knife/fork";
    }
private:
    int m_capacity;
};

class Hospital: public Landmark {
public:
    Hospital(string name) : Landmark(name) {}
    
    virtual ~Hospital() {
        cout << "Destroying the hospital " << name() << "." << endl;
    }
    
    virtual string color() const {
        return "blue";
    }
    
    virtual string icon() const {
        return "H";
    }
};
