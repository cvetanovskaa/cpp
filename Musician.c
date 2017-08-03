/*
Musician Problem 5 (1 / 4)
Define a class Musician that has info on:

name (char array max 100)
earnings (float)
performances (int)
gender (char M/F).
Overload:

operator << for printing the name, earnings and gender (M/F)
operator > for comparing musician performance price and float.
From this class derive two new classes Guitarist and Drummer.

For the guitarist additionally we have:

guitar price (float).
For the drummer additionally we have:

age (integer).
The performance price of the musician is computed by the following rules:

for the guitarist the price per performance is GUITARPRICE10
for the drummer the price per performance is AGE∗50
Each musician pays tax per earnings. Write the methods for computing taxes:

for guitarists: if the number of performances is larger than 30 the tax rate is 8% from the earnings, 10% otherwise.
for drummers: if it's man than the tax rate is 12% from the earnings, 10% otherwise.
Write a external function mostExpensiveMusician that as arguments accepts array of pointers to Musician and their number and prints the info for the musician with highest performance price.
*/

#include <iostream>
#include <cstring>

using namespace std;

class Musician {
protected:
    char name[100];
    float earnings;
    int performances;
    char gender;
public:
    Musician(char*n,float e, int p, char g)
    {
        strcpy(name,n);
        earnings=e;
        performances=p;
        gender=g;
    }
    friend ostream&operator<<(ostream&o,Musician&m)
    {
        o<<m.name<<endl;
        o<<m.earnings<<endl;
        o<<m.gender<<endl;
        return o;
    }
    bool operator>(Musician&m)
    {
        return earnings>m.earnings;
    }
    virtual float performancePrice()=0;
    virtual float taxPerEarnings()=0;
    ~Musician (){}
};
class Guitarist:public Musician{
private:
    float gPrice;
public:
    Guitarist(char*n,float e, int p, char g, float gP):Musician(n,e,p,g)
    {
        gPrice=gP;
    }
    float performancePrice()
    {
        return (gPrice/10);
    }
    float taxPerEarnings()
    {
        if(performances>30)
        {
            return earnings*0.08;
        }
        return earnings*0.1;
    }
};
class Drummer:public Musician{
private:
    int age;
public:
    Drummer(char*n,float e, int p, char g, int a):Musician(n,e,p,g)
    {
        age=a;
    }
    float performancePrice()
    {
        return age*50;
    }
    float taxPerEarnings()
    {
        if(gender=='M' || gender=='m')
        {
            return earnings*0.12;
        }
        return earnings*0.1;
    }
};

void mostExpensiveMusician(Musician**m,int n)
{
    int x=0;
    for(int i=0;i<n;i++)
    {

        if(*m[i]>*m[x])
        {
            x=i;
        }
    }
    cout<<*m[x];

}


int main() {
	int n, x;
	cin >> n >> x;
	Musician **m = new Musician*[n];
	for(int i = 0; i < n; ++i) {
		char ime[100];
		float zarabotka;
		int nastapi;
		char pol;
		cin >> ime >> zarabotka >> nastapi >> pol;
		if(i < x) {
			float cena_gitara;
			cin >> cena_gitara;
			m[i] = new Guitarist(ime, zarabotka, nastapi, pol, cena_gitara);
		} else {
			int vozrast;
			cin >> vozrast;
			m[i] = new Drummer(ime, zarabotka, nastapi, pol, vozrast);
		}
	}
	cout << "=== TAX ===" << endl;
	for(int i = 0; i < n; ++i) {
        cout << *m[i];
		cout << m[i]->taxPerEarnings() << endl;
	}
	cout << "=== MOST EXPENSIVE ===" << endl;
	mostExpensiveMusician(m, n);

    for(int i = 0; i < n; ++i) {
		delete m[i];
    }
    delete [] m;
	return 0;
}

