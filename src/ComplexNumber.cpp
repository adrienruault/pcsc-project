#include "ComplexNumber.hpp"
#include <cmath>

// Override default constructor
// Set real and imaginary parts to zero
ComplexNumber::ComplexNumber()
{
   mRealPart = 0.0;
   mImaginaryPart = 0.0;
}

// Constructor that sets complex number z=x+iy
ComplexNumber::ComplexNumber(double x, double y)
{
   mRealPart = x;
   mImaginaryPart = y;
}

/*ComplexNumber::ComplexNumber(double x)
	:mRealPart(x), mImaginaryPart(0)
{}*/

ComplexNumber::ComplexNumber(const ComplexNumber &z)
	:mRealPart(z.mRealPart), mImaginaryPart(z.mImaginaryPart)
{}

// Method for computing the modulus of a
// complex number
double ComplexNumber::CalculateModulus() const
{
   return sqrt(mRealPart*mRealPart+
               mImaginaryPart*mImaginaryPart);
}

// Method for computing the argument of a
// complex number
double ComplexNumber::CalculateArgument() const
{
   return atan2(mImaginaryPart, mRealPart);
}

// Method for raising complex number to the power n
// using De Moivre's theorem - first complex
// number must be converted to polar form
ComplexNumber ComplexNumber::CalculatePower(double n) const
{
   double modulus = CalculateModulus();
   double argument = CalculateArgument();
   double mod_of_result = pow(modulus, n);
   double arg_of_result = argument*n;
   double real_part = mod_of_result*cos(arg_of_result);
   double imag_part = mod_of_result*sin(arg_of_result);
   ComplexNumber z(real_part, imag_part);
   return z;
}

// Overloading the = (assignment) operator
ComplexNumber& ComplexNumber::operator=(const ComplexNumber& z)
{
   mRealPart = z.mRealPart;
   mImaginaryPart = z.mImaginaryPart;
   return *this;
}

// Overloading the unary - operator
ComplexNumber ComplexNumber::operator-() const
{
   ComplexNumber w;
   w.mRealPart = -mRealPart;
   w.mImaginaryPart = -mImaginaryPart;
   return w;
}

// Overloading the binary + operator
ComplexNumber ComplexNumber::
              operator+(const ComplexNumber& z) const
{
   ComplexNumber w;
   w.mRealPart = mRealPart + z.mRealPart;
   w.mImaginaryPart = mImaginaryPart + z.mImaginaryPart;
   return w;
}

ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& z)
{
  *this = *this + z;
  return *this;
}

// Overloading of operator* for the multiplication of 2 complex numbers
ComplexNumber ComplexNumber::operator*(const ComplexNumber& z) const
{
	double x = mRealPart*z.mRealPart - mImaginaryPart*z.mImaginaryPart;
	double y = mRealPart*z.mImaginaryPart + z.mRealPart*mImaginaryPart;
	return ComplexNumber(x,y);
}

// Overloading of operator* for the multiplication of a complex number and a double
ComplexNumber ComplexNumber::operator*(const double& d)
{
  return ComplexNumber(d)*(*this);
}

// Allow the double complex multiplication in the other direction
ComplexNumber operator*(const double& d, const ComplexNumber& z)
{
  return z*d;
}


// Overloading the binary - operator
ComplexNumber ComplexNumber::
              operator-(const ComplexNumber& z) const
{
   ComplexNumber w;
   w.mRealPart = mRealPart - z.mRealPart;
   w.mImaginaryPart = mImaginaryPart - z.mImaginaryPart;
   return w;
}

// Overloading the insertion << operator
std::ostream& operator<<(std::ostream& output,
                         const ComplexNumber& z)
{
   // Format as "(a + bi)" or as "(a - bi)"
   output << "(" << z.mRealPart << " ";
   if (z.mImaginaryPart >= 0.0)
   {
      output << "+ " << z.mImaginaryPart << "i)";
   }
   else
   {
      // z.mImaginaryPart < 0.0
      // Replace + with minus sign
      output << "- " << -z.mImaginaryPart << "i)";
   }

   return output;
}
//Code from Chapter06.tex line 779 save as ComplexNumber.cpp

double ComplexNumber::GetRealPart() const
{
	return mRealPart;
}

double ComplexNumber::GetImaginaryPart() const
{
	return mImaginaryPart;
}

double GetRealPart(ComplexNumber z)
{
	return z.mRealPart;
}

double GetImaginaryPart(ComplexNumber z)
{
	return z.mImaginaryPart;
}

ComplexNumber ComplexNumber::CalculateConjugate() const
{
	ComplexNumber z(mRealPart, -mImaginaryPart);
	return z;
}

void ComplexNumber::SetConjugate()
{
	mImaginaryPart = -mImaginaryPart;
}


std::vector<ComplexNumber> getRow(const std::vector<std::vector<ComplexNumber> >& arr, int i)
{
  std::vector<ComplexNumber> row(arr.size());
  for (size_t x = 0; x < arr.size() ; x++) {
    row[x] = arr[x][i];
  }
  return row;
}

std::vector<ComplexNumber> getColumn(const std::vector<std::vector<ComplexNumber> >& arr, int i)
{
  return arr[i];
}

void setRow(std::vector<std::vector<ComplexNumber> >& arr, const std::vector<ComplexNumber>& row, int i)
{
  for (size_t x = 0; x < row.size(); x++) {
    arr[x][i] = row[x];
  }
}

void setColumn(std::vector<std::vector<ComplexNumber> >& arr, const std::vector<ComplexNumber>& column, int i)
{
  arr[i] = column;
}
