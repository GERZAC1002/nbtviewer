extern void TAG_String(gzFile nbt,int8_t named){
	if(named == 1){
		int16_t tag_name_length;
		gzread(nbt, &tag_name_length, sizeof(tag_name_length));
		SWAP(tag_name_length);
		if(tag_name_length > 0){
			char tagname[tag_name_length];
			int16_t length;
			gzread(nbt, &tagname, sizeof(tagname));
			printf("TAG_STRING(\"");
			for(int i = 0; i < sizeof(tagname); i++){
				putchar(tagname[i]);
			}
			printf("\"): ");
			gzread(nbt, &length, sizeof(length));
			SWAP(length);
			char string[length];
			gzread(nbt, &string, sizeof(string));
			for(int i = 0; i < sizeof(string); i++){
				putchar(string[i]);
			}
			printf("\n");
		}else{
			printf("\n[ERROR]\tTAG_STRING has no name\n");
		}
	}else{
		int16_t length;
		printf("TAG_STRING(\"\"):");
		gzread(nbt, &length, sizeof(length));
		SWAP(length);
		char string[length];
		gzread(nbt, &string, sizeof(string));
		for(int i = 0; i < sizeof(string); i++){
			putchar(string[i]);
		}
		printf("\n");
	}
}


