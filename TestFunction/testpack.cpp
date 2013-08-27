#include "testpack.h"

//****************************************************************************80

double genz_function (int indx, int ndim, double z[], double alpha[], double beta[])

//****************************************************************************80
//
//  Purpose:
//
//    GENZ_FUNCTION evaluates one of the test integrand functions.
//
//  Modified:
//
//    26 May 2007
//
//  Author:
//
//    Original FORTRAN77 version by Alan Genz
//    C++ version by John Burkardt
//
//  Reference:
//
//    Alan Genz,
//    A Package for Testing Multiple Integration Subroutines,
//    in Numerical Integration:
//    Recent Developments, Software and Applications,
//    edited by Patrick Keast, Graeme Fairweather,
//    D Reidel, 1987, pages 337-340,
//    LC: QA299.3.N38.
//
//  Parameters:
//
//    Input, int INDX, the index of the test function.
//
//    Input, int NDIM, the spatial dimension.
//
//    Input, double Z[NDIM], the point at which the integrand 
//    is to be evaluated.
//
//    Input, double ALPHA[NDIM], BETA[NDIM], parameters 
//    associated with the integrand function.
//
//    Output, double GENZ_FUNCTION, the value of the test function.
//
{
  int j;
  const double pi = 3.14159265358979323844;
  bool test;
  double total;
  double value;

  value = 0.0;
//
//  Oscillatory.
//
  if ( indx == 1 )
  {
    total = 2.0 * pi * beta[0] + r8vec_sum ( ndim, z );
    value = cos ( total );
  }
//
//  Product Peak.
//
  else if ( indx == 2 )
  {
    total = 1.0;
    for ( j = 0; j < ndim; j++ )
    {
      total = total * (
        1.0 / pow ( alpha[j], 2) + pow ( z[j] - beta[j], 2 ) );
    }
    value = 1.0 / total;
  }
//
//  Corner Peak.
//
  else if ( indx == 3 )
  {
//
//  For this case, the BETA's are used to randomly select
//  a corner for the peak.
//
    total = 1.0;
    for ( j = 0; j < ndim; j++ )
    {
      if ( beta[j] < 0.5 )
      {
        total = total + z[j];
      }
      else
      {
        total = total + alpha[j] - z[j];
      }
    }
    value = 1.0 / pow ( total, ndim + 1 );
  }
//
//  Gaussian.
//  C++ math library complains about things like exp ( -700 )!
//
  else if ( indx == 4 )
  {
    total = 0.0;
    for ( j = 0; j < ndim; j++ )
    {
      total = total + pow ( alpha[j] * ( z[j] - beta[j] ), 2 );
    }
    total = r8_min ( total, 100.0 );
    value = exp ( - total );
  }
//
//  C0 Function.
//
  else if ( indx == 5 )
  {
    total = 0.0;
    for ( j = 0; j < ndim; j++ )
    {
      total = total + alpha[j] * r8_abs ( z[j] - beta[j] );
    }
    value = exp ( - total );
  }
//
//  Discontinuous.
//
  else if ( indx == 6 )
  {
    test = false;

    for ( j = 0; j < ndim; j++ )
    {
      if ( beta[j] < z[j] )
      {
        test = true;
        break;
      }
    }
    if ( test )
    {
      value = 0.0;
    }
    else
    {
      total = r8vec_dot ( ndim, alpha, z );
      value = exp ( total );
    }
  }
  return value;
}
//****************************************************************************80

double genz_integral ( int indx, int ndim, double alpha[], double beta[] )

//****************************************************************************80
//
//  Purpose:
//
//    GENZ_INTEGRAL computes the exact integrals of the test functions.
//
//  Modified:
//
//    26 May 2007
//
//  Author:
//
//    Original FORTRAN77 version by Alan Genz
//    C++ version by John Burkardt
//
//  Reference:
//
//    Alan Genz,
//    A Package for Testing Multiple Integration Subroutines,
//    in Numerical Integration:
//    Recent Developments, Software and Applications,
//    edited by Patrick Keast, Graeme Fairweather,
//    D Reidel, 1987, pages 337-340,
//    LC: QA299.3.N38.
//
//  Parameters:
//
//    Input, int INDX, the index of the test.
//
//    Input, int NDIM, the spatial dimension.
//
//    Input, double A[NDIM], B[NDIM], the lower and upper limits
//    of integration.
//
//    Input, double ALPHA[NDIM], BETA[NDIM], parameters 
//    associated with the integrand function.
//
//    Output, double GENZ_INTEGRAL, the exact value of the integral.
//
{
  double ab;
  int *ic;
  int isum;
  int j;
  const double pi = 3.14159265358979323844;
  int rank;
  double s;
  double sgndm;
  double total;
  double value;
//
//  Oscillatory.
//
  if ( indx == 1 )
  {
    value = 0.0;
//
//  Generate all sequences of NDIM 0's and 1's.
//
    rank = 0;
    ic = new int[ndim];

    for ( ; ; )
    {
      tuple_next ( 0, 1, ndim, &rank, ic );

      if ( rank == 0 )
      {
        break;
      }

      total = 2.0 * pi * beta[0];
      for ( j = 0; j < ndim; j++ )
      {
        if ( ic[j] != 1 )
        {
          total = total + alpha[j];
        }
      }

      isum = i4vec_sum ( ndim, ic );

      s = 1 + 2 * ( ( isum / 2 ) * 2 - isum );

      if ( ( ndim % 2 ) == 0 )
      {
        value = value + s * cos ( total );
      }
      else
      {
        value = value + s * sin ( total );
      }
    }
    delete [] ic;

    if ( 1 < ( ndim % 4 ) )
    {
      value = - value;
    }
  }
//
//  Product Peak.
//
  else if ( indx == 2 )
  {
    value = 1.0;

    for ( j = 0; j < ndim; j++ )
    {
      value = value * alpha[j] * ( 
          atan ( ( 1.0 - beta[j] ) * alpha[j] ) 
        + atan (       + beta[j]   * alpha[j] ) );
    }
  }
//
//  Corner Peak.
//
  else if ( indx == 3 )
  {
    value = 0.0;

    sgndm = 1.0;
    for ( j = 1; j <= ndim; j++ )
    {
      sgndm = - sgndm / ( double ) ( j );
    }

    rank = 0;
    ic = new int[ndim];

    for ( ; ; )
    {
      tuple_next ( 0, 1, ndim, &rank, ic );

      if ( rank == 0 )
      {
        break;
      }

      total = 1.0;

      for ( j = 0; j < ndim; j++ )
      {
        if ( ic[j] != 1 )
        {
          total = total + alpha[j];
        }
      }

      isum = i4vec_sum ( ndim, ic );

      s = 1 + 2 * ( ( isum / 2 ) * 2 - isum );
      value = value + ( double ) s / total;

    }

    delete [] ic;

    value = value * sgndm;
  }
//
//  Gaussian.
//
  else if ( indx == 4 )
  {
    value = 1.0;

    ab = sqrt ( 2.0 );
    for ( j = 0; j < ndim; j++ )
    {
      value = value * ( sqrt ( pi ) / alpha[j] ) * 
        (   genz_phi ( ( 1.0 - beta[j] ) * ab * alpha[j] ) 
          - genz_phi (       - beta[j]   * ab * alpha[j] ) );
    }
  }
//
//  C0 Function.
//
  else if ( indx == 5 )
  {
    value = 1.0;
    for ( j = 0; j < ndim; j++ )
    {
      ab = alpha[j] * beta[j];
      value = value * 
        ( 2.0 - exp ( - ab ) - exp ( ab - alpha[j] ) ) / alpha[j];
    }
  }
//
//  Discontinuous.
//
  else if ( indx == 6 )
  {
    value = 1.0;
    for ( j = 0; j < ndim; j++ )
    {
      value = value * ( exp ( alpha[j] * beta[j] ) - 1.0 ) / alpha[j];
    }
  }

  return value;
}
//****************************************************************************80

std::string genz_name (int index)

{
  std::string name;
  switch (index)
  {
    case 1: name = "Oscillatory"; break;
    case 2: name = "Product Peak"; break;
    case 3: name = "Corner Peak"; break;
    case 4: name = "Gaussian"; break;
    case 5: name = "C0 function"; break;
    case 6: name = "Discontinuous"; break;
    default: name = "Unknown function"; break;
  }
  return name;
}
//****************************************************************************80

double genz_phi ( double z )

//****************************************************************************80
//
//  Purpose:
//
//    GENZ_PHI estimates the normal cumulative density function.
//
//  Discussion:
//
//    The approximation is accurate to 1.0E-07.
//
//    This routine is based upon algorithm 5666 for the error function,
//    from Hart et al.
//
//  Modified:
//
//    20 March 2007
//
//  Author:
//
//    Original FORTRAN77 version by Alan Miller
//    C++ version by John Burkardt
//
//  Reference:
//
//    John Hart, Ward Cheney, Charles Lawson, Hans Maehly,
//    Charles Mesztenyi, John Rice, Henry Thatcher,
//    Christoph Witzgall,
//    Computer Approximations,
//    Wiley, 1968,
//    LC: QA297.C64.
//
//  Parameters:
//
//    Input, double Z, a value which can be regarded as the distance,
//    in standard deviations, from the mean.
//
//    Output, double GENZ_PHI, the integral of the normal PDF from negative
//    infinity to Z.
//
//  Local parameters:
//
//    Local, double ROOTPI, despite the name, is actually the 
//    square root of TWO * pi.
//
{
  double expntl;
  double p;
  const double p0 = 220.2068679123761;
  const double p1 = 221.2135961699311;
  const double p2 = 112.0792914978709;
  const double p3 = 33.91286607838300;
  const double p4 = 6.373962203531650;
  const double p5 = 0.7003830644436881;
  const double p6 = 0.03526249659989109;
  const double q0 = 440.4137358247522;
  const double q1 = 793.8265125199484;
  const double q2 = 637.3336333788311;
  const double q3 = 296.5642487796737;
  const double q4 = 86.78073220294608;
  const double q5 = 16.06417757920695;
  const double q6 = 1.755667163182642;
  const double q7 = 0.08838834764831844;
  const double rootpi = 2.506628274631001;
  double zabs;

  zabs = r8_abs ( z );
//
//  12 < |Z|.
//
  if ( 12.0 < zabs )
  {
    p = 0.0;
  }
  else
  {
//
//  |Z| <= 12
//
    expntl = exp ( - zabs * zabs / 2.0 );
//
//  |Z| < 7
//
    if ( zabs < 7.0 )
    {
      p = expntl * (((((( 
                  p6 
         * zabs + p5 ) 
         * zabs + p4 ) 
         * zabs + p3 ) 
         * zabs + p2 ) 
         * zabs + p1 ) 
         * zabs + p0 ) / ((((((( 
                  q7 
         * zabs + q6 ) 
         * zabs + q5 ) 
         * zabs + q4 ) 
         * zabs + q3 ) 
         * zabs + q2 ) 
         * zabs + q1 ) 
         * zabs + q0 );
    }
//
//  CUTOFF <= |Z|
//
    else
    {
      p = expntl / ( 
        zabs + 1.0 / (
        zabs + 2.0 / ( 
        zabs + 3.0 / ( 
        zabs + 4.0 / ( 
        zabs + 0.65 ))))) / rootpi;
    }
  }

  if ( 0.0 < z )
  {
    p = 1.0 - p;
  }

  return p;
}
//****************************************************************************80

double genz_random ( int *seed )

//****************************************************************************80
//
//  Purpose:
//
//    GENZ_RANDOM is a portable random number generator
//
//  Modified:
//
//    27 May 2007
//
//  Author:
//
//    Original FORTRAN77 version by Linus Schrage
//    C++ version by John Burkardt
//
//  Reference:
//
//    Linus Schrage,
//    A More Portable Fortran Random Number Generator,
//    ACM Transactions on Mathematical Software,
//    Volume 5, Number 2, June 1979, pages 132-138.
//
//  Parameters:
//
//    Input, integer/output, int *SEED, a seed for the random
//    number generator.
//
//    Output, double GENZ_RANDOM, a pseudorandom value.
//
{
  const int a = 16807;
  const int b15 = 32768;
  const int b16 = 65536;
  int fhi;
  int k;
  int leftlo;
  const int p = 2147483647;
  double value;
  int xalo;
  int xhi;

  xhi = *seed / b16;
  xalo = ( *seed - xhi * b16 ) * a;
  leftlo = xalo / b16;
  fhi = xhi * a + leftlo;
  k = fhi / b15;

  *seed = ( 
            ( 
              ( xalo - leftlo * b16 ) - p 
            ) 
          + ( fhi - k * b15 ) * b16 
          ) + k;

  if ( *seed < 0 )
  {
    *seed = *seed + p;
  }

  value = ( double ) ( *seed ) / ( double ) ( p );

  return value;
}
//****************************************************************************80

int i4_max ( int i1, int i2 )

//****************************************************************************80
//
//  Purpose:
//
//    I4_MAX returns the maximum of two I4's.
//
//  Modified:
//
//    13 October 1998
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int I1, I2, are two integers to be compared.
//
//    Output, int I4_MAX, the larger of I1 and I2.
//
{
  int value;

  if ( i2 < i1 )
  {
    value = i1;
  }
  else
  {
    value = i2;
  }
  return value;
}
//****************************************************************************80

int i4_min ( int i1, int i2 )

//****************************************************************************80
//
//  Purpose:
//
//    I4_MIN returns the minimum of two I4's.
//
//  Modified:
//
//    13 October 1998
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int I1, I2, two integers to be compared.
//
//    Output, int I4_MIN, the smaller of I1 and I2.
//
{
  int value;

  if ( i1 < i2 )
  {
    value = i1;
  }
  else
  {
    value = i2;
  }
  return value;
}
//****************************************************************************80

int i4_power ( int i, int j )

//****************************************************************************80
//
//  Purpose:
//
//    I4_POWER returns the value of I^J.
//
//  Modified:
//
//    01 April 2004
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int I, J, the base and the power.  J should be nonnegative.
//
//    Output, int I4_POWER, the value of I^J.
//
{
  int k;
  int value;

  if ( j < 0 )
  {
    if ( i == 1 )
    {
      value = 1;
    }
    else if ( i == 0 )
    {
      std::cout << "\n";
      std::cout << "I4_POWER - Fatal error!\n";
      std::cout << "  I^J requested, with I = 0 and J negative.\n";
      exit ( 1 );
    }
    else
    {
      value = 0;
    }
  }
  else if ( j == 0 )
  {
    if ( i == 0 )
    {
      std::cout << "\n";
      std::cout << "I4_POWER - Fatal error!\n";
      std::cout << "  I^J requested, with I = 0 and J = 0.\n";
      exit ( 1 );
    }
    else
    {
      value = 1;
    }
  }
  else if ( j == 1 )
  {
    value = i;
  }
  else
  {
    value = 1;
    for ( k = 1; k <= j; k++ )
    {
      value = value * i;
    }
  }
  return value;
}
//****************************************************************************80

int i4vec_sum ( int n, int a[] )

//****************************************************************************80
//
//  Purpose:
//
//    I4VEC_SUM sums the entries of an I4VEC.
//
//  Example:
//
//    Input:
//
//      A = ( 1, 2, 3, 4 )
//
//    Output:
//
//      I4VEC_SUM = 10
//
//  Modified:
//
//    26 May 1999
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int N, the number of entries in the vector.
//
//    Input, int A[N], the vector to be summed.
//
//    Output, int I4VEC_SUM, the sum of the entries of A.
//
{
  int i;
  int sum;

  sum = 0;
  for ( i = 0; i < n; i++ )
  {
    sum = sum + a[i];
  }

  return sum;
}

//****************************************************************************80

double r8_abs ( double x )

//****************************************************************************80
//
//  Purpose:
//
//    R8_ABS returns the absolute value of an R8.
//
//  Modified:
//
//    14 November 2006
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, double X, the quantity whose absolute value is desired.
//
//    Output, double R8_ABS, the absolute value of X.
//
{
  double value;

  if ( 0.0 <= x )
  {
    value = x;
  } 
  else
  {
    value = -x;
  }
  return value;
}
//****************************************************************************80

double r8_epsilon ( void )

//****************************************************************************80
//
//  Purpose:
//
//    R8_EPSILON returns the R8 roundoff unit.
//
//  Discussion:
//
//    The roundoff unit is a number R which is a power of 2 with the 
//    property that, to the precision of the computer's arithmetic,
//      1 < 1 + R
//    but 
//      1 = ( 1 + R / 2 )
//
//  Modified:
//
//    01 July 2004
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Output, double R8_EPSILON, the R8 round-off unit.
//
{
  double value;

  value = 1.0;

  while ( 1.0 < ( double ) ( 1.0 + value )  )
  {
    value = value / 2.0;
  }

  value = 2.0 * value;

  return value;
}
//****************************************************************************80

double r8_max ( double x, double y )

//****************************************************************************80
//
//  Purpose:
//
//    R8_MAX returns the maximum of two R8's.
//
//  Modified:
//
//    18 August 2004
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, double X, Y, the quantities to compare.
//
//    Output, double R8_MAX, the maximum of X and Y.
//
{
  double value;

  if ( y < x )
  {
    value = x;
  } 
  else
  {
    value = y;
  }
  return value;
}
//****************************************************************************80

double r8_min ( double x, double y )

//****************************************************************************80
//
//  Purpose:
//
//    R8_MIN returns the minimum of two R8's.
//
//  Modified:
//
//    31 August 2004
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, double X, Y, the quantities to compare.
//
//    Output, double R8_MIN, the minimum of X and Y.
//
{
  double value;

  if ( y < x )
  {
    value = y;
  } 
  else
  {
    value = x;
  }
  return value;
}
//****************************************************************************80

double r8vec_dot ( int n, double a1[], double a2[] )

//****************************************************************************80
//
//  Purpose:
//
//    R8VEC_DOT computes the dot product of a pair of R8VEC's.
//
//  Modified:
//
//    03 July 2005
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int N, the number of entries in the vectors.
//
//    Input, double A1[N], A2[N], the two vectors to be considered.
//
//    Output, double R8VEC_DOT, the dot product of the vectors.
//
{
  int i;
  double value;

  value = 0.0;
  for ( i = 0; i < n; i++ )
  {
    value = value + a1[i] * a2[i];
  }

  return value;
}
//****************************************************************************80

void r8vec_median ( int n, double r[], double rmed[3] )

//****************************************************************************80
//
//  Purpose:
//
//    R8VEC_MEDIAN computes the median of an R8VEC.
//
//  Modified:
//
//    20 March 2007
//
//  Author:
//
//    Original FORTRAN77 version by Alan Genz
//    C++ version by John Burkardt
//
//  Parameters:
//
//    Input, int N, the dimension of the array.
//
//    Input, double R[N], the array to be examined.
//
//    Output, double RMED[3].  RMED[0] contains the median,
//    RMED[1] and RMED[2] specify the confidence interval.
//
{
  int j;
  int k;
  int kmax;
  int nconf;
  int nd;
  double rmax;

  for ( j = 0; j < n; j++ )
  {
    kmax = j;

    for ( k = j + 1; k < n; k++ )
    {
      if ( r[kmax] < r[k] )
      {
        kmax = k;
      }
    }
    rmax = r[kmax];
    r[kmax] = r[j];
    r[j] = rmax;
  }

  nd = n / 2;

  if ( ( n % 2 ) == 0 )
  {
    rmed[0] = ( r[nd-1] + r[nd] ) / 2.0;
  }
  else
  {
    rmed[0] = r[nd];
  }

  nconf = i4_max ( 1, ( 2 * n ) / 5 - 2 );

  rmed[1] = r[n-nconf];
  rmed[2] = r[nconf-1];

  return;
}
//****************************************************************************80

double r8vec_product ( int n, double a[] )

//****************************************************************************80
//
//  Purpose:
//
//    R8VEC_PRODUCT returns the product of the entries of an R8VEC.
//
//  Modified:
//
//    17 September 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int N, the number of entries in the vector.
//
//    Input, double A[N], the vector.
//
//    Output, double R8VEC_PRODUCT, the product of the vector.
//
{
  int i;
  double product;

  product = 1.0;
  for ( i = 0; i < n; i++ )
  {
    product = product * a[i];
  }

  return product;
}
//****************************************************************************80

double r8vec_sum ( int n, double a[] )

//****************************************************************************80
//
//  Purpose:
//
//    R8VEC_SUM returns the sum of an R8VEC.
//
//  Modified:
//
//    15 October 2004
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int N, the number of entries in the vector.
//
//    Input, double A[N], the vector.
//
//    Output, double R8VEC_SUM, the sum of the vector.
//
{
  int i;
  double sum;

  sum = 0.0;
  for ( i = 0; i < n; i++ )
  {
    sum = sum + a[i];
  }

  return sum;
}

//****************************************************************************80

void tuple_next ( int m1, int m2, int n, int *rank, int x[] )

//****************************************************************************80
//
//  Purpose:
//
//    TUPLE_NEXT computes the next element of a tuple space.
//
//  Discussion:
//
//    The elements are N vectors.  Each entry is constrained to lie
//    between M1 and M2.  The elements are produced one at a time.
//    The first element is
//      (M1,M1,...,M1),
//    the second element is
//      (M1,M1,...,M1+1),
//    and the last element is
//      (M2,M2,...,M2)
//    Intermediate elements are produced in lexicographic order.
//
//  Example:
//
//    N = 2, M1 = 1, M2 = 3
//
//    INPUT        OUTPUT
//    -------      -------
//    Rank  X      Rank   X
//    ----  ---    -----  ---
//    0     * *    1      1 1
//    1     1 1    2      1 2
//    2     1 2    3      1 3
//    3     1 3    4      2 1
//    4     2 1    5      2 2
//    5     2 2    6      2 3
//    6     2 3    7      3 1
//    7     3 1    8      3 2
//    8     3 2    9      3 3
//    9     3 3    0      0 0
//
//  Modified:
//
//    29 April 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int M1, M2, the minimum and maximum entries.
//
//    Input, int N, the number of components.
//
//    Input/output, int *RANK, counts the elements.
//    On first call, set RANK to 0.  Thereafter, the output value of RANK
//    will indicate the order of the element returned.  When there are no
//    more elements, RANK will be returned as 0.
//
//    Input/output, int X[N], on input the previous tuple.
//    On output, the next tuple.
//
{
  int i;
  int j;

  if ( m2 < m1 )
  {
    *rank = 0;
    return;
  }

  if ( *rank <= 0 )
  {
    for ( i = 0; i < n; i++ )
    {
      x[i] = m1;
    }
    *rank = 1;
  }
  else
  {
    *rank = *rank + 1;
    i = n - 1;

    for ( ; ; )
    {

      if ( x[i] < m2 )
      {
        x[i] = x[i] + 1;
        break;
      }

      x[i] = m1;

      if ( i == 0 )
      {
        *rank = 0;
        for ( j = 0; j < n; j++ )
        {
          x[j] = m1;
        }
        break;
      }
      i = i - 1;
    }
  }
  return;
}

