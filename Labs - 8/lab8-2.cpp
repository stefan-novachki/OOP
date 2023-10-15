// Lab 8 - 2

#include <iostream>
#include <cstring>

using namespace std;

class FoodItem {
protected:
    char *type;
    int num;

    void copy(const FoodItem &fi) {
        this->type = new char[strlen(fi.type)];
        strcpy(this->type, fi.type);
        this->num = fi.num;
    }

public:
    FoodItem(char *type = 0, int num = 0) {
        this->type = new char[strlen(type) + 1];
        strcpy(this->type, type);
        this->num = num;
    }

    FoodItem(const FoodItem &fi) {
        copy(fi);
    }

    FoodItem &operator=(const FoodItem &fi) {
        if (this != &fi) {
            delete[] type;
            copy(fi);
        }
        return *this;
    }

    char *getType() const {
        return type;
    }

    virtual double getPrice() = 0;

    virtual double getTime() = 0;

    virtual ~FoodItem() {
        delete[] type;
    }
};

class Pizza : public FoodItem {
private:
    char *dough;

    void copy(const Pizza &p) {
        this->dough = new char[strlen(p.dough) + 1];
        strcpy(this->dough, p.dough);
    }

public:
    Pizza(char *type = 0, int num = 0, char *dough = 0) : FoodItem(type, num) {
        this->dough = new char[strlen(dough) + 1];
        strcpy(this->dough, dough);
    }

    Pizza(const Pizza &p) : FoodItem(p) {
        copy(p);
    }

    Pizza &operator=(const Pizza &p) {
        if (this != &p) {
            delete[] dough;
            FoodItem::copy(p);
            copy(p);
        }
        return *this;
    }

    double getPrice() {
        if (strcmp(this->dough, "wholeWheat") == 0) {
            return num * 250;
        } else if (strcmp(this->dough, "glutenFree") == 0) {
            return num * 350;
        }
    }

    double getTime() {
        return 25;
    }

    virtual ~Pizza() {
        delete[] dough;
    }
};

class Steak : public FoodItem {
private:
    bool cooked;
public:
    Steak(char *type = 0, int num = 0, bool cooked = false)
            : FoodItem(type, num) {
        this->cooked = cooked;
    }

    double getPrice() {
        return num * 1300;
    }

    double getTime() {
        if (cooked == true) {
            return 20;
        } else {
            return 15;
        }
    }

    virtual ~Steak() {}
};

FoodItem *getMaxFoodItem(FoodItem **pItem, int n) {
    FoodItem *maxFoodItem = pItem[0];
    for (int i = 0; i < n; ++i) {
        if (pItem[i]->getPrice() > maxFoodItem->getPrice()) {
            maxFoodItem = pItem[i];
        }
    }

    return maxFoodItem;
}

int main() {
    FoodItem *p;
    int n;
    cin >> n;

    char type[30];
    char dough[30];
    bool cooked;
    int size;

    FoodItem *items[n];

    for (int i = 0; i < n; ++i) {
        cin >> type;
        cin >> size;


        if (strcmp(type, "pizza") == 0) {
            cin >> dough;
            items[i] = new Pizza(type, size, dough);
        } else {
            cin >> cooked;
            items[i] = new Steak(type, size, cooked);
        }

    }

    FoodItem *it = getMaxFoodItem(items, n);
    cout << "Type: " << it->getType() << endl;
    cout << "The max price is: " << it->getPrice() << endl;
    cout << "Time to cook: " << it->getTime();
    return 0;
}