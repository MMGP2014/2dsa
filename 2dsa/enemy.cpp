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
	}
	fclose(fp);
}
