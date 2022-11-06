#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <zlib.h>
#include "nbt.h"

int main(int argc, char* argv[]){
	gzFile nbt;
	uint8_t c;
	int16_t ident = 0;

	if((nbt = gzopen(argv[1],"r")) == NULL){
		printf("[ERROR]\tunable to open input file\n");
		return 1;
	}

	while((c = gzgetc(nbt)) != 255){
		read_TAG(nbt,c, &ident,1);
	}
	gzclose(nbt);
	return 0;
}
