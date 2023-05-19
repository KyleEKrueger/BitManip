PROGRAM = bitManip
CC = gcc
CFLAGS = -g3

${PROGRAM}:	${PROGRAM}.c
		${CC} ${PROGRAM}.c -o ${PROGRAM}

clean:
		rm -f ${PROGRAM}
