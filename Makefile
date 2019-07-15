CC = clang++
CFLAGS = -std=c++11 -O3

cover-tx: coverscene-texture.cc
	${CC} ${CFLAGS} coverscene-texture.cc -o coverscene-texture.out

gen-cover-tx:
	@make cover-tx
	@./coverscene-texture.out

clean:
	@rm -rf *.ppm
	@rm -rf *.out
	@rm -rf *.dSYM
