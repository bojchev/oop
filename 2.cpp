#include <iostream>
#include <cstring>

using namespace std;

class Library {
protected:
    string name;
    string city;
    double cost;
    

    

public:
    bool weekend;
    virtual void printDetail() = 0;
    virtual double calculateMembershipCardCost() = 0;
    Library(string n, string c, double co, bool w) : name(n), city(c), cost(co), weekend(w) {}
    virtual ~Library() {} // Virtual destructor
};

class AcademicLibrary : public Library {
protected:
    bool research;
    int specialised;

public:
    AcademicLibrary(string n, string c, double co, bool w, bool r, int s)
        : Library(n, c, co, w), research(r), specialised(s) {}

    double calculateMembershipCardCost() override {
        if (research == true) {
            return cost * 1.24 + specialised * 6; // Fixed comma
        } else {
            return cost + specialised * 6;
        }
    }

    void printDetail() override {
        double c = calculateMembershipCardCost();
        cout << name << " - (Academic) " << city << " "
             << (research ? "Yes" : "No") << " " << c << "\n";
    }
};

class NationalLibrary : public Library {
protected:
    bool educational;
    int national;

public:
    NationalLibrary(string n, string c, double co, bool w, bool r, int s)
        : Library(n, c, co, w), educational(r), national(s) {}

    double calculateMembershipCardCost() override {
        if (educational == true) {
            return cost * 0.93 + national * 15; // Fixed and replaced 'educational' with 'national'
        } else {
            return cost + national * 15; // Replaced 'educational' with 'national'
        }
    }

    void printDetail() override {
        double c = calculateMembershipCardCost();
        cout << name << " - (National) " << city << " "
             << (educational ? "Yes" : "No") << " " << c << "\n";//ovde moze da ti treba (p.educational ? "Yes" : "No")
    }

   
    
};

 int findMostExpensiveNationalLibrary(Library **l, int n) {
        int index = -1;
        double maxCost = 0;
    
        for (int i = 0; i < n; ++i) {
            
            NationalLibrary* natLib = dynamic_cast<NationalLibrary*>(l[i]);
            if (natLib != nullptr) {
                double currentCost = natLib->calculateMembershipCardCost();
                if (currentCost > maxCost || 
                    (currentCost == maxCost && natLib->weekend)) {
                    maxCost = currentCost;
                    index = i;
                }
            }
        }
    
        return index;
    }

int main() {
   int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Library** m = new Library*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        bool weekend_working;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> weekend_working;
        cin.ignore();

        if (type == 1) {
            bool open_cooperation;
            int specialized_articles;

            cin >> open_cooperation >> specialized_articles;
            cin.ignore();

            m[i] = new AcademicLibrary(name, city, base_price, weekend_working, open_cooperation, specialized_articles);
        } else {
            bool cultural_program;
            int national_articles;

            cin >> cultural_program >> national_articles;
            cin.ignore();

            m[i] = new NationalLibrary(name, city, base_price, weekend_working, cultural_program, national_articles);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateMembershipCardCost() << endl;
        }
        cout << "calculateMembershipCardCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
   else if(testCase == 4){
        int most_expensive_nat_lib_index = findMostExpensiveNationalLibrary(m, n);
        if(most_expensive_nat_lib_index>=0){
            m[most_expensive_nat_lib_index]->printDetail();
        }else{
            cout << "National Library not found in the array!"<<endl;
        }
        cout << "findMostExpensiveNationalLibrary method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}