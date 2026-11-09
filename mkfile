</$objtype/mkfile

LIB=libcomplex.a$O

OFILES=\
	complex.$O\
	split.$O\
	dual.$O\
	fmt.$O

HFILES=\
	complex.h

UPDATE=\
	mkfile\
	$HFILES\
	${OFILES:%.$O=%.c}

</sys/src/cmd/mklib
