#include <iostream>

using namespace std;


enum Level {
    LOW,
    MEDIUM,
    HIGH
  } level;


  /* string sizeStr;
    switch (p.size) {
        case FlatPizza::small: sizeStr = "small"; break;
        case FlatPizza::large: sizeStr = "large"; break;
        case FlatPizza::family: sizeStr = "family"; break;
    }*/

class Employee {
protected:
    string name;
    int salary;
    static int counter;

public:
    Employee() {
        name = "blank";
        salary = 0;
        cout << "Default constructor called\n";
        counter++;
    }

    Employee(string name, int salary) {
        this->name = name;
        this->salary = salary;
        cout << "Parameterized constructor called\n";
        counter++;
    }

    virtual int calculateSalary()
    {
        return salary;
    }


    Employee(const Employee& e) : name(e.name), salary(e.salary) {
        cout<<"Copy constructor called\n";
        counter++;
    }

    string get_name() {
        return name;
    }

    int get_salary() {
        return salary;
    }

    void set_name(const string& name) {
        this->name = name;
    }

    void set_salary(const int& salary) {
        this->salary = salary;
    }

    void print() {
        cout << "Name: " << name << "\nSalary: " << salary << "\n";
    }

    static int get_counter() {
        return counter;
    }

    bool operator==(const Employee& e)
    {
        if(this->name == e.name)
        {
            return true;
        }
        return false;
    }

    Employee operator+(const Employee& e) {
        return Employee("blank", this->salary + e.salary);
    }

    
    friend ostream& operator<<(ostream& out, const Employee& e) {
        out << "Name: " << e.name << "\nSalary: " << e.salary << "\n";
        return out;
    }

    friend istream& operator>>(istream& in, Employee& e) {
        cout << "Enter name: ";
        in >> e.name;
        cout << "Enter salary: ";
        in >> e.salary;
        return in;
    }
};

class Manager : public Employee {
    protected:
        int bonus;
    
    public:
        Manager(string n, int s, int b) : Employee(n, s), bonus(b) {}
    
        void display() {
            cout << "Name: " << name << ", Salary: " << salary << ", Bonus: " << bonus << endl;
        }

        int calculateSalary(){
            return salary+bonus;
        }
    };



class Director : public Manager {
    protected:
    int coefficient;

    public:

    Director(string n, int s, int b, int c) : Manager(n, s, b), coefficient(c){}

int calculateSalary(){
    return (salary+bonus)*coefficient;
}
};


int Employee::counter = 0;

int main() {
    Employee e1;
    Employee e2("nikola", 50000);
    Employee e3(e2);
    Employee e4 = e2 + e3;

    cout << e1; 

    cout << "Number of employees: " << Employee::get_counter() << endl;

    return 0;
}