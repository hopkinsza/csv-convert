csv-convert: csv-convert.c
	${CC} ${CFLAGS} -o $@ csv-convert.c
