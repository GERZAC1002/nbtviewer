#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SEPERATOR '\t'
//#define SEPERATOR ' '

void SwapBytes(void *pv, size_t n){
	char *p = pv;
	size_t lo, hi;
	for(lo=0, hi=n-1; hi>lo; lo++, hi--){
		char tmp=p[lo];
		p[lo] = p[hi];
		p[hi] = tmp;
	}
}
#define SWAP(x) SwapBytes(&x, sizeof(x));

void read_TAG(gzFile nbt, int8_t tag, int16_t *ident, int8_t named);

void TAG_End(gzFile nbt, int16_t *ident){
	int16_t id = *ident;
	if(id>0){
		id--;
	}
	*ident = id;
	//printf("TAG_END\n");
	printf("}\n");
}

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
			//printf("TAG_Compound(\"");
			printf("\"");
			for(int i = 0; i < sizeof(tagname); i++){
				putchar(tagname[i]);
			}
			printf("\"{\n");
			//printf("\")\n");
		}else{
			//printf("TAG_Compound(\"%s\"){\n",argv[1]);
			//printf("TAG_Compound(\"\"){\n");
			printf("\"\"{\n");
		}
	}else{
		int16_t id = *ident;
		id++;
		*ident = id;
		//printf("TAG_Compound(\"\"):\n");
		printf("\"\"{\n");
		int8_t tag;
		putchar(SEPERATOR);
		//fread(&tag,sizeof(tag),1,nbt);
		gzread(nbt,&tag,sizeof(tag));
		read_TAG(nbt,tag,ident,1);
	}
}

void TAG_Byte(gzFile nbt, int8_t named){
	if(named == 1){
		int16_t tag_name_length;
		//fread(&tag_name_length, sizeof(tag_name_length),1,nbt);
		gzread(nbt, &tag_name_length, sizeof(tag_name_length));
		SWAP(tag_name_length);
		if(tag_name_length > 0){
			char tagname[tag_name_length];
			int8_t value;
			//fread(&tagname,sizeof(tagname),1,nbt);
			gzread(nbt, &tagname, sizeof(tagname));
			printf("TAG_Byte(\"");
			for(int i = 0; i < sizeof(tagname); i++){
				putchar(tagname[i]);
			}
			//fread(&value,sizeof(value),1,nbt);
			gzread(nbt, &value, sizeof(value));
			printf("\"): %d\n",value);
		}else{
			printf("\n[ERROR]\tTAG_Byte has no name\n");
		}
	}else{
		int8_t value;
		//fread(&value,sizeof(value),1,nbt);
		gzread(nbt,&value,sizeof(value));
		printf("TAG_Byte(\"\"): %d\n",value);
	}
}

void TAG_Short(gzFile nbt, int8_t named){
	if(named == 1){
		int16_t tag_name_length;
		//fread(&tag_name_length, sizeof(tag_name_length),1,nbt);
		gzread(nbt, &tag_name_length, sizeof(tag_name_length));
		SWAP(tag_name_length);
		if(tag_name_length > 0){
			char tagname[tag_name_length];
			int16_t value;
			//fread(&tagname,sizeof(tagname),1,nbt);
			gzread(nbt, &tagname, sizeof(tagname));
			printf("TAG_Short(\"");
			for(int i = 0; i < sizeof(tagname); i++){
				putchar(tagname[i]);
			}
			//fread(&value,sizeof(value),1,nbt);
			gzread(nbt,&value,sizeof(value));
			SWAP(value);
			printf("\"): %d\n",value);
		}else{
			printf("\n[ERROR]\tTAG_Short has no name\n");
		}
	}else{
		int16_t value;
		//fread(&value,sizeof(value),1,nbt);
		gzread(nbt,&value,sizeof(value));
		SWAP(value);
		printf("TAG_Float(\"\"): %d\n",value);
	}
}

void TAG_Int(gzFile nbt, int8_t named){
	if(named == 1){
		int16_t tag_name_length;
		//fread(&tag_name_length, sizeof(tag_name_length),1,nbt);
		gzread(nbt, &tag_name_length, sizeof(tag_name_length));
		SWAP(tag_name_length);
		if(tag_name_length > 0){
			char tagname[tag_name_length];
			int32_t value;
			//fread(&tagname,sizeof(tagname),1,nbt);
			gzread(nbt, &tagname, sizeof(tagname));
			printf("TAG_Int(\"");
			for(int i = 0; i < sizeof(tagname); i++){
				putchar(tagname[i]);
			}
			//fread(&value,sizeof(value),1,nbt);
			gzread(nbt, &value, sizeof(value));
			SWAP(value);
			printf("\"): %d\n",value);
		}else{
			printf("\n[ERROR]\tTAG_Int has no name\n");
		}
	}else{
		int32_t value;
		//fread(&value,sizeof(value),1,nbt);
		gzread(nbt,&value,sizeof(value));
		SWAP(value);
		printf("TAG_Int(\"\"): %d\n",value);
	}
}

void TAG_Long(gzFile nbt, int8_t named){
	if(named == 1){
		int16_t tag_name_length;
		//fread(&tag_name_length, sizeof(tag_name_length),1,nbt);
		gzread(nbt, &tag_name_length, sizeof(tag_name_length));
		SWAP(tag_name_length);
		if(tag_name_length > 0){
			char tagname[tag_name_length];
			int64_t value;
			//fread(&tagname,sizeof(tagname),1,nbt);
			gzread(nbt, &tagname, sizeof(tagname));
			printf("TAG_Long(\"");
			for(int i = 0; i < sizeof(tagname); i++){
				putchar(tagname[i]);
			}
			//fread(&value,sizeof(value),1,nbt);
			gzread(nbt, &value, sizeof(value));
			SWAP(value);
			printf("\"): %ld\n",value);
		}else{
			printf("\n[ERROR]\tTAG_Long has no name\n");
		}
	}else{
		int64_t value;
		//fread(&value,sizeof(value),1,nbt);
		gzread(nbt, &value, sizeof(value));
		SWAP(value);
		printf("TAG_Long(\"\"): %ld\n",value);

	}
}

void TAG_Float(gzFile nbt, int8_t named){
	if(named == 1){
		int16_t tag_name_length;
		//fread(&tag_name_length, sizeof(tag_name_length),1,nbt);
		gzread(nbt, &tag_name_length, sizeof(tag_name_length));
		SWAP(tag_name_length);
		if(tag_name_length > 0){
			char tagname[tag_name_length];
			float value;
			//fread(&tagname,sizeof(tagname),1,nbt);
			gzread(nbt, &tagname, sizeof(tagname));
			printf("TAG_Float(\"");
			for(int i = 0; i < sizeof(tagname); i++){
				putchar(tagname[i]);
			}
			//fread(&value,sizeof(value),1,nbt);
			gzread(nbt, &value, sizeof(value));
			SWAP(value);
			printf("\"): %f\n",value);
		}else{
			printf("\n[ERROR]\tTAG_Float has no name\n");
		}
	}else{
		float value;
		//fread(&value,sizeof(value),1,nbt);
		gzread(nbt, &value, sizeof(value));
		SWAP(value);
		printf("TAG_Float(\"\"): %f\n",value);
	}
}

void TAG_Double(gzFile nbt, int8_t named){
	if(named == 1){
		int16_t tag_name_length;
		//fread(&tag_name_length, sizeof(tag_name_length),1,nbt);
		gzread(nbt, &tag_name_length, sizeof(tag_name_length));
		SWAP(tag_name_length);
		if(tag_name_length > 0){
			char tagname[tag_name_length];
			double value;
			//fread(&tagname,sizeof(tagname),1,nbt);
			gzread(nbt, &tagname, sizeof(tagname));
			printf("TAG_Double(\"");
			for(int i = 0; i < sizeof(tagname); i++){
				putchar(tagname[i]);
			}
			//fread(&value,sizeof(value),1,nbt);
			gzread(nbt, &value, sizeof(value));
			SWAP(value);
			printf("\"): %lf\n",value);
		}else{
			printf("\n[ERROR]\tTAG_Double has no name\n");
		}
	}else{
		double value;
		//fread(&value,sizeof(value),1,nbt);
		gzread(nbt, &value, sizeof(value));
		SWAP(value);
		printf("TAG_Double:(\"\"): %lf\n",value);
	}
}

void TAG_Byte_Array(gzFile nbt){
	int16_t tag_name_length;
	//fread(&tag_name_length, sizeof(tag_name_length),1,nbt);
	gzread(nbt, &tag_name_length, sizeof(tag_name_length));
	SWAP(tag_name_length);
	if(tag_name_length > 0){
		char tagname[tag_name_length];
		double value;
		//fread(&tagname,sizeof(tagname),1,nbt);
		gzread(nbt, &tagname, sizeof(tagname));
		printf("TAG_Byte_Array(\"");
		for(int i = 0; i < sizeof(tagname); i++){
			putchar(tagname[i]);
		}
		//fread(&value,sizeof(value),1,nbt);
		gzread(nbt, &value, sizeof(value));
		SWAP(value);
		printf("\"): %lf\n",value);
	}else{
		printf("\n[ERROR]\tTAG_Byte_Array has no name\n");
	}
}

void TAG_String(gzFile nbt,int8_t named){
	if(named == 1){
		int16_t tag_name_length;
		//fread(&tag_name_length, sizeof(tag_name_length),1,nbt);
		gzread(nbt, &tag_name_length, sizeof(tag_name_length));
		SWAP(tag_name_length);
		if(tag_name_length > 0){
			char tagname[tag_name_length];
			int16_t length;
			//fread(&tagname,sizeof(tagname),1,nbt);
			gzread(nbt, &tagname, sizeof(tagname));
			printf("TAG_String(\"");
			for(int i = 0; i < sizeof(tagname); i++){
				putchar(tagname[i]);
			}
			printf("\"):");
			//fread(&length, sizeof(length),1,nbt);
			gzread(nbt, &length, sizeof(length));
			SWAP(length);
			char string[length];
			//fread(&string, sizeof(string),1,nbt);
			gzread(nbt, &string, sizeof(string));
			for(int i = 0; i < sizeof(string); i++){
				putchar(string[i]);
			}
			printf("\n");
		}else{
			printf("\n[ERROR]\tTAG_String has no name\n");
		}
	}else{
		int16_t length;
		printf("TAG_String(\"\"):");
		//fread(&length, sizeof(length),1,nbt);
		gzread(nbt, &length, sizeof(length));
		SWAP(length);
		char string[length];
		//fread(&string, sizeof(string),1,nbt);
		gzread(nbt, &string, sizeof(string));
		for(int i = 0; i < sizeof(string); i++){
			putchar(string[i]);
		}
		printf("\n");
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
		printf("TAG_List(\"");
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
		printf("\n[ERROR]\tTAG_List has no name\n");
	}
}

void TAG_Int_Array(gzFile nbt, int16_t *ident){
	int16_t tag_name_length;
	//fread(&tag_name_length, sizeof(tag_name_length),1,nbt);
	gzread(nbt, &tag_name_length, sizeof(tag_name_length));
	SWAP(tag_name_length);
	if(tag_name_length > 0){
		char tagname[tag_name_length];
		int32_t value;
		int32_t array_length;
		//fread(&tagname,sizeof(tagname),1,nbt);
		gzread(nbt, &tagname, sizeof(tagname));
		printf("TAG_Int_Array(\"");
		for(int i = 0; i < sizeof(tagname); i++){
			putchar(tagname[i]);
		}
		printf("\")\n");
		//fread(&array_length,sizeof(array_length),1,nbt);
		gzread(nbt, &array_length, sizeof(array_length));
		SWAP(array_length);
		for(int32_t i = 0; i < array_length; i++){
			putchar(SEPERATOR);
			for(int16_t i = 0; i < *ident; i++){
				putchar(SEPERATOR);
			}
			TAG_Int(nbt,0);
		}
	}else{
		printf("\n[ERROR]\tTAG_Int_Array has no name\n");
	}
}

void TAG_Long_Array(gzFile nbt){
	int16_t tag_name_length;
	//fread(&tag_name_length, sizeof(tag_name_length),1,nbt);
	gzread(nbt, &tag_name_length, sizeof(tag_name_length));
	SWAP(tag_name_length);
	if(tag_name_length > 0){
		char tagname[tag_name_length];
		int64_t value;
		int32_t array_length;
		//fread(&tagname,sizeof(tagname),1,nbt);
		gzread(nbt, &tagname, sizeof(tagname));
		printf("TAG_Int_Array(\"");
		for(int i = 0; i < sizeof(tagname); i++){
			putchar(tagname[i]);
		}
		printf("\")\n");
		//fread(&array_length,sizeof(array_length),1,nbt);
		gzread(nbt, &array_length, sizeof(array_length));
		SWAP(array_length);
		for(int32_t i = 0; i < array_length; i++){
			putchar(SEPERATOR);
			TAG_Long(nbt,0);
		}
	}else{
		printf("\n[ERROR]\tTAG_Int_Array has no name\n");
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
		TAG_Byte_Array(nbt);
	}else if(tag == 0x08){
		TAG_String(nbt, named);
	}else if(tag == 0x09){
		TAG_List(nbt, ident);
	}else if(tag == 0x0A){
		TAG_Compound(nbt, ident, named);
	}else if(tag == 0x0B){
		TAG_Int_Array(nbt, ident);
	}else if(tag == 0x0C){
		TAG_Long_Array(nbt);
	}else{
		return;
	}
}

