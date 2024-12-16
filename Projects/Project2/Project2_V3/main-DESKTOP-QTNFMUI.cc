#include <iostream>
using namespace std;
int main()
{
int no1, no2, sum, product;

cout << "Input your favorite integer and press Enter.\n";
cin >> no1;
cout << "Now input your least favorite integer and press Enter.\n";
cin >> no2;

sum = no1 + no2;
product = no1 * no2;

cout << "The sum of your two integers is ";
cout << sum;
cout << " and the product of your two integers is ";
cout << product << endl;
}

