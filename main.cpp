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

    private:
        static int totalPlants;

    public:

        ~Plant(){
            totalPlants--;
            cout << "A plant was destroyed" << endl;
        }

        Plant(string name, int matureAge){
            this->name = name;
            this->matureAge = matureAge;
            maxWater = 100;
            waterLevel = 0;
            health = 0;
            age = 0;
            growthStage = "Seedling";
            totalPlants++;
        }
        string getName(){
            return name;
        }
        void setName(string newName){
            name = newName;
        }
        int getWaterLevel(){
            return waterLevel;
        }
        int getAge(){
            return age;
        }
        void setWaterLevel(int amount) {
            waterLevel = min(maxWater, waterLevel+amount);
        }
        void updateAge(double age){
            this->age += age;
        }
        void updateTime(int time){
            this->time = time;
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
            updateAge(0.5);
            updateTime(1);
        }
        void water(int amount){
            setWaterLevel(amount);
        }
        void status(){
            cout << "Plant: " << getName() << endl;
            cout << "Growth Stage: " << growthStage << endl;
            cout << "Age: " << getAge() << endl;
            cout << "Health: " << health << endl;
            cout << "Water Level: " << getWaterLevel() << endl;
        }
        static void showTotalPlants(){
            cout << endl << "Total Plants: " << totalPlants << endl;
        }
};

int Plant::totalPlants = 0;

class Garden {
    private:
        vector<Plant*> plants;
        static int attendedGarden;
    public:
        ~Garden(){
            attendedGarden--;
            cout << "A Garden was destroyed" << endl;
        }
        static int getAttendedGarden() {
            return attendedGarden;
        }
        static void setAttendedGarden(int times) {
            attendedGarden = times;
        }
        void addPlant(Plant* p){
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
        void showAllPlants(){
            for (auto plant : plants) {
                cout << "----------------" << endl;
                plant->status();
                cout << "----------------" << endl;
                Plant::showTotalPlants();
            }
        }
        static void showNoOfTimesAttended(){
            cout << "Number of times Garden was attended: " << Garden::getAttendedGarden() << endl;
        };
};

int Garden::attendedGarden = 0;

int main() {

    int numPlants;
    cout << "Enter the number of plants you want to create: ";
    cin >> numPlants;

    Plant** plants = new Plant*[numPlants];

    for (int i = 0; i < numPlants; i++) {
        string plantName;
        int matureAge;
        cout << "Enter name for plant " << i + 1 << ": ";
        cin >> plantName;
        cout << "Enter mature age for plant " << i + 1 << ": ";
        cin >> matureAge;

        plants[i] = new Plant(plantName, matureAge);
    }

    Garden* myGarden = new Garden();

    for (int i = 0; i < numPlants; i++) {
        myGarden->addPlant(plants[i]);
    }

    cout << "Initial garden status:" << endl;
    myGarden->showAllPlants();

    cout << endl << "Growing all plants..." << endl;
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