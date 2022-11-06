CC=cc

nbtviewer:
	$(CC) nbtviewer.c -o nbtviewer.run -lz -Wall

install:
	cp nbtviewer.run /usr/local/bin

uninstall:
	rm /usr/local/bin/nbtviewer.run

clean:
	rm nbtviewer.run
