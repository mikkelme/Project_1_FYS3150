#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <armadillo>
// use namespace for output and input
using namespace std;
using namespace arma;

// object for output files
ofstream ofile;

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
  int a;
  int b;
  int c;
  int n;
  double h;
    if (argc <= 3) {
      cout << "Bad Usage: \"" << argv[0] <<
              "\" reads integers a, b, c and then max power 10^n as command line input" << endl;
          exit(1);
    }
    else {
      a = atoi(argv[1]);
      b = atoi(argv[2]);
      c = atoi(argv[3]);
      exponent = atoi(argv[4]);
      n = pow(10, exponent);
      h = 1./((double)n - 1.);
    }


    //Matrix
    mat A = zeros<mat>(n,n);
    vec x(n);  vec g(n);
    double hh = h*h;


    A(0,0) = b; A(0,1) = c;
    x(0) = h; x(n-1) = (n-1)*h;
    g(0) = hh*f(x(0)); g(n-1) = hh*f(x(n-1));

    for (int i = 1; i < n-1; i++){
        x(i) = (i)*h;
        g(i) = hh*f(x(i));
        A(i,i-1)  = a;
        A(i,i)    = b;
        A(i,i+1)  = c; }
    A(n-1,n-2) = a; A(n-1,n-1) = b; A(n-2,n-1) = c;


    //vec u(n);
    //u = solve(A,g);
    vec u  = solve(A,g);



  return 0;
}
