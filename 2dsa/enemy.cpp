#include "DxLib.h"
#include "prot.h"
#include "mypath.h"
#include <stdio.h>
#include <string.h>

void input_floor_enemy(FLOOR *flr,char *fname,ENEMY *ene){
	int cnt=-2;
	char buf[256];
	FILE *fp;
	if((fopen_s(&fp,fname,"r")) != 0) exit(EXIT_FAILURE);
	while(fgets(buf,256,fp) != NULL){
		cnt++;
		if(cnt == -1) continue;
		sscanf_s(buf,"%d,%d,%d",&flr->enemy[cnt].type,&flr->enemy[cnt].crd.x,&flr->enemy[cnt].crd.y);
		flr->enemy[cnt].HP=(ene+flr->enemy[cnt].type)->HP;
		flr->enemy[cnt].size=(ene+flr->enemy[cnt].type)->size;
		flr->enemy[cnt].handle=(ene+flr->enemy[cnt].type)->handle;
	}
	cnt++;
	flr->enemy_num=cnt;
	fclose(fp);
}


void file_in(ENEMY *ene,char *file){
//ファイルを開いて、えねに代入する関数。sscanf_s
	
	FILE *fp;
	char s[256];
	int i;
	i = 0;
	char file_name[1000];
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
	sprintf_s(file_name,"%senemy_type%d.png",PIC,(ene+i-2)->type);
	(ene+i-2)->handle = LoadGraph(file_name);
	
	/*ClearDrawScreen();
		print_char(s);
		print_int(i);
		ScreenFlip();

		WaitKey();
*/
	
	}
	

	fclose(fp);
	
}