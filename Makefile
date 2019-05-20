CC = clang++
CFLAGS = -O3

coverscene: coverscene.cc
	${CC} ${CFLAGS} coverscene.cc -o coverscene.out

generate:
	@./coverscene.out

clean:
	@rm -rf *.ppm
	@rm -rf *.out
