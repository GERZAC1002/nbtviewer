#define SEPERATOR '\t'

extern void TAG_Long_Array(gzFile nbt, int16_t *ident){
	int16_t tag_name_length;
	gzread(nbt, &tag_name_length, sizeof(tag_name_length));
	SWAP(tag_name_length);
	if(tag_name_length > 0){
		char tagname[tag_name_length];
		int32_t array_length;
		gzread(nbt, &tagname, sizeof(tagname));
		printf("TAG_LONG_ARRAY(\"");
		for(int i = 0; i < sizeof(tagname); i++){
			putchar(tagname[i]);
		}
		printf("\")\n");
		gzread(nbt, &array_length, sizeof(array_length));
		SWAP(array_length);
		for(int32_t i = 0; i < array_length; i++){
			putchar(SEPERATOR);
			for(int16_t i = 0; i < *ident; i++){
				putchar(SEPERATOR);
			}
			TAG_Long(nbt,0);
		}
	}else{
		printf("\n[ERROR]\tTAG_LONG_ARRAY has no name\n");
	}
}


