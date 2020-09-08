#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <time.h>
// use namespace for output and input
using namespace std;

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
  double max_err;
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
      h = 1./((double)n + 1);
      double hh = h*h;
      max_err = - pow(10, 7);


      //Define arrays
      double *A = new double [n+2];
      double *B = new double [n+2];
      double *C = new double [n+2];
      double *g = new double [n+2];
      double *x = new double [n+2];
      double *v = new double [n+2]; //Discretized Solution

      for (int i = 0; i < n+2; i++){
        A[i] = a;
        B[i] = b;
        C[i] = c;
        x[i] = i*h;
        g[i] = hh*f(x[i]);
      }

      clock_t start, finish;
      start = clock();

      //Forward Sub
      for (int i = 2; i < n+1; i++){
        B[i] = B[i] - A[i]*C[i-1]/B[i-1];
        g[i] = g[i] - A[i]*g[i-1]/B[i-1];
      }

      //Backwards Sub
      //v[0] = 0.; //v[n-1] = 0.;
      v[n] = g[n]/B[n];
      for (int i = n-1; i > 0; i--){
        v[i] = (g[i] - C[i]*v[i+1])/B[i];
      }
      finish = clock();
      double time =(double)(finish - start)/((double) CLOCKS_PER_SEC);
      delete[] A;
      delete[] B;
      delete[] C;
      delete[] g;

      //Output
      string argument = to_string(exponent);
      if (exponent <= 4){
        string output_file = "output_n";
        output_file.append(argument);
        output_file.append(".txt");
        ofile.open(output_file);
        ofile << setiosflags(ios::showpoint | ios::uppercase);
         //      ofile << "       x:             approx:          exact:       relative error" << endl;
        ofile << setw(15) << setprecision(8) << time*pow(10,6)<<" mu s" <<endl;
        for (int i = 1; i < n-1; i++){
          double RelativeError = log10(fabs((analytic(x[i]) - v[i])/analytic(x[i])));
          if (RelativeError > max_err){
            max_err = RelativeError;}
          ofile << setw(15) << setprecision(8) << x[i];
          ofile << setw(15) << setprecision(8) << v[i];
          ofile << setw(15) << setprecision(8) << analytic(x[i]);
          ofile << setw(15) << setprecision(8) << RelativeError << endl;
        }
        ofile.close();
        cout << "n = 10^" <<  exponent << "   time = " << time << "   max_err "<< max_err << endl;
      }

      if (exponent > 4){
        for (int i = 1; i < n-1; i++){
          double RelativeError = log10(fabs((analytic(x[i]) - v[i])/analytic(x[i])));
          if (RelativeError > max_err){
            max_err = RelativeError;}
        }
      cout << "n = 10^" <<  exponent << "   time = " << time << "   max_err "<< max_err << endl;
      }

      string output_file_err = "max_err_n";
      output_file_err.append(argument);
      ofile.open(output_file_err);
      ofile << setiosflags(ios::showpoint | ios::uppercase);
      ofile << setw(15) << setprecision(8) << max_err;
      ofile.close();

      delete[] x;
      delete[] v;
  }
  return 0;
}
