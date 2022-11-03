extern void TAG_Int(gzFile nbt, int8_t named){
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
			printf("TAG_INT(\"");
			for(int i = 0; i < sizeof(tagname); i++){
				putchar(tagname[i]);
			}
			//fread(&value,sizeof(value),1,nbt);
			gzread(nbt, &value, sizeof(value));
			SWAP(value);
			printf("\"): %d\n",value);
		}else{
			printf("\n[ERROR]\tTAG_INT has no name\n");
		}
	}else{
		int32_t value;
		//fread(&value,sizeof(value),1,nbt);
		gzread(nbt,&value,sizeof(value));
		SWAP(value);
		printf("TAG_INT(\"\"): %d\n",value);
	}
}
