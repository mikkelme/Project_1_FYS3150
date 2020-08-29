#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
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

    //Define arrays
    double *A = new double [n];   //A = (double*)malloc(n*sizeof(double));
    double *B = new double [n];   //B = (double*)malloc(n*sizeof(double));
    double *C = new double [n];   //C = (double*)malloc(n*sizeof(double));
    for (int i = 0; i < n; i++){
      A[i] = a;
      B[i] = b;
      C[i] = c;
    }

    double *g = new double [n];
    double *x = new double [n];
    for (int i = 0; i < n; i++){
      x[i] = (i)*h;
      g[i] = pow(h,2)*f(x[i]);
    }

    //Forward Sub
    double *B_tilde = new double [n];
    double *g_tilde = new double [n];
    B_tilde[0] = B[0];
    g_tilde[0] = g[0];
    for (int i = 1; i < n; i++){
      B_tilde[i] = B[i] - A[i]*C[i-1]/B_tilde[i-1];
      g_tilde[i] = g[i] - A[i]*g_tilde[i-1]/B_tilde[i-1];
    }

    //cout << g_tilde[0] << endl;
    //Backwards Sub
    double *u = new double [n];
    u[0] = 0.;
    u[n-1] = 0.;
    for (int i = n-1; i > 0; i--){
      u[i-1] = g_tilde[i-1] - (C[i-1]*u[i])/B_tilde[i-1];


    }
    ofile.open("output_file");
    ofile << setiosflags(ios::showpoint | ios::uppercase);
     //      ofile << "       x:             approx:          exact:       relative error" << endl;
    for (int i = 1; i < n-1; i++){
      double RelativeError = fabs((analytic(x[i]) - u[i])/analytic(x[i]));
      ofile << setw(15) << setprecision(8) << x[i];
      ofile << setw(15) << setprecision(8) << u[i];
      ofile << setw(15) << setprecision(8) << analytic(x[i]);
      ofile << setw(15) << setprecision(8) << log10(RelativeError) << endl;
    }
    ofile.close();



    //delete [] x; delete [] d; delete [] b; delete [] solution;






    delete[] A;   //free(A);
    delete[] B;   //free(B);
    delete[] C;   //free(C)

  return 0;
}
