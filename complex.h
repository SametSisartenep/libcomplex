typedef struct Complex	Complex;
typedef struct Split	Split;
typedef struct Dual	Dual;

struct Complex {
	double r, i;
};

struct Split {
	double r, j;
};

struct Dual {
	double r, ε;
};

Complex		ℂ(double, double);
Complex		addcomplex(Complex, Complex);
Complex		subcomplex(Complex, Complex);
Complex		mulcomplex(Complex, Complex);
Complex		divcomplex(Complex, Complex);
Complex		complexconj(Complex);
Complex		complexmod(Complex);
Complex		complexarg(Complex);
Complex		complexexp(Complex);
Complex		complexlog(Complex);

Split		ℂ´(double, double);
Split		addsplit(Split, Split);
Split		subsplit(Split, Split);
Split		mulsplit(Split, Split);
Split		divsplit(Split, Split);
Split		splitconj(Split);
Split		splitmod(Split);
Split		splitarg(Split);
Split		splitexp(Split);
Split		splitlog(Split);

Dual		𝔻(double, double);
Dual		adddual(Dual, Dual);
Dual		subdual(Dual, Dual);
Dual		muldual(Dual, Dual);
Dual		divdual(Dual, Dual);
Dual		dualconj(Dual);
Dual		dualmod(Dual);
Dual		dualarg(Dual);
Dual		dualexp(Dual);
Dual		duallog(Dual);

#pragma varargck type "ℂ" Complex
#pragma varargck type "ℍ" Split		/* it collides with the quaternions but i can't think of a better letter */
#pragma varargck type "𝔻" Dual
int		ℂfmt(Fmt*);
int		ℍfmt(Fmt*);
int		𝔻fmt(Fmt*);
void		COMPLEXfmtinstall(void);
