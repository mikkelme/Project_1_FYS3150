#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
// use namespace for output and input
using namespace std;


//Functions
inline double f(double x){
  return 100.0*exp(-10*x);}
inline double analytic(double x){
  return 1.0-(1-exp(-10))*x-exp(-10*x);}


//Main program (Solves equation: Av = f)
int main(int argc, char *argv[])
{
  //Read file and exponent from command line
  int exponent; //Matrix size: exponent x exponent
  string filename; //File contains X---X ????
    if (argc <= 1) {
      cout << "Bad Usage: \"" << argv[0] <<
              "\" reads filename and max power 10^n as command line input" << endl;
          exit(1);
    }
    else {
      filename = argv[1];
      exponent = atoi(argv[2]);
    }













  return 0;
}
