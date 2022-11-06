#include <stdio.h>

extern void TAG_End(gzFile nbt, int16_t *ident){
	int16_t id = *ident;
	if(id>0){
		id--;
	}
	*ident = id;
	printf("TAG_END\n");
}
