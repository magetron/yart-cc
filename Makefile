CC = clang++
CFLAGS = -std=c++11 -O3

cover: coverscene.cc
	${CC} ${CFLAGS} coverscene.cc -o coverscene.out

cover-mb: coverscene-motionblur.cc
	${CC} ${CFLAGS} coverscene-motionblur.cc -o coverscene-motionblur.out

cover-mt: coverscene-mt.cc
	${CC} ${CFLAGS} coverscene-mt.cc -o coverscene-mt.out

cover-tx: coverscene-texture.cc
	${CC} ${CFLAGS} coverscene-texture.cc -o coverscene-texture.out

gen-cover:
	@make cover
	@./coverscene.out

gen-cover-mb:
	@make cover-mb
	@./coverscene-motionblur.out

gen-cover-mt:
	@make cover-mt
	@./coverscene-mt.out

gen-cover-tx:
	@make cover-tx
	@./coverscene-texture.out

clean:
	@rm -rf *.ppm
	@rm -rf *.out
	@rm -rf *.dSYM
