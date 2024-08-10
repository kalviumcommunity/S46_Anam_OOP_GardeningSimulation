#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Plant{

    protected:
        string name;
        string growthStage;
        double age;
        int health;
        int matureAge;
        int maxWater;
        int waterLevel;
        int time;

    public:

        Plant(string name, int matureAge){
            this->name = name;
            this->matureAge = matureAge;
            maxWater = 100;
            waterLevel = 0;
            health = 0;
            age = 0;
            growthStage = "Seedling";
        }
        void grow(){
            if (growthStage == "Seedling") {
                if (time >= matureAge / 2) {
                    growthStage = "Growing";
                    health += 20;
                }
            } else if (growthStage == "Growing") {
                if (age >= matureAge) {
                    growthStage = "Mature";
                    health += 15;
                }
            }
            if (age > matureAge) {
                health -= 5;
            } else {
                health += 10;
            }
            age += 0.5;
            time += 1;
        }
        void water(int amount){
            waterLevel = min(maxWater, waterLevel + amount);
        }
        void status(){
            cout << "Plant: " << name << endl;
            cout << "Growth Stage: " << growthStage << endl;
            cout << "Age: " << age << endl;
            cout << "Health: " << health << endl;
            cout << "Water Level: " << waterLevel << endl;
        }
};

class Garden {
    private:
        vector<Plant> plants;

    public:
        void addPlant(const Plant& p){
            plants.push_back(p);
        }
        void waterAllPlants(int amount) {
            for (auto& plant : plants) {
                plant.water(amount);
            }
        }
        void growAllPlants() {
            for (auto& plant : plants) {
                plant.grow();
            }
        }
        void showAllPlants(){
            for (auto& plant : plants) {
                plant.status();
                cout << "----------------" << endl;
            }
        }
};


int main() {
    Garden myGarden;

    Plant plants[2] = {{"Rose",13},{"Tomato",8}};

    int len =  sizeof(plants)/sizeof(plants[0]);

    for (int i = 0; i < len; i++) {
        myGarden.addPlant(plants[i]);
    }

    cout << "Initial garden status:" << endl;
    myGarden.showAllPlants();

    cout << endl;

    cout << "Growing all plants..." << endl;
    myGarden.growAllPlants();


    cout << "Watering all plants..." << endl;
    cout << endl;
    myGarden.waterAllPlants(50);

    cout << "Updated garden status:" << endl;
    myGarden.showAllPlants();

    return 0;
}
