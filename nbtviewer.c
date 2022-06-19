#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

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


int main(int argc, char* argv[]){

	int32_t header;
	FILE *uncompressednbt;
	uint8_t c;
	int ident = 0;

	if((uncompressednbt = fopen(argv[1],"r")) == NULL){
		printf("[ERROR]\tunable to open input file\n");
		return 1;
	}

	/*
	if(fread(&header,sizeof(header),1,uncompressednbt) == 1){
		printf("%08x\n", header);
	}*/

	while((c = getc(uncompressednbt)) != 255){

		for(int i =0; i < ident;i++){
			printf("\t");
		}

		if(c == 0x00){
			ident--;
			printf("\r");
			for(int i = 0; i < ident; i++){
				printf("\t");
			}
			printf("TAG_END\n");
			continue;
		}

		if(c == 0x0A){
			c = getc(uncompressednbt);
			if(c != 0){
				printf("\nError, after Tag_Compound\n");
			}
			c = getc(uncompressednbt);
			if(c > 0){
				char tagname[c];
				fread(&tagname,sizeof(tagname),1,uncompressednbt);
				printf("TAG_Compound(\"");
				for(int i = 0; i < sizeof(tagname); i++){
					putchar(tagname[i]);
				}
				printf("\"){\n");
			}else{
				printf("TAG_Compound(\"%s\"){\n",argv[1]);
			}
			ident++;
			continue;
		}

		if(c == 0x01){
			c = getc(uncompressednbt);
			if(c != 0){
				printf("\n[Error]\tafter TAG_Byte\n");
			}
			c = getc(uncompressednbt);
			if(c > 0){
				char tagname[c];
				int8_t value;
				fread(&tagname,sizeof(tagname),1,uncompressednbt);
				printf("TAG_Byte(\"");
				for(int i = 0; i < sizeof(tagname); i++){
					putchar(tagname[i]);
				}
				fread(&value,sizeof(value),1,uncompressednbt);
				printf("\"):%d\n",value);
			}else{
				printf("\n[ERROR]\tTAG_Byte has no name\n");
			}
			continue;
		}

		if(c == 0x02){
			c = getc(uncompressednbt);
			if(c != 0){
				printf("\n[Error]\tafter TAG_Short\n");
			}
			c = getc(uncompressednbt);
			if(c > 0){
				char tagname[c];
				int16_t value;
				fread(&tagname,sizeof(tagname),1,uncompressednbt);
				printf("TAG_Int(\"");
				for(int i = 0; i < sizeof(tagname); i++){
					putchar(tagname[i]);
				}
				fread(&value,sizeof(value),1,uncompressednbt);
				__bswap_16(value);
				printf("\"):%d\n",value);
			}else{
				printf("\n[ERROR]\tTAG_Short has no name\n");
			}
			continue;
		}

		if(c == 0x03){
			c = getc(uncompressednbt);
			if(c != 0){
				printf("\n[Error]\tafter TAG_Int\n");
			}
			c = getc(uncompressednbt);
			if(c > 0){
				char tagname[c];
				int32_t value;
				fread(&tagname,sizeof(tagname),1,uncompressednbt);
				printf("TAG_Int(\"");
				for(int i = 0; i < sizeof(tagname); i++){
					putchar(tagname[i]);
				}
				fread(&value,sizeof(value),1,uncompressednbt);
				SWAP(value);
				printf("\"):%d\n",value);
			}else{
				printf("\n[ERROR]\tTAG_Int has no name\n");
			}
			continue;
		}

		if(c == 0x04){
			c = getc(uncompressednbt);
			if(c != 0){
				printf("\n[Error]\tafter TAG_Long\n");
			}
			c = getc(uncompressednbt);
			if(c > 0){
				char tagname[c];
				int64_t value;
				fread(&tagname,sizeof(tagname),1,uncompressednbt);
				printf("TAG_Long(\"");
				for(int i = 0; i < sizeof(tagname); i++){
					putchar(tagname[i]);
				}
				fread(&value,sizeof(value),1,uncompressednbt);
				SWAP(value);
				printf("\"):%ld\n",value);
			}else{
				printf("\n[ERROR]\tTAG_Long has no name\n");
			}
			continue;
		}

		if(c == 0x05){
			c = getc(uncompressednbt);
			if(c != 0){
				printf("\n[Error]\tafter TAG_Float\n");
			}
			c = getc(uncompressednbt);
			if(c > 0){
				char tagname[c];
				float value;
				fread(&tagname,sizeof(tagname),1,uncompressednbt);
				printf("TAG_Float(\"");
				for(int i = 0; i < sizeof(tagname); i++){
					putchar(tagname[i]);
				}
				fread(&value,sizeof(value),1,uncompressednbt);
				SWAP(value);
				printf("\"):%f\n",value);
			}else{
				printf("\n[ERROR]\tTAG_Float has no name\n");
			}
			continue;
		}

		if(c == 0x06){
			c = getc(uncompressednbt);
			if(c != 0){
				printf("\n[Error]\tafter TAG_Double\n");
			}
			c = getc(uncompressednbt);
			if(c > 0){
				char tagname[c];
				double value;
				fread(&tagname,sizeof(tagname),1,uncompressednbt);
				printf("TAG_Double(\"");
				for(int i = 0; i < sizeof(tagname); i++){
					putchar(tagname[i]);
				}
				fread(&value,sizeof(value),1,uncompressednbt);
				SWAP(value);
				printf("\"):%lf\n",value);
			}else{
				printf("\n[ERROR]\tTAG_Double has no name\n");
			}
			continue;
		}

/*		if(c == 0x07){
			c = getc(uncompressednbt);
			if(c != 0){
				printf("\n[Error]\tafter TAG_Byte_Array\n");
			}
			c = getc(uncompressednbt);
			if(c > 0){
				char tagname[c];
				double value;
				fread(&tagname,sizeof(tagname),1,uncompressednbt);
				printf("TAG_Byte_Array(\"");
				for(int i = 0; i < sizeof(tagname); i++){
					putchar(tagname[i]);
				}
				fread(&value,sizeof(value),1,uncompressednbt);
				SWAP(value);
				printf("\"):%lf\n",value);
			}else{
				printf("\n[ERROR]\tTAG_Byte_Array has no name\n");
			}
		}*/


		if(c == 0x08){
			c = getc(uncompressednbt);
			if(c != 0){
				printf("\n[Error]\tafter TAG_String\n");
			}
			c = getc(uncompressednbt);
			if(c > 0){
				char tagname[c];
				int16_t length;
				fread(&tagname,sizeof(tagname),1,uncompressednbt);
				printf("TAG_String(\"");
				for(int i = 0; i < sizeof(tagname); i++){
					putchar(tagname[i]);
				}
				printf("\"):");
				fread(&length, sizeof(length),1,uncompressednbt);
				SWAP(length);
				char string[length];
				fread(&string, sizeof(string),1,uncompressednbt);
				for(int i = 0; i < sizeof(string); i++){
					putchar(string[i]);
				}
				printf("\n");
			}else{
				printf("\n[ERROR]\tTAG_String has no name\n");
			}
			continue;
		}


		//printf(" %d",c);
	}

	return 0;
}
