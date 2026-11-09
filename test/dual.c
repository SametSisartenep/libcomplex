#include <u.h>
#include <libc.h>
#include "../complex.h"

void
usage(void)
{
	fprint(2, "usage: %s r ε\n", argv0);
	exits("usage");
}

void
main(int argc, char *argv[])
{
	Dual z;

	COMPLEXfmtinstall();
	ARGBEGIN{
	default: usage();
	}ARGEND;
	if(argc != 2)
		usage();

	z.r = strtod(argv[0], nil);
	z.ε = strtod(argv[1], nil);
	print("z = %𝔻\nz² = %𝔻\nzz∗ = %𝔻\n", z, muldual(z, z), muldual(z, dualconj(z)));
	print("exp(z) = %𝔻\nlog(z) = %𝔻\n", dualexp(z), duallog(z));
	print("log(exp(z)) = %𝔻\nexp(log(z)) = %𝔻\n",
		duallog(dualexp(z)), dualexp(duallog(z)));
	exits(nil);
}
