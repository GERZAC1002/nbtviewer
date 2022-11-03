nbtviewer:
	gcc nbtviewer.c -o nbtviewer.run -lz

install:
	cp nbtviewer.run /usr/local/bin

uninstall:
	rm /usr/local/bin/nbtviewer.run

clean:
	rm nbtviewer.run
