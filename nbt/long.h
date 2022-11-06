extern void TAG_Long(gzFile nbt, int8_t named){
	if(named == 1){
		int16_t tag_name_length;
		gzread(nbt, &tag_name_length, sizeof(tag_name_length));
		SWAP(tag_name_length);
		if(tag_name_length > 0){
			char tagname[tag_name_length];
			int64_t value;
			gzread(nbt, &tagname, sizeof(tagname));
			printf("TAG_LONG(\"");
			for(int i = 0; i < sizeof(tagname); i++){
				putchar(tagname[i]);
			}
			gzread(nbt, &value, sizeof(value));
			SWAP(value);
			printf("\"): %lld\n",value);
		}else{
			printf("\n[ERROR]\tTAG_LONG has no name\n");
		}
	}else{
		int64_t value;
		gzread(nbt, &value, sizeof(value));
		SWAP(value);
		printf("TAG_LONG(\"\"): %lld\n",value);
	}
}

