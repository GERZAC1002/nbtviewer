#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SEPERATOR '\t'

#include "nbt/byte_swap.h"
#include "nbt/end.h"
#include "nbt/byte.h"
#include "nbt/short.h"
#include "nbt/int.h"
#include "nbt/long.h"
#include "nbt/float.h"
#include "nbt/double.h"
#include "nbt/string.h"
#include "nbt/int_array.h"
#include "nbt/long_array.h"
#include "nbt/byte_array.h"

void read_TAG(gzFile nbt, int8_t tag, int16_t *ident, int8_t named);

void TAG_Compound(gzFile nbt,int16_t *ident, int8_t named){
	if(named == 1){
		int16_t id = *ident;
		id++;
		*ident = id;
		int16_t tag_name_length;
		//fread(&tag_name_length, sizeof(tag_name_length),1,nbt);
		gzread(nbt, &tag_name_length, sizeof(tag_name_length));
		SWAP(tag_name_length);
		if(tag_name_length > 0){
			char tagname[tag_name_length];
			//fread(&tagname,sizeof(tagname),1,nbt);
			gzread(nbt,&tagname,sizeof(tagname));
			printf("TAG_COMPOUND(\"");
			//printf("\"");
			for(int i = 0; i < sizeof(tagname); i++){
				putchar(tagname[i]);
			}
			//printf("\"{\n");
			printf("\"):\n");
		}else{
			//printf("TAG_Compound(\"%s\"){\n",argv[1]);
			printf("TAG_COMPOUND(\"\"):\n");
			//printf("\"\"{\n");
		}
	}else{
		int16_t id = *ident;
		id++;
		*ident = id;
		printf("TAG_COMPOUND(\"\"):\n");
		//printf("\"\"{\n");
		int8_t tag;
		putchar(SEPERATOR);
		//fread(&tag,sizeof(tag),1,nbt);
		gzread(nbt,&tag,sizeof(tag));
		while(tag != 0){
			read_TAG(nbt,tag,ident,1);
			gzread(nbt,&tag,sizeof(tag));
			putchar(SEPERATOR);
		}
		read_TAG(nbt,tag,ident,1);
	}
}

void TAG_List(gzFile nbt,int16_t *ident){
	int16_t tag_name_length;
	//fread(&tag_name_length, sizeof(tag_name_length),1,nbt);
	gzread(nbt, &tag_name_length, sizeof(tag_name_length));
	SWAP(tag_name_length);
	if(tag_name_length > 0){
		char tagname[tag_name_length];
		int32_t list_length;
		int8_t list_type;
		//fread(&tagname,sizeof(tagname),1,nbt);
		gzread(nbt, &tagname, sizeof(tagname));
		printf("TAG_LIST(\"");
		for(int i = 0; i < sizeof(tagname); i++){
			putchar(tagname[i]);
		}
		printf("\"):");
		//fread(&list_type,sizeof(list_type),1,nbt);
		gzread(nbt, &list_type, sizeof(list_type));
		printf("List Type: %02x:",list_type);
		//fread(&list_length,sizeof(list_length),1,nbt);
		gzread(nbt, &list_length, sizeof(list_length));
		SWAP(list_length);
		printf("List Length: %d\n",list_length);
		for(int32_t i = 0; i < list_length; i++){
			putchar(SEPERATOR);
			read_TAG(nbt,list_type,ident,0);
		}
	}else{
		printf("\n[ERROR]\tTAG_LIST has no name\n");
	}
}

void read_TAG(gzFile nbt,int8_t tag,int16_t *ident,int8_t named){
	if(tag == 0x00){
		for(int16_t i = 0; i < *ident-1; i++){
			putchar(SEPERATOR);
		}
		TAG_End(nbt, ident);
		return;
	}
	for(int16_t i = 0; i < *ident; i++){
		putchar(SEPERATOR);
	}

	if(tag == 0x01){
		TAG_Byte(nbt, named);
	}else if(tag == 0x02){
		TAG_Short(nbt, named);
	}else if(tag == 0x03){
		TAG_Int(nbt, named);
	}else if(tag == 0x04){
		TAG_Long(nbt, named);
	}else if(tag == 0x05){
		TAG_Float(nbt, named);
	}else if(tag == 0x06){
		TAG_Double(nbt, named);
	}else if(tag == 0x07){
		TAG_Byte_Array(nbt, ident);
	}else if(tag == 0x08){
		TAG_String(nbt, named);
	}else if(tag == 0x09){
		TAG_List(nbt, ident);
	}else if(tag == 0x0A){
		TAG_Compound(nbt, ident, named);
	}else if(tag == 0x0B){
		TAG_Int_Array(nbt, ident);
	}else if(tag == 0x0C){
		TAG_Long_Array(nbt, ident);
	}else{
		return;
	}
}

