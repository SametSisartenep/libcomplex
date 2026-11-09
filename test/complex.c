#include <u.h>
#include <libc.h>
#include "../complex.h"

void
usage(void)
{
	fprint(2, "usage: %s r i\n", argv0);
	exits("usage");
}

void
main(int argc, char *argv[])
{
	Complex z;

	COMPLEXfmtinstall();
	ARGBEGIN{
	default: usage();
	}ARGEND;
	if(argc != 2)
		usage();

	z.r = strtod(argv[0], nil);
	z.i = strtod(argv[1], nil);
	print("z = %ℂ\nz² = %ℂ\nzz∗ = %ℂ\n", z, mulcomplex(z, z), mulcomplex(z, complexconj(z)));
	print("exp(z) = %ℂ\nlog(z) = %ℂ\n", complexexp(z), complexlog(z));
	print("log(exp(z)) = %ℂ\nexp(log(z)) = %ℂ\n",
		complexlog(complexexp(z)), complexexp(complexlog(z)));
	exits(nil);
}
