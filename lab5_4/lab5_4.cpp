#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Address {
private:
    string street;
    string city;

public:
    Address(string street, string city) : street(street), city(city) {}

    string toString() const {
        return "city: " + city + ", street: " + street;
    }

    string getStreet() const {
        return street;
    }

    string getCity() const {
        return city;
    }
};

class Person{
protected:
    string name;
    Address* address;

public:
    Person(string name, Address* address) : name(name), address(address) {}

    // Add a protected getter for the address
    Address* getAddress() const {
        return address;
    }
};
class Driver : public Person {
private:
    string driverLicense;

public:
    Driver(string name, Address* address, string driverLicense)
        : Person(name, address), driverLicense(driverLicense) {}

    Address getAddress() const {
        return *address;
    }
};

class Mosquito {
private:
    int mosquito_id;

public:
    Mosquito(int mosquito_id) : mosquito_id(mosquito_id) {}

    int getId() const {
        return mosquito_id;
    }

    // Define equality operator for Mosquito
    bool operator==(const Mosquito& other) const {
        return mosquito_id == other.mosquito_id;
    }
};

class Vehicle {
protected:
    string licenseNumber;
    Address* address;
    Driver* driver;
    vector<Person*> passengers;
    vector<Mosquito> mosquitoes;

public:
    Vehicle(string licenseNumber, Address* address, Driver* driver)
        : licenseNumber(licenseNumber), address(address), driver(driver) {}

    void addPassenger(Person* passenger) {
        passengers.push_back(passenger);
    }

    void addMosquito(const Mosquito& mosquito) {
        mosquitoes.push_back(mosquito);
    }

    bool hasMosquito(const Mosquito& mosquito) const {
        return find(mosquitoes.begin(), mosquitoes.end(), mosquito) != mosquitoes.end();
    }

    const vector<Person*>& getPassengers() const {
        return passengers;
    }

    Driver* getDriver() const {
        return driver;
    }
};

class Bus : public Vehicle {
private:
    vector<Address*> stops;

public:
    Bus(string licenseNumber, Address* address, Driver* driver)
        : Vehicle(licenseNumber, address, driver) {}

    void startEngine() {
        cout << "Bus engine started." << endl;
    }

    string getLicenseNumber() const {
        return licenseNumber;
    }

    int getNumCommuters() const {
        return static_cast<int>(passengers.size());
    }

    void addStop(Address* stop) {
        stops.push_back(stop);
    }

    const vector<Address*>& getStops() const {
        return stops;
    }
};

class Car : public Vehicle {
public:
    Car(string licenseNumber, Address* address, Driver* driver)
        : Vehicle(licenseNumber, address, driver) {}
};

class Apartment {
private:
    Address* address;
    vector<Mosquito> mosquitoes;

public:
    Apartment(Address* address) : address(address) {}

    void moveIn(const vector<Mosquito>& newMosquitoes) {
        mosquitoes.insert(mosquitoes.end(), newMosquitoes.begin(), newMosquitoes.end());
    }

    bool hasMosquito(const Mosquito& mosquito) const {
        return find(mosquitoes.begin(), mosquitoes.end(), mosquito) != mosquitoes.end();
    }

    void removeMosquito(const Mosquito& mosquito) {
        auto it = find(mosquitoes.begin(), mosquitoes.end(), mosquito);
        if (it != mosquitoes.end()) {
            mosquitoes.erase(it);
        }
    }

    vector<Mosquito> getMosquitoes() const {
        return mosquitoes;
    }
};

class BusStation {
private:
    int station_id;
    vector<Bus*> buses;
    vector<Person*> commuters;

public:
    BusStation(int station_id) : station_id(station_id) {}

    void addBus(Bus* bus) {
        buses.push_back(bus);
    }

    void addCommuter(Person* commuter) {
        commuters.push_back(commuter);
    }

    const vector<Bus*>& getBuses() const {
        return buses;
    }

    int getNumCommuters() const {
        return static_cast<int>(commuters.size());
    }

    int getStationId() const {
        return station_id;
    }
};

class Student : public Person {
public:
    Student(string name, Address* address) : Person(name, address) {}
    void setAddress(Address* newAddress) {
        address = newAddress;
    }
};
class Application {
public:
    void startBusEngine(Bus* bus) {
        bus->startEngine();
    }

    int numCommutersInBus(Bus* bus) {
        if (bus == nullptr) {
            cout << "Invalid input." << endl;
            return 0;
        }

        return bus->getNumCommuters();
    }
    void moveApartmentFromPersonToStudent(Person* person, Student* student, Apartment* apartment) {
        if (person == nullptr || student == nullptr || apartment == nullptr) {
            cout << "Invalid input." << endl;
            return;
        }

        
        Mosquito mosquito(1);  
        apartment->removeMosquito(mosquito);

       
        student->setAddress(person->getAddress());

        apartment->moveIn({ mosquito });  
    }

    int numCommutersInBusStation(BusStation* busStation) {
        return busStation->getNumCommuters();
    }

    vector<Bus*> busesStoppingAtStation(BusStation* busStation) {
        return busStation->getBuses();
    }

    bool isStudentInBusDrivenByDriver(Student* student, Bus* bus, Driver* driver) {
        if (bus == nullptr || driver == nullptr) {
            return false;  // Invalid input
        }

        
        return find(bus->getPassengers().begin(), bus->getPassengers().end(),
            student) != bus->getPassengers().end() &&
            bus->getDriver() == driver;
    }

    void addStudentToLocations(Student* student, BusStation* busStation, Bus* bus, Car* car, Apartment* apartment) {
        Mosquito mosquito(1);
        busStation->addCommuter(student);
        bus->addPassenger(student);
        car->addPassenger(student);
        apartment->moveIn({ mosquito });
        bus->addMosquito(mosquito);
        car->addMosquito(mosquito);
    }

    void moveMosquitoFromApartment(Apartment* apartment, Mosquito& mosquito, Vehicle* destination) {
        if (apartment == nullptr || destination == nullptr) {
            cout << "Invalid input." << endl;
            return;
        }

        if (apartment->hasMosquito(mosquito)) {
            apartment->removeMosquito(mosquito);
            destination->addMosquito(mosquito);
            cout << "Mosquito moved from apartment to " << typeid(*destination).name() << "." << endl;
        }
        else {
            cout << "Mosquito not found in the apartment." << endl;
        }
    }

    

    vector<Address*> getBusStops(Bus* bus) {
        return bus->getStops();
    }
        
    
};

int main() {
    Address driverAddress("D.Stoica", "Craiova");
    Driver driver("Alex", &driverAddress, "str.Brutariei");

    Bus bus("BUS123", &driverAddress, &driver);
    bus.addStop(new Address("Stop1", "Bals"));
    bus.addStop(new Address("Stop2", "Slatina"));

    BusStation busStation(101);
    Car car("CAR456", &driverAddress, &driver);
    Apartment apartment(&driverAddress);
    Student student("Alice", &driverAddress);

    Application app;

    app.startBusEngine(&bus);

    Bus bus2("BUS456", &driverAddress, &driver);
    busStation.addBus(&bus);
    busStation.addBus(&bus2);

    vector<Bus*> busesAtStation = app.busesStoppingAtStation(&busStation);
    cout << "Buses at Bus Station " << busStation.getStationId() << ":" << endl;
    for (const auto& b : busesAtStation) {
        cout << b->getLicenseNumber() << endl;
    }

    app.addStudentToLocations(&student, &busStation, &bus, &car, &apartment);

    // Check if Alice is in the bus driven by Alex
    bool isInBus = app.isStudentInBusDrivenByDriver(&student, &bus, &driver);

    if (isInBus) {
        cout << "Alice is in the bus driven by Alex." << endl;
    }
    else {
        cout << "Alice is not in the bus driven by Alex." << endl;
    }

    int commutersInBus = app.numCommutersInBus(&bus);
    int commutersInBusStation = app.numCommutersInBusStation(&busStation);

    cout << "Number of commuters in Bus: " << commutersInBus << endl;
    cout << "Number of commuters in BusStation: " << commutersInBusStation << endl;

    // Check if mosquito is in the bus, car, or apartment
    Mosquito mosquito(1);
    cout << "Mosquito in Bus: " << bus.hasMosquito(mosquito) << endl;
    cout << "Mosquito in Car: " << car.hasMosquito(mosquito) << endl;
    cout << "Mosquito in Apartment: " << apartment.hasMosquito(mosquito) << endl;

    // Move mosquito from apartment to bus
    app.moveMosquitoFromApartment(&apartment, mosquito, &bus);

    // Check if mosquito is in the bus, car, or apartment after moving
    cout << "Mosquito in Bus: " << bus.hasMosquito(mosquito) << endl;
    cout << "Mosquito in Car: " << car.hasMosquito(mosquito) << endl;
    cout << "Mosquito in Apartment: " << apartment.hasMosquito(mosquito) << endl;

    // Move apartment from person to student
    app.moveApartmentFromPersonToStudent(&student, &student, &apartment);

    return 0;
}
