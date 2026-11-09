#include <u.h>
#include <libc.h>
#include "complex.h"

Complex
ℂ(double r, double i)
{
	return (Complex){r, i};
}

Complex
addcomplex(Complex a, Complex b)
{
	return (Complex){a.r + b.r, a.i + b.i};
}

Complex
subcomplex(Complex a, Complex b)
{
	return (Complex){a.r - b.r, a.i - b.i};
}

Complex
mulcomplex(Complex a, Complex b)
{
	return (Complex){a.r*b.r - a.i*b.i, a.r*b.i + a.i*b.r};
}

Complex
divcomplex(Complex a, Complex b)
{
	double d;

	d = 1.0/(b.r*b.r + b.i*b.i);	/* bb∗⁻¹ */
	return (Complex){(a.r*b.r + a.i*b.i)*d, (a.i*b.r - a.r*b.i)*d};
}

Complex
complexconj(Complex z)
{
	return (Complex){z.r, -z.i};
}

Complex
complexmod(Complex z)
{
	return (Complex){hypot(z.r, z.i), 0};
}

Complex
complexarg(Complex z)
{
	return (Complex){atan2(z.i, z.r), 0};
}

Complex
complexexp(Complex z)
{
	double mod;

	mod = exp(z.r);
	return (Complex){mod*cos(z.i), mod*sin(z.i)};
}

Complex
complexlog(Complex z)
{
	return (Complex){log(hypot(z.r, z.i)), atan2(z.i, z.r)};
}
