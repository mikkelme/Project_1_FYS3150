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
  int d;
  int e;
  int n;
  double h;
    if (argc <= 1) {
      cout << "Bad Usage: \"" << argv[0] <<
              "\" command-line reads exponent x for integration point n as n = 10^x" << endl;
          exit(1);
    }
    else {
      d = 2;
      e = -1;
      max_exp = atoi(argv[1]);
    }

    for (int exponent = 1; exponent <= max_exp; exponent++){
      n = pow(10, exponent);
      h = 1./((double)n);
      double hh = h*h;
      max_err = - pow(10, 7);



      //Define arrays
      double *D = new double [n];
      double *E = new double [n];
      double *g = new double [n];
      double *x = new double [n];
      double *v = new double [n];

      for (int i = 0; i < n; i++){
        x[i] = i*h;
        g[i] = hh*f(x[i]);
      }

      clock_t start, finish;
      start = clock();

      //Forward Sub
      D[0] = d;
      for (int i = 1; i < n; i++){
        D[i] = (i + 1.)/1.;
        g[i] = g[i] + (i-1.)*g[i-1]/i;
      }

      //Backwards sub
      for (int i = n-1; i > 0; i--){
        v[i] = i/(i+1.)*(g[i] + v[i+1]);
      }

      finish = clock();
      double time =(double)(finish - start)/((double) CLOCKS_PER_SEC);
      delete[] D;
      delete[] E;
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
        cout << "n = 10^" <<  exponent << "   time = " << time*pow(10, 6) << " mu s   max_err "<< max_err << endl;
      }

      if (exponent > 4){
        for (int i = 1; i < n-1; i++){
          double RelativeError = log10(fabs((analytic(x[i]) - v[i])/analytic(x[i])));
          if (RelativeError > max_err){
            max_err = RelativeError;}
        }
      cout << "n = 10^" <<  exponent << "   time = " << time*pow(10, 6) << " mu s   max_err "<< max_err << endl;
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
