// Lab 9 - 2

#include <iostream>
#include <cstring>

using namespace std;

class Vehicle {
protected:
    char model[40];
    double enginePower;
    double maximumSpeed;
    double fuelEfficiency;
public:
    Vehicle() {}

    Vehicle(char *model, double enginePower, double maximumSpeed, double fuelEfficiency) {
        strcpy(this->model, model);
        this->enginePower = enginePower;
        this->maximumSpeed = maximumSpeed;
        this->fuelEfficiency = fuelEfficiency;
    }

    virtual void displayInfo() = 0;

    virtual float power() = 0;
};

class LuxuryVehicle : virtual public Vehicle {
protected:
    int numberOfSeats;
public:
    LuxuryVehicle() {}

    LuxuryVehicle(char *model, double enginePower, double maximumSpeed, double fuelEfficiency, int numberOfSeats)
            : Vehicle(model, enginePower, maximumSpeed, fuelEfficiency) {
        this->numberOfSeats = numberOfSeats;
    }

    float power() {
        return (0.2 * enginePower * numberOfSeats) + (0.55 * maximumSpeed * numberOfSeats) +
               (0.25 * fuelEfficiency * numberOfSeats);
    }

    void displayInfo() {
        cout << "LuxuryVehicle: " << model << endl;
        cout << "Number of seats: " << numberOfSeats << endl;
        cout << "Engine power: " << enginePower << endl;
        cout << "Maximum speed: " << maximumSpeed << endl;
        cout << "Fuel efficiency: " << fuelEfficiency << endl;
        cout << "Power: " << power() << endl;
    }
};

class SportsVehicle : virtual public Vehicle {
protected:
    bool isConvertible;

public:
    SportsVehicle() {}

    SportsVehicle(char *model, double enginePower, double maximumSpeed, double fuelEfficiency, bool isConvertible) :
            Vehicle(model, enginePower, maximumSpeed, fuelEfficiency) {
        this->isConvertible = isConvertible;
    }

    float power() {
        float temp = enginePower + maximumSpeed + fuelEfficiency;
        if (isConvertible)
            temp /= 2;
        return temp;
    }

    void displayInfo() {
        cout << "SportsVehicle: " << model << endl;
        cout << "Convertible: ";
        if (isConvertible)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
        cout << "Engine power: " << enginePower << endl;
        cout << "Maximum speed: " << maximumSpeed << endl;
        cout << "Fuel efficiency: " << fuelEfficiency << endl;
        cout << "Power: " << power() << endl;
    }
};

class LuxurySportsVehicle : public LuxuryVehicle, public SportsVehicle {
public:
    LuxurySportsVehicle() {}

    LuxurySportsVehicle(char *model, double enginePower, double maximumSpeed, double fuelEfficiency, int numberOfSeats,
                        bool isConvertible) :
            LuxuryVehicle(model, enginePower, maximumSpeed, fuelEfficiency, numberOfSeats),
            SportsVehicle(model, enginePower, maximumSpeed, fuelEfficiency, isConvertible),
            Vehicle(model, enginePower, maximumSpeed, fuelEfficiency) {

    }

    float power() {
        float powerLuxury = LuxuryVehicle::power();
        float powerSports = SportsVehicle::power();
        return (powerLuxury + powerSports) / 2;
    }

    void displayInfo() {
        cout << "LuxurySportsVehicle: " << model << endl;
        cout << "Engine power: " << enginePower << endl;
        cout << "Maximum speed: " << maximumSpeed << endl;
        cout << "Fuel efficiency: " << fuelEfficiency << endl;
        cout << "Power: " << power() << endl;
    }
};

Vehicle *mostPowerfulLuxuryVehicle(Vehicle **vehicles, int n) {
    LuxuryVehicle *mostPowerful = nullptr;
    for (int i = 0; i < n; i++) {
        LuxuryVehicle *tmpVehicle = dynamic_cast<LuxuryVehicle *>(vehicles[i]);
        if (tmpVehicle) {
            if (mostPowerful == nullptr || mostPowerful->power() < tmpVehicle->power()) {
                mostPowerful = tmpVehicle;
            }
        }
    }
    return mostPowerful;
}

int main() {
    char model[50];
    double enginePower;
    double maximumSpeed;
    double fuelEfficiency;
    int numberOfSeats;
    bool isConvertible;
    int n;
    int choice;

    cin >> choice;
    if (choice == 1) {
        cin >> model;
        LuxurySportsVehicle luxurySportsVehicle(model, 740, 355, 13, 2, false);
        luxurySportsVehicle.displayInfo();
    } else {
        cin >> n;

        Vehicle **v = new Vehicle *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> model >> enginePower >> maximumSpeed >> fuelEfficiency >> numberOfSeats;
                v[i] = new LuxuryVehicle(model, enginePower, maximumSpeed, fuelEfficiency, numberOfSeats);
            } else {
                cin >> model >> enginePower >> maximumSpeed >> fuelEfficiency >> isConvertible;
                v[i] = new SportsVehicle(model, enginePower, maximumSpeed, fuelEfficiency, isConvertible);
            }
        }

        mostPowerfulLuxuryVehicle(v, n)->displayInfo();
    }

    return 0;
}

