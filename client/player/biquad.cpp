#include "biquad.hpp"

namespace biquad {

	Biquad::Biquad(double a0, double a1, double a2,
				      double b0, double b1, double b2)
	{
		coeff_.a1 = a1/a0;
		coeff_.a2 = a2/a0;
		coeff_.b0 = b0/a0;
		coeff_.b1 = b1/a0;
		coeff_.b2 = b2/a0;
	}

	double Biquad::filter(double signal_in)
	{
		x3_ = x2_;
		x2_ = x1_;
		x1_ = signal_in;
		y3_ = y2_;
		y2_ = y1_; 

		y1_ = coeff_.b0 * x1_ + 
			coeff_.b1 * x2_ + 
			coeff_.b2 * x3_ + 
			coeff_.a1 * y2_ + 
			coeff_.a2 * y3_;

		return y1_;
	}
} // namespace biquad
