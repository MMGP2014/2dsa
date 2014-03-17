#include "DxLib.h"
#include "prot.h"
#include "mypath.h"
#include <stdio.h>
#include <string.h>

void file_in(ENEMY *ene,char *file){
//ファイルを開いて、えねに代入する関数。sscanf_s
	
	FILE *fp;
	char s[256];

	int i;
	i = 0;

	if((fopen_s(&fp,file,"r"))!=0){
		printf("ERORRRRRRR!");
		exit(EXIT_FAILURE);
	}

	
	while(fgets(s,256,fp) != NULL){
		i++;
			

	if(i<=1){	
		continue;	
		
	}
	sscanf_s(s,"%d,%d,%d,&d",&(ene+i-2)->type,&(ene+i-2)->size.x,&(ene+i-2)->size.y,&(ene+i-2)->HP);	

	/*ClearDrawScreen();
		print_char(s);
		print_int(i);
		ScreenFlip();

		WaitKey();
*/
	
	}
	

	fclose(fp);
	
}