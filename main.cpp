#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Base Class: Plant
class Plant {
protected:
    string name;
    string growthStage;
    double age;
    int health;
    int matureAge;
    int maxWater;
    int waterLevel;
    
private:
    static int totalPlants;

public:
    Plant(string name, int matureAge) {
        this->name = name;
        this->matureAge = matureAge;
        maxWater = 100;
        waterLevel = 0;
        health = 0;
        age = 0;
        growthStage = "Seedling";
        totalPlants++;
    }

    virtual ~Plant() {} // Virtual destructor for proper cleanup of derived classes.

    virtual void grow() {
        if (growthStage == "Seedling" && age >= matureAge / 2) {
            growthStage = "Growing";
            health += 20;
        } else if (growthStage == "Growing" && age <= matureAge) {
            growthStage = "Mature";
            health += 15;
        }
        if (age > matureAge) {
            health -= 5;
        } else {
            health += 10;
        }
        age += 2;
    }

    virtual void status() {
        cout << "Plant: " << name << endl;
        cout << "Growth Stage: " << growthStage << endl;
        cout << "Age: " << age << endl;
        cout << "Health: " << health << endl;
        cout << "Water Level: " << waterLevel << endl;
    }

    void water(int amount) {
        waterLevel = min(maxWater, waterLevel + amount);
    }

    static void showTotalPlants() {
        cout << "Total Plants: " << totalPlants << endl;
    }
};

int Plant::totalPlants = 0;

// Derived Class (Single Inheritance): FloweringPlant
class FloweringPlant : public Plant {
private:
    int flowerCount;

public:
    FloweringPlant(string name, int matureAge) : Plant(name, matureAge) {
        flowerCount = 0;
    }

    void grow() override {
        Plant::grow();
        if (growthStage == "Mature") {
            flowerCount += 5; // Flowering plants produce flowers when mature.
        }
    }

    void status() override {
        Plant::status();
        cout << "Flower Count: " << flowerCount << endl;
    }
};

// Derived Class (Multilevel Inheritance): FruitPlant -> AppleTree
class FruitPlant : public Plant {
protected:
    int fruitCount;

public:
    FruitPlant(string name, int matureAge) : Plant(name, matureAge) {
        fruitCount = 0;
    }

    void grow() override {
        Plant::grow();
        if (growthStage == "Mature") {
            fruitCount += 3; // Fruit plants produce fruits when mature.
        }
    }

    void status() override {
        Plant::status();
        cout << "Fruit Count: " << fruitCount << endl;
    }
};

// Further Derived Class: AppleTree
class HighYieldFruit : public FruitPlant {
public:
    HighYieldFruit(string name, int matureAge) : FruitPlant(name, matureAge) {}

    void grow() override {
        FruitPlant::grow();
        if (growthStage == "Mature") {
            fruitCount += 10;
        }
    }
};

// Garden class remains unchanged
class Garden {
private:
    vector<Plant*> plants;
    static int attendedGarden;

public:
    static int getAttendedGarden() {
        return attendedGarden;
    }
    static void setAttendedGarden(int times) {
        attendedGarden = times;
    }

    void addPlant(Plant* p) {
        plants.push_back(p);
    }

    void waterAllPlants(int amount) {
        for (auto plant : plants) {
            plant->water(amount);
        }
        attendedGarden++;
    }

    void growAllPlants() {
        for (auto plant : plants) {
            plant->grow();
        }
    }

    void showAllPlants() {
        for (auto plant : plants) {
            cout << "----------------" << endl;
            plant->status();
            cout << "----------------" << endl;
        }
        Plant::showTotalPlants();
    }

    static void showNoOfTimesAttended() {
        cout << "Number of times Garden was attended: " << getAttendedGarden() << endl;
    }
};

int Garden::attendedGarden = 0;

int main() {
    int numPlants;
    vector<string> fruits = {
        "blackberry", "raspberry", "strawberry",
        "blueberry", "tomato", "apple",
        "mango", "jackfruit", "fig"
    };
    cout << "Enter the number of plants you want to create: ";
    cin >> numPlants;

    Plant** plants = new Plant*[numPlants];

    for (int i = 0; i < numPlants; i++) {
        string plantName;
        int matureAge;
        string type;
        cout << "Enter name for plant " << i + 1 << ": ";
        cin >> plantName;
        cout << "Enter mature age for plant " << i + 1 << ": ";
        cin >> matureAge;
        cout << "Enter type of plant (flowering, fruit, vegetable): ";
        cin >> type;

        if (type == "flowering") {
            plants[i] = new FloweringPlant(plantName, matureAge);
        } else if (type == "fruit") {
            auto it = find(fruits.begin(), fruits.end(), type);
            if (it != fruits.end()) {
                plants[i] = new HighYieldFruit(plantName, matureAge);
            } else {
                plants[i] = new FruitPlant(plantName, matureAge);
            }
        }else {
            plants[i] = new Plant(plantName, matureAge);
        }
    }

    Garden* myGarden = new Garden();

    for (int i = 0; i < numPlants; i++) {
        myGarden->addPlant(plants[i]);
    }

    cout << "Initial garden status:" << endl;
    myGarden->showAllPlants();

    cout << endl << "Growing all plants..." << endl;
    myGarden->growAllPlants();
    myGarden->growAllPlants();
    myGarden->growAllPlants();

    cout << "Watering all plants..." << endl;
    myGarden->waterAllPlants(50);

    cout << endl << "Updated garden status:" << endl;
    myGarden->showAllPlants();

    Garden::showNoOfTimesAttended();

    for (int i = 0; i < numPlants; i++) {
        delete plants[i];
    }
    delete[] plants;

    delete myGarden;

    return 0;
}
