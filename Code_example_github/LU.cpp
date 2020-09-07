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
  int max_exp; //Matrix size: exponent x exponent
  int a;
  int b;
  int c;
  int n;
  double h;
    if (argc <= 1) {
      cout << "Bad Usage: \"" << argv[0] <<
              "\" command-line reads exponent x for integration point n as n = 10^x" << endl;
          exit(1);
    }
    else {
      a = -1;
      b = 2;
      c = -1;
      max_exp = atoi(argv[1]);
    }

    for (int exponent = 1; exponent <= max_exp; exponent++){
      n = pow(10, exponent);
      h = 1./((double)n);
      double hh = h*h;




      n = n-1;  //  shift so that only points between endpoints are studied
      mat A = zeros<mat>(n,n);
      // Set up arrays for the simple case
      vec g(n);  vec x(n);
      A(0,0) = 2.0;  A(0,1) = -1;  x(0) = h;  g(0) =  hh*f(x(0));
      x(n-1) = x(0)+(n-1)*h; g(n-1) = hh*f(x(n-1));
      for (int i = 1; i < n-1; i++){
        x(i) = x(i-1)+h;
	       g(i) = hh*f(x(i));
        A(i,i-1)  = -1.0;
        A(i,i)    = 2.0;
        A(i,i+1)  = -1.0;
      }
      A(n-1,n-1) = 2.0; A(n-2,n-1) = -1.0; A(n-1,n-2) = -1.0;

      clock_t start, finish;
      start = clock();


      // solve Ax = b
      vec v  = solve(A,g);

      finish = clock();
      double time =(double)(finish - start)/((double) CLOCKS_PER_SEC);

      string argument = to_string(exponent);
      string output_file = "output_n";
      output_file.append(argument);
      output_file.append(".txt");

      ofile.open(output_file);
      ofile << setiosflags(ios::showpoint | ios::uppercase);

       //      ofile << "       x:             approx:          exact:       relative error" << endl;
      ofile << setw(15) << setprecision(8) << time*pow(10,6)<<" mu s" <<endl;
      for (int i = 1; i < n-1; i++){
        double RelativeError = fabs((analytic(x[i]) - v[i])/analytic(x[i]));
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