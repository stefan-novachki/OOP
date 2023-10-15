// Lab 1 - 2

#include <stdio.h>
#include <stdlib.h>

typedef struct Engine {
    int horsepower;
    int torque;
} Engine;

typedef struct Car {
    Engine engine;
    char manufacturer[30];
    int year;
} Car;

void printCars(Car *cars, int n) {
    Car tmp;
    Car tmp1 = cars[0];
    for (int i = 1; i < n; i++) {
        if (cars[i].engine.horsepower < tmp1.engine.horsepower) {
            tmp = tmp1;
            tmp1 = cars[i];
        }
    }

    if (tmp.engine.torque > tmp1.engine.torque) {
        tmp1 = tmp;
    }

    printf("Manufacturer: %s\nHorsepower: %d\nTorque: %d", tmp1.manufacturer, tmp1.engine.horsepower,
           tmp1.engine.torque);
}


int main() {
    int n;
    scanf("%d", &n);

    Car cars[n];

    for (int i = 0; i < n; i++) {
        scanf("%s", cars[i].manufacturer);
        scanf("%d %d %d", &cars[i].year, &cars[i].engine.horsepower, &cars[i].engine.torque);
    }

    printCars(cars, n);
    return 0;
}
