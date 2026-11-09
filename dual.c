#include <u.h>
#include <libc.h>
#include "complex.h"

Dual
𝔻(double r, double i)
{
	return (Dual){r, i};
}

Dual
adddual(Dual a, Dual b)
{
	return (Dual){a.r + b.r, a.ε + b.ε};
}

Dual
subdual(Dual a, Dual b)
{
	return (Dual){a.r - b.r, a.ε - b.ε};
}

Dual
muldual(Dual a, Dual b)
{
	return (Dual){a.r*b.r, a.r*b.ε + a.ε*b.r};
}

Dual
divdual(Dual a, Dual b)
{
	double d;

	d = 1.0/b.r;	/* √(bb∗⁻¹) */
	return (Dual){a.r*d, (a.ε*b.r - a.r*b.ε)*d*d};
}

Dual
dualconj(Dual z)
{
	return (Dual){z.r, -z.ε};
}

Dual
dualmod(Dual z)
{
	return (Dual){fabs(z.r), 0};
}

Dual
dualarg(Dual z)
{
	return (Dual){z.ε/z.r, 0};
}

Dual
dualexp(Dual z)
{
	double mod;

	mod = exp(z.r);
	return (Dual){mod, mod*z.ε};
}

Dual
duallog(Dual z)
{
	return (Dual){log(fabs(z.r)), z.ε/z.r};
}
