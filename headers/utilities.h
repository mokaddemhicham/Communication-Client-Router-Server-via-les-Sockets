

char **fragmentation(char str[80]){
    char **strFr;
    strFr = (char * * )malloc(sizeof(char*)*5);
    for (int i = 0; i < 5; i++){
        *(strFr+i) = (char * )malloc(sizeof(char)*16);
    }

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			strFr[i][j] = str[(i*16)+j];
		}
		
	}
    return strFr;
}
