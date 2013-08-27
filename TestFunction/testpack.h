#ifndef TESTPACK_H
#define TESTPACK_H

# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
# include <ctime>
# include <string.h>

double genz_function (int indx, int ndim, double z[], double alpha[], double beta[]);
double genz_integral (int indx, int ndim, double alpha[], double beta[]);
std::string genz_name (int index);
double genz_phi (double z);
double genz_random (int *seed);
int i4_max (int i1, int i2);
int i4_min (int i1, int i2);
int i4_power (int i, int j);
int i4vec_sum (int n, int a[]);
double r8_abs (double x);
double r8_epsilon (void);
double r8_max (double x, double y);
double r8_min (double x, double y);
double r8vec_dot (int n, double a1[], double a2[]);
void r8vec_median (int n, double r[], double rmed[3]);
double r8vec_product (int n, double a[]);
double r8vec_sum (int n, double a[]);
void tuple_next (int m1, int m2, int n, int *rank, int x[]);

#endif // TESTPACK_H
