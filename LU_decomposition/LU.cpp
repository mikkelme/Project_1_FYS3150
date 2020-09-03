#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <armadillo>
// If compile gives: "linker command failed" try adding "-larmadillo" at the end of commandline
//example: c++ -o LU.exe LU.cpp -larmadillo
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

    }

    for (int exponent = 0; exponent <= max_exp; exponent++){
      n = pow(10, exponent);
      h = 1./((double)n - 1.);


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
    vec v  = solve(A,g);

    string argument = to_string(exponent);
    string output_file = "output_n";
    output_file.append(argument);
    output_file.append(".txt");

    ofile.open(output_file);
    ofile << setiosflags(ios::showpoint | ios::uppercase);

     //      ofile << "       x:             approx:          exact:       relative error" << endl;
    ofile << setw(15) << setprecision(8) << time*pow(10,6)<<" mu s" <<endl;
    for (int i = 1; i < n-1; i++){
      double RelativeError = fabs((analytic(x[i]) - u[i])/analytic(x[i]));
      ofile << setw(15) << setprecision(8) << x[i];
      ofile << setw(15) << setprecision(8) << v[i];
      ofile << setw(15) << setprecision(8) << analytic(x[i]);
      ofile << setw(15) << setprecision(8) << log10(RelativeError) << endl;
    }
    ofile.close();

    cout << "n = 10^" <<  exponent << "   time = " << time*pow(10, 6) << " mu s"<< endl;

  }
  return 0;
}
