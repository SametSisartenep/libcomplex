#include <u.h>
#include <libc.h>
#include <thread.h>
#include <draw.h>
#include <mouse.h>
#include <keyboard.h>
#include "../complex.h"

#define TAU	(PI+PI)

Point	⊕;

void *
erealloc(void *p, ulong newsize)
{
	void *np;

	np = realloc(p, newsize);
	if(np == nil)
		sysfatal("erealloc: %r");
	if(p == nil)
		setmalloctag(np, getcallerpc(&p));
	else
		setrealloctag(np, getcallerpc(&p));
	return np;
}

static int
round(double n)
{
	return n < 0? n-0.5: n+0.5;
}

Point
C2P(Complex c)
{
	return (Point){round(c.r), round(c.i)};
}

/*
 * based on the spiral from MIT 18.03 Supplementary Notes on the
 * Complex Exponential § 6.6, Fig. 3
 */
void
drawspiral(Image *dst, double Δt)
{
	Complex c;
	double t;
	Point *p;
	int np;

	p = nil;
	np = 0;
	t = 0;
	c = ℂ(1, TAU);
	do{
		if(np % 16 == 0)
			p = erealloc(p, (np + 16)*sizeof(Point));
		p[np++] = addpt(⊕, C2P(complexexp(mulcomplex(c, ℂ(t, 0)))));
		t += Δt;
	}while(ptinrect(p[np-1], screen->r));
	poly(dst, p, np, Enddisc, Enddisc, 0, display->black, ZP);
	free(p);
}

void
redraw(void)
{
	draw(screen, screen->r, display->white, nil, ZP);
	drawspiral(screen, 1e-3);
	flushimage(display, 1);
}

void
mouse(Mousectl *mc)
{
	static char *menutab[] = {
		"exit",
		nil
	};
	static Menu menu = { .item = menutab };

	if(mc->buttons != 4)
		return;
	if(menuhit(3, mc, &menu, nil) == 0)
		threadexitsall(nil);
}

void
resize(void)
{
	if(getwindow(display, Refnone) < 0)
		sysfatal("getwindow: %r");
	⊕ = divpt(addpt(screen->r.min, screen->r.max), 2);
	redraw();
}

void
keybd(Rune r)
{
	if(r == Kdel || r == 'q')
		threadexitsall(nil);
}

void
usage(void)
{
	fprint(2, "usage: %s\n", argv0);
	exits("usage");
}

void
threadmain(int argc, char *argv[])
{
	Mousectl *mc;
	Keyboardctl *kc;
	Rune r;

	ARGBEGIN{
	default: usage();
	}ARGEND;

	if(initdraw(nil, nil, "spiral") < 0)
		sysfatal("initdraw: %r");
	if((mc = initmouse(nil, screen)) == nil)
		sysfatal("initmouse: %r");
	if((kc = initkeyboard(nil)) == nil)
		sysfatal("initkeyboard: %r");
	⊕ = divpt(addpt(screen->r.min, screen->r.max), 2);
	redraw();

	enum { MOUSE, RESIZ, KEYBD };
	Alt a[] = {
	 [MOUSE]	{ mc->c,	&mc->Mouse,	CHANRCV },
	 [RESIZ]	{ mc->resizec,	nil,		CHANRCV },
	 [KEYBD]	{ kc->c,	&r,		CHANRCV },
			{ nil,		nil,		CHANEND },
	};
	for(;;) switch(alt(a)){
	case MOUSE:
		mouse(mc);
		break;
	case RESIZ:
		resize();
		break;
	case KEYBD:
		keybd(r);
		break;
	default:
		sysfatal("alt: %r");
	}
}
