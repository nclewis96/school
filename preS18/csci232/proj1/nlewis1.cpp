/**
*Converts a measurment given in yards/feet/in to meters
*
*@author Nathaniel Lewis
*@version 0.9
*@date 8/31/15
********************************************/

#include <iostream>
using namespace std;

/*
*function prototype takes yd/ft/in (int)
*converts to meters
*/
double linearConvert(int yds, int ft, int inches);

int main(int argc, char *arv[])
{
	int yd = 0;
	int ft = 0;
	int in = 0;

	cout << "How many yards?\n";
	cin >> yd;

	cout << "How many feet?\n";
	cin >> ft;

	cout << "How many inches?\n";
	cin >> in;

	double meters = linearConvert(yd, ft, in);
	cout << yd << " yards, " << ft << " feet, " << in << " inches converts  to " << meters << " meters.";
}



/*
* Converts the given measurements into meters
* Assumes given measurements are reasonable and free of error
*yds / 1.0936 = meters
*ft / 3.2808 = meters
*inches / 39.370 = meters
*returns meters
*/
double linearConvert(int yds, int ft, int inches)
{
	double meters = 0;

	meters += yds / 1.0936;
	meters += ft / 3.2808;
	meters += inches / 39.370;

	return meters;
}
