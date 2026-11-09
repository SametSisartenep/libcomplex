#include <u.h>
#include <libc.h>
#include "../complex.h"

void
usage(void)
{
	fprint(2, "usage: %s r j\n", argv0);
	exits("usage");
}

void
main(int argc, char *argv[])
{
	Split z;

	COMPLEXfmtinstall();
	ARGBEGIN{
	default: usage();
	}ARGEND;
	if(argc != 2)
		usage();

	z.r = strtod(argv[0], nil);
	z.j = strtod(argv[1], nil);
	print("z = %ℍ\nz² = %ℍ\nzz∗ = %ℍ\n", z, mulsplit(z, z), mulsplit(z, splitconj(z)));
	print("exp(z) = %ℍ\nlog(z) = %ℍ\n", splitexp(z), splitlog(z));
	print("log(exp(z)) = %ℍ\nexp(log(z)) = %ℍ\n",
		splitlog(splitexp(z)), splitexp(splitlog(z)));
	exits(nil);
}
