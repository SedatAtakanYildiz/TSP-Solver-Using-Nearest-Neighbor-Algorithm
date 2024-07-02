#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct City {
    int x, y;
    bool visited;
};

double distance(City a, City b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int nearestNeighbor(const vector<City>& cities, int currentCity) {
    double minDistance = numeric_limits<double>::max();
    int nearestCity = -1;

    for (size_t i = 0; i < cities.size(); ++i) {
        if (!cities[i].visited && i != currentCity) {
            double dist = distance(cities[currentCity], cities[i]);
            if (dist < minDistance) {
                minDistance = dist;
                nearestCity = i;
            }
        }
    }

    return nearestCity;
}

void TSP_NearestNeighbor(vector<City>& cities) {
    double totalCost = 0;
    int currentCity = 0;

    cout << "Optimal maliyeti saglayan path: ";
    cout << currentCity << " ";

    for (size_t i = 1; i < cities.size(); ++i) {
        cities[currentCity].visited = true; 
        int nextCity = nearestNeighbor(cities, currentCity); 
        cout << nextCity << " "; 
        totalCost += distance(cities[currentCity], cities[nextCity]);
        currentCity = nextCity;
    }

   
    totalCost += distance(cities[currentCity], cities[0]);

    
    cout << "0" << endl;
    cout << "Optimal maliyet degeri: " << totalCost << endl;
}

void processFile(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Dosya acilamadi: " << fileName << endl;
        return;
    }

    int cityCount;
    file >> cityCount;

    vector<City> cities(cityCount);

    for (int i = 0; i < cityCount; ++i) {
        file >> cities[i].x >> cities[i].y;
        cities[i].visited = false;
    }
    file.close();

    auto start = high_resolution_clock::now();

    TSP_NearestNeighbor(cities);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Dosya " << fileName << " icin programin calisma suresi: " << duration.count() << " milisaniye" << endl;
}

int main() {
    vector<string> fileNames = {
        "tsp_51_1",
        "tsp_100_2",
        "tsp_783_1",
        "tsp_4461_1",
        "tsp_85900_1"
    };

    for (const string& fileName : fileNames) {
        processFile(fileName);
    }

    cout << "Programi kapatmak icin 1'e basin...";
    char input;
    cin >> input;

    if (input == '1') {
        return 0;
    } else {
        cout << "Hatali giris. Program kapanmadi." << endl;
        return 1;
    }
}