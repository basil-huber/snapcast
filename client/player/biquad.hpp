#ifndef BIQUAD_H
#define BIQUAD_H

namespace biquad 
{
struct Coefficients
{
	double a1;
	double a2;
	double b0;
	double b1;
	double b2;
};

class Biquad
{
public:
	/**
			 * Sets all coefficients
			 * \param a0 1st IIR coefficient
			 * \param a1 2nd IIR coefficient
			 * \param a2 3rd IIR coefficient
			 * \param b0 1st FIR coefficient
			 * \param b1 2nd FIR coefficient
			 * \param b2 3rd FIR coefficient
			 **/
	Biquad(double a0, double a1, double a2,
					double b0, double b1, double b2);
	double filter(double signal_in);
private:
	double x1_, x2_, x3_, y1_, y2_, y3_ = 0;

	Coefficients coeff_;
};
} // namepsace biquad
#endif
