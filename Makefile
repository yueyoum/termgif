
test: record.o wjpeg.o
	gcc -o test record.o wjpeg.o -L /opt/jpeg9/lib/ \
	-Wl,-rpath,/opt/jpeg9/lib/ \
	-lX11 -ljpeg


record.o: record.c wjpeg.h
	gcc -c record.c -Wall

wjpeg.o: wjpeg.c wjpeg.h
	gcc -c wjpeg.c -I /opt/jpeg9/include/ -Wall

.PHONY: clean
clean:
	-rm -f record.o wjpeg.o test
