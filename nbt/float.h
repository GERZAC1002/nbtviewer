extern void TAG_Float(gzFile nbt, int8_t named){
	if(named == 1){
		int16_t tag_name_length;
		gzread(nbt, &tag_name_length, sizeof(tag_name_length));
		SWAP(tag_name_length);
		if(tag_name_length > 0){
			char tagname[tag_name_length];
			float value;
			gzread(nbt, &tagname, sizeof(tagname));
			printf("TAG_FLOAT(\"");
			for(int i = 0; i < sizeof(tagname); i++){
				putchar(tagname[i]);
			}
			gzread(nbt, &value, sizeof(value));
			SWAP(value);
			printf("\"): %f\n",value);
		}else{
			printf("\n[ERROR]\tTAG_FLOAT has no name\n");
		}
	}else{
		float value;
		gzread(nbt, &value, sizeof(value));
		SWAP(value);
		printf("TAG_FLOAT(\"\"): %f\n",value);
	}
}
