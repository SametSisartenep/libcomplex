#include <u.h>
#include <libc.h>
#include "complex.h"

int
ℂfmt(Fmt *f)
{
	Complex z;

	z = va_arg(f->args, Complex);
	return fmtprint(f, "%g + %gi", z.r, z.i);
}

int
ℍfmt(Fmt *f)
{
	Split z;

	z = va_arg(f->args, Split);
	return fmtprint(f, "%g + %gj", z.r, z.j);
}

int
𝔻fmt(Fmt *f)
{
	Dual z;

	z = va_arg(f->args, Dual);
	return fmtprint(f, "%g + %gε", z.r, z.ε);
}

void
COMPLEXfmtinstall(void)
{
	fmtinstall(L'ℂ', ℂfmt);
	fmtinstall(L'ℍ', ℍfmt);
	fmtinstall(L'𝔻', 𝔻fmt);
}
