// Да се креира апстрактна класа Pizza за опишување пици. (5 поени) За секоја пица се чуваат следните информации:

// име (низа од максимум 20 знаци)
// состојки (низа од максимум 100 знаци)
// основна цена (реален број)
// Од оваа класа да се изведат класите FlatPizza и FoldedPizza за опишување на рамни и преклопени пици соодветно (5 поени).

// За секоја рамна пица дополнително се чува големина (enum - една од три можности: мала, голема и фамилијарна). За секоја преклопена пица дополнително се чува информација дали тестото е од бело брашно или не (boolean).

// За секоја пица треба да се обезбеди метод за пресметување на нејзината продажна цена:

// цената на рамната пица се пресметува така што основната цена се зголемува за 10%, 30% и 50% за мала, голема и фамилијарна пица соодветно.
// цената на преклопената пица се пресметува така што основната цена се зголемува за 10% ако е тестото е од бело брашно, а во спротивно за 30%. (10 поени)
// Да се преоптоварат следните оператори:

// оператор << - за печатење сите податоци за пиците во следниов формат:

// За рамна пица:[име]: [состојки], [големина] - [продажната цена на пицата]. 
// За преклопена пица: [име]: [состојки], [wf - ако е со бело брашно / nwf - ако не е со бело брашно] - [продажната цена на пицата]
// (5 поени)

// оператор < - за споредување на пиците од каков било вид според нивната продажна цена. (5 поени)
// Да се дефинира глобална функција еxpensivePizza што на влез прима низа од покажувачи кон објекти од класата Pizza и нивниот број, а како резултат ги печати информациите за пицата со највисока продажна цена. Ако има повеќе пици со иста највисока цена, се печати првата. (10 поени)

// Да се дефинираат потребните конструктори и методи во класите за правилно функционирање на програмата. (5 поени)

#include <cstring>
#include <iostream>
using namespace std;

class Pizza {

protected:

    string name;
    string ingredients;
    double price;
    
public:

    Pizza(string n, string i, double p): name(n), ingredients(i), price(p) {}

    virtual double calculatePrice() const = 0;

    bool operator<(const Pizza& p)
    {
        if(this->price<p.price)
        {
            return true;
        }

        else{
            return false;
        }
    }

    virtual ~Pizza() {}



};


class FlatPizza : public Pizza {

protected:
    

public:
enum Size {
    small,
    large,
    family
} size;

FlatPizza(string n, string i, double p, Size s): Pizza(n, i, p), size(s) {} 

double calculatePrice() const override {
    if (size == FlatPizza::small) {
        return price * 1.1; 
    } else if (size == FlatPizza::large) {
        return price * 1.3;
    } else { 
        return price * 1.5; 
    }
}

friend ostream& operator<<(ostream& out, const FlatPizza& p) {
    string sizeStr;
    switch (p.size) {
        case FlatPizza::small: sizeStr = "small"; break;
        case FlatPizza::large: sizeStr = "large"; break;
        case FlatPizza::family: sizeStr = "family"; break;
    }
    out << "Name: " << p.name << "\tIngredients: " << p.ingredients << ", " <<sizeStr<< " - " << p.calculatePrice() << "\n";
    return out;
}


};

class FoldedPizza : public Pizza {

protected:
    bool wheatFlour;

public:

FoldedPizza(string n, string i, double p, bool w): Pizza(n, i, p), wheatFlour(w) {}

double calculatePrice() const override{

    if(wheatFlour==true)
    {
        return price*1.1;
    }
    else{
        return price*1.3;
    }

}


    friend ostream& operator<<(ostream& out, const FoldedPizza& p) {

        out << "Name: " << p.name << "\tIngredients: " << p.ingredients << ", " <<(p.wheatFlour ? "wf":"nwf")<< " - " << p.calculatePrice() << "\n";
        return out;
    }

    

   
    

};

void expensivePizza(Pizza** pizzas, int n) {
    if (n == 0) {
        cout << "No pizzas available." << endl;
        return;
    }

    Pizza* mostExpensive = pizzas[0]; 

    for (int i = 1; i < n; i++) {
        if (pizzas[i]->calculatePrice() > mostExpensive->calculatePrice()) {
            mostExpensive = pizzas[i];
        }
    }

    FlatPizza* flatPizza = dynamic_cast<FlatPizza*>(mostExpensive);
    if (flatPizza) {
        cout << *flatPizza;
    } else {
        FoldedPizza* foldedPizza = dynamic_cast<FoldedPizza*>(mostExpensive);
        if (foldedPizza) {
            cout << *foldedPizza;
        }
    }
}


int main() {
    // Create an array of Pizza pointers
    Pizza* pizzas[4];

    // Create FlatPizza objects
    pizzas[0] = new FlatPizza("Margherita", "Tomato, Mozzarella", 500, FlatPizza::small);
    pizzas[1] = new FlatPizza("Pepperoni", "Tomato, Mozzarella, Pepperoni", 600, FlatPizza::family);

    // Create FoldedPizza objects
    pizzas[2] = new FoldedPizza("Calzone", "Ham, Cheese, Mushrooms", 550, true);
    pizzas[3] = new FoldedPizza("Veggie", "Spinach, Cheese, Olives", 450, false);

    // Test calculatePrice for each pizza
    cout << "Testing calculatePrice for each pizza:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "Pizza " << i + 1 << ": " << pizzas[i]->calculatePrice() << endl;
    }
    cout << endl;

    // Test overloaded << operator
    cout << "Testing overloaded << operator:" << endl;
    for (int i = 0; i < 4; i++) {
        FlatPizza* flatPizza = dynamic_cast<FlatPizza*>(pizzas[i]);
        if (flatPizza) {
            cout << *flatPizza;
        } else {
            FoldedPizza* foldedPizza = dynamic_cast<FoldedPizza*>(pizzas[i]);
            if (foldedPizza) {
                cout << *foldedPizza;
            }
        }
    }
    cout << endl;

    // Test overloaded < operator
    cout << "Testing overloaded < operator:" << endl;
    if (*pizzas[0] < *pizzas[1]) {
        cout << "Pizza 1 is cheaper than Pizza 2" << endl;
    } else {
        cout << "Pizza 1 is not cheaper than Pizza 2" << endl;
    }
    cout << endl;

    // Test expensivePizza function
    cout << "Testing expensivePizza function:" << endl;
    expensivePizza(pizzas, 4);
    cout << endl;

    // Clean up dynamically allocated memory
    for (int i = 0; i < 4; i++) {
        delete pizzas[i];
    }

    return 0;
}