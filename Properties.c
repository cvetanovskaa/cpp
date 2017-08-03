/*
Properties Problem 4 (2 / 5)
Create abstract class for Property that has:

address (array of max 50 chars)
city (array of max 50 chars)
area (float)
Overload the following operators:

operator << - for printing address, city and area.
operator < - for comparing properties by their estimated price.
From this class derive House and Building.

For each house there is:

number of floors (integer)
area of one floor (float). (The area of each floor is equal)
if it has sub roof (bool)
For each building there is:

area of one apartment
number of apartments
For each property the price should be estimated:

the price of the house is estimated as: areaHouse∗700+areaSubroof∗450
the price of the building is estimated as: (areaApartment∗800)∗aparmentsNumber+aparmentsNumber∗500
Write external function void mostExpensiveProperty that accepts array of pointers to objects of class Property and their number and prints the info of the property with highest price.
*/

#include <iostream>
#include <cstring>
using namespace std;

class Property{
protected:
    char address[50];
    char city[50];
    float area;
public:
    Property(char*a,char*c,float ar)
    {
        strcpy(address,a);
        strcpy(city,c);
        area=ar;
    }
    friend ostream&operator<<(ostream&o, Property&p)
    {
        o<<"Address: "<<p.address<<endl;
        o<<"City: "<<p.city<<endl;
        o<<p.area<<" square meters"<<endl;
        return o;
    }
    virtual float estimatedPrice()=0;
    bool operator<( Property&p)
    {
        if(this->estimatedPrice()<p.estimatedPrice())
            return true;
        else return false;
    }
    virtual ~Property(){}
};


class House: public Property{
private:
    int noFloors;
    float areaFloor;
    bool hasSubRoof;
public:
    House(char*a,char*c,float ar, int noF,float aF, bool hSR):Property(a,c,ar)
    {
        noFloors=noF;
        areaFloor=aF;
        hasSubRoof=hSR;
    }
    float estimatedPrice()
    {
        if(hasSubRoof)
        {
        return areaFloor*noFloors*700+areaFloor*450;
        }
        else return areaFloor*noFloors*700;
    }
};
class Building: public Property{
private:
    float areaApartment;
    int apartments;
public:
     Building(char*a,char*c,float ar,int ap,float aA):Property(a,c,ar)
    {
        areaApartment=aA;
        apartments=ap;
    }
    float estimatedPrice()
    {
        return((areaApartment*800)*apartments+apartments*500);
    }
};

void mostExpensiveProperty(Property **p, int n) {

    int id=0;
    for(int i=1; i<n; i++)
    {
        if(p[id] < p[i])
            id=i;
    }
    cout << *p[id];
}

int main() {
    int n;
    int tip_nedviznost;

    cin >> n;

    Property **ned = new Property*[n];
    char adresa[100];
    char grad[30] ;
    float kvadratura;
    for(int i = 0; i < n; ++i) {
        cin >> tip_nedviznost>> adresa >> grad >> kvadratura;
        if(tip_nedviznost==1) {
            int br_kat;
            float kvadrat_kat;
            bool potkrovje;
            cin >> br_kat >> kvadrat_kat >> potkrovje;
            ned[i] = new House(adresa, grad, kvadratura, br_kat, kvadrat_kat, potkrovje);
        }
        else if(tip_nedviznost == 2) {
            int br_stanovi;
            float kvadrat_na_stan;
            cin >> br_stanovi >> kvadrat_na_stan;

            ned[i] = new Building(adresa, grad, kvadratura, br_stanovi, kvadrat_na_stan);
        }
    }

    cout<<"== PROPERTIES =="<<endl;
    for (int i=0; i<n; i++){
    	cout<<*(ned[i])<<"Price: "<< ned[i]->estimatedPrice()<<endl;
    }

    cout << "=== MOST EXPENSIVE PROPERTY ===" << endl;
    mostExpensiveProperty(ned, n);

    return 0;
}
