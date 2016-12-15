#ifndef COMPLEXNUMBERHEADERDEF
#define COMPLEXNUMBERHEADERDEF

#include <iostream>
#include <vector>

class ComplexNumber
{
private:
	double mRealPart;

	double mImaginaryPart;
public:
	ComplexNumber();

	ComplexNumber(double x , double y = 0);

	//ComplexNumber(double x);

	ComplexNumber(const ComplexNumber &z);

	double CalculateModulus() const;

	double CalculateArgument() const;

	ComplexNumber CalculatePower(double n) const;

	ComplexNumber& operator=(const ComplexNumber& z);
	ComplexNumber& operator=(const double& x);

	ComplexNumber operator-() const;

	ComplexNumber operator+(const ComplexNumber& z) const;

	ComplexNumber& operator+=(const ComplexNumber& z);

	ComplexNumber operator-(const ComplexNumber& z) const;

	ComplexNumber operator*(const ComplexNumber& z) const;

	ComplexNumber operator*(const double& d);

	friend std::ostream& operator<<(std::ostream& output,
	const ComplexNumber& z);

	double GetRealPart() const;

	double GetImaginaryPart() const;

	ComplexNumber CalculateConjugate()const ;

	void SetConjugate();

	friend double GetRealPart(ComplexNumber z);

	friend double GetImaginaryPart(ComplexNumber z);

};

	ComplexNumber operator*(const double& d, const ComplexNumber& z);

	double GetRealPart(ComplexNumber z);

	double GetImaginaryPart(ComplexNumber z);

	std::vector<ComplexNumber> getRow(const std::vector<std::vector<ComplexNumber> >& arr, int i);

	std::vector<ComplexNumber> getColumn(const std::vector<std::vector<ComplexNumber> >& arr, int i);

	void setRow(std::vector<std::vector<ComplexNumber> >& arr, const std::vector<ComplexNumber>& row, int i);

	void setColumn(std::vector<std::vector<ComplexNumber> >& arr, const std::vector<ComplexNumber>& column, int i);

#endif
