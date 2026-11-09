#include <u.h>
#include <libc.h>
#include "complex.h"

static double
atan2h(double y, double x)
{
	assert(x >= 0? x > y : x < y);	/* avoid a negative log argument and division by zero */
	return 0.5*log((x+y)/(x-y));
}

Split
ℂ´(double r, double j)
{
	return (Split){r, j};
}

Split
addsplit(Split a, Split b)
{
	return (Split){a.r + b.r, a.j + b.j};
}

Split
subsplit(Split a, Split b)
{
	return (Split){a.r - b.r, a.j - b.j};
}

Split
mulsplit(Split a, Split b)
{
	return (Split){a.r*b.r + a.j*b.j, a.r*b.j + a.j*b.r};
}

Split
divsplit(Split a, Split b)
{
	double d;

	d = 1.0/(b.r*b.r - b.j*b.j);	/* bb∗⁻¹ */
	return (Split){(a.r*b.r - a.j*b.j)*d, (a.j*b.r - a.r*b.j)*d};
}

Split
splitconj(Split z)
{
	return (Split){z.r, -z.j};
}

Split
splitmod(Split z)
{
	return (Split){sqrt(z.r*z.r - z.j*z.j), 0};
}

Split
splitarg(Split z)
{
	return (Split){atan2h(z.j, z.r), 0};
}

Split
splitexp(Split z)
{
	double mod;

	mod = exp(z.r);
	return (Split){mod*cosh(z.j), mod*sinh(z.j)};
}

Split
splitlog(Split z)
{
	return (Split){log(sqrt(z.r*z.r - z.j*z.j)), atan2h(z.j, z.r)};
}
