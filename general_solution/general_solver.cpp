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


      //Define arrays
      double *A = new double [n];
      double *B = new double [n];
      double *C = new double [n];
      double *g = new double [n];
      double *x = new double [n];
      double *v = new double [n]; //Discretized Solution

      for (int i = 0; i < n; i++){
        A[i] = a;
        B[i] = b;
        C[i] = c;
        x[i] = i*h;
        g[i] = hh*f(x[i]);
      }

      clock_t start, finish;
      start = clock();

      //Forward Sub
      for (int i = 2; i < n; i++){
        B[i] = B[i] - A[i]*C[i-1]/B[i-1];
        g[i] = g[i] - A[i]*g[i-1]/B[i-1];
      }

      //Backwards Sub
      v[0] = 0.; //v[n-1] = 0.;
      v[n-1] = g[n-1]/B[n-1];
      for (int i = n-2; i > 0; i--){
        v[i] = (g[i] - C[i]*v[i+1])/B[i];
      }
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
      delete[] A;   //free(A);
      delete[] B;   //free(B);
      delete[] C;   //free(C)


  }
  return 0;
}




/*
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
      max_exp = atoi(argv[4]);
    }

    for (int exponent = 1; exponent <= max_exp; exponent++){
      n = pow(10, exponent);
      h = 1./((double)n);
      clock_t start, finish;
      start = clock();

      //Define arrays
      double *A = new double [n];   //A = (double*)malloc(n*sizeof(double));
      double *B = new double [n];   //B = (double*)malloc(n*sizeof(double));
      double *C = new double [n];   //C = (double*)malloc(n*sizeof(double));
      double *g = new double [n];
      double *x = new double [n];
      double hh = h*h;
      for (int i = 0; i <= n; i++){
        A[i] = a;
        B[i] = b;
        C[i] = c;
        x[i] = (i)*h;
        g[i] = hh*f(x[i]);
      }


      //Forward Sub
      double *B_tilde = new double [n];
      double *g_tilde = new double [n];
      B_tilde[0] = B[0];
      g_tilde[1] = g[1];
      for (int i = 1; i < n; i++){
        B_tilde[i] = B_tilde[i] - A[i]*C[i-1]/B_tilde[i-1];
        cout << B_tilde[i] << endl;
      }
      for (int i = 2; i < n; i++){
        g_tilde[i] = g[i] - A[i]*g_tilde[i-1]/B_tilde[i-1];
      }


      //Backwards Sub
      double *v = new double [n];
      v[0] = 0.;
      v[n-1] = 0.;
      cout << B_tilde[n-1] << endl;
      for (int i = n-1; i > 0; i--){
        v[i] = g_tilde[i] - (C[i]*v[i+1])/B_tilde[i];
      }
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
      delete[] A;   //free(A);
      delete[] B;   //free(B);
      delete[] C;   //free(C)


  }
  return 0;
}
*/
