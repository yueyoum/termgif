
test: record.o wjpeg.o get_target_window.o
	gcc -o test record.o wjpeg.o get_target_window.o -L /opt/jpeg9/lib/ \
	-Wl,-Bstatic -ljpeg \
	-Wl,-Bdynamic -lX11


record.o: record.c wjpeg.h
	gcc -c record.c -Wall

get_target_window.o: get_target_window.c
	gcc -c get_target_window.c -Wall


wjpeg.o: wjpeg.c wjpeg.h
	gcc -c wjpeg.c -I /opt/jpeg9/include/ -Wall

.PHONY: clean
clean:
	-rm -f record.o wjpeg.o get_target_window.o test
