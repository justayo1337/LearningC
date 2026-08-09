#include <iostream>


using namespace std;


double square (double x);
void print_square(double x);

int main () {
        print_square(1224);	
	return 0;
}


double square (double x) {

	return (x*x);
}

void print_square(double x ){

	cout << "The square of x is: " << square(x) << "\n";

}
