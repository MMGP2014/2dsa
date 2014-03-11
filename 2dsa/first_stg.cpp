#include "DxLib.h"
#include "prot.h"
#include "mypath.h"
#include <stdio.h>
#include <string.h>



int first_stg(void){
	int i,j;
	int turnflag=0;
    	int cr;
	int col0=GetColor(255,0,0);
	int col1=GetColor(0,255,0);
	FLOOR floor[ FLOOR_NUM ][ FLOOR_NUM ];
	char flr_name[1000];
	char tmp_char[1000];
	char stage[]="STAGE1";
	char main_name[]=PIC "sin.png";
	int main_handle = LoadGraph(main_name);
	SPEED speed;
	COORD2 crd,flr_crd;

	cr=GetColor(100,100,100);

	flr_crd.x=10; flr_crd.y=10;//初期フロア10,10
	speed.x=0; speed.y=0;

	for(i=0;i<FLOOR_NUM;i++){
		for(j=0;j<FLOOR_NUM;j++){
			if((i == 10) && (j == 10)){
				sprintf_s(flr_name,"%s%s\\floor_%d_%d",DATA,stage,i,j);
				sprintf_s(tmp_char,"%s.png",flr_name);
				floor[i][j].handle = LoadGraph(tmp_char);
				sprintf_s(tmp_char,"%s.csv",flr_name);
				input_csv(&floor[i][j],tmp_char);
			}
		}
	}
	crd.x= BLOCK_SIZE * 2;
	crd.y= BLOCK_SIZE * 2;

	while( ProcessMessage() == 0){
		ScreenFlip();
		ClearDrawScreen();

		DrawGraph(0,0,floor[flr_crd.x][flr_crd.y].handle,0);
		DrawString(540,0,"END:[ENTER]",cr);
		//print_char(tmp_char);
		//print_int(flr_crd.x);
		//print_int(flr_crd.y);
		/*
		for(i=1;i<=640;i++){
			for(j=1;j<=480;j++){
				if(floor[flr_crd.x][flr_crd.y] == 1){
				       	DrawPixel(i,j,col1);
				}else if(floor[flr_crd.x][flr_crd.y] == 0 ){
				       	DrawPixel(i,j,col0);
				}
			}
		}
		*/
		if(get_key_action(&speed,&turnflag,floor[flr_crd.x][flr_crd.y],crd))break;
		check_contact(&crd,&speed,&floor[flr_crd.x][flr_crd.y]);
		move_obj(main_handle,&crd,&speed,turnflag,&floor[flr_crd.x][flr_crd.y]);
	}
	return 0;
}
void move_obj(int handle,COORD2 *crd,SPEED *speed,int turnflag,FLOOR *floor){
	crd->y = crd->y + speed->y;
	crd->x = crd->x + speed->x;
	DrawRotaGraph(crd->x,crd->y,EXTRATE,0.0,handle,1,turnflag);
}


int get_key_action(SPEED *speed,int *turnflag,FLOOR floor,COORD2 crd){
	/************************************************* 
	/キー入力を読み取り、上下左右のスピードを計算する
	/また移動方向によりキャラの向きも算出する
	/終了のキーを受けたら1を返す
	 *************************************************/
	char key[256];	
	GetHitKeyStateAll( key ) ;

	//左右のキー入力
	if(key[KEY_INPUT_LEFT] >= 1){
	       	speed->x = -1 * LR_SPEED;
	}else if(key[KEY_INPUT_RIGHT] >= 1){ 
		speed->x = LR_SPEED;
	}else{ 
		speed->x=0;
       	}

	//上下のキー入力
	if(speed->y < 5) speed->y+=2;
	if(key[KEY_INPUT_DOWN] >= 1){
		speed->y += 3;
	}else if(key[KEY_INPUT_SPACE] >= 1 && jump_before(crd,floor)==1){
		speed->y = -20;
	}

	//エンターのキー入力(exit)
        if(key[KEY_INPUT_RETURN] >= 1) return 1; 

	//キャラクターの向き
	if(speed->x < 0){
		*turnflag = 1;
	} else if(speed->x > 0){
      		*turnflag = 0;
	}
	return 0;
}

void input_csv(FLOOR *floor,char *fname){
	int x,y;
	char buf[256];
	FILE *fp;
	if((fopen_s(&fp,fname,"r")) != 0) exit(EXIT_FAILURE);
	for(y=0; y < BLOCK_NUM_H ;y++){
		if( fgets(buf,256,fp) == NULL) exit(EXIT_FAILURE);
		for(x=0; x < BLOCK_NUM_W ;x++){
			floor->block[x][y] = atoi(&buf[2*x]);
		}
	}
	fclose(fp);
}

void check_contact(COORD2 *crd,SPEED *speed,FLOOR *floor){
	int block_pxl;
	int block_pxr;
	int block_pyu;
	int block_pyd;

	block_pyd = (crd->y + (BLOCK_SIZE / 2)  - 1) / BLOCK_SIZE;
	block_pyu = (crd->y - (BLOCK_SIZE / 2)) / BLOCK_SIZE;
	while(speed->x > 0){
		block_pxr = (crd->x + (BLOCK_SIZE / 2) + speed->x - 1) / BLOCK_SIZE;
		if((floor->block[block_pxr][block_pyu] == 0) && (floor->block[block_pxr][block_pyd] == 0)) break;
		speed->x--;
	}
	while(speed->x < 0){
		block_pxl = (crd->x - (BLOCK_SIZE / 2) + speed->x ) / BLOCK_SIZE;
		if((floor->block[block_pxl][block_pyu] == 0) && (floor->block[block_pxl][block_pyd] == 0)) break;
		speed->x++;
	}

	block_pxr = (crd->x + (BLOCK_SIZE / 2) + speed->x - 1) / BLOCK_SIZE;
	block_pxl = (crd->x - (BLOCK_SIZE / 2) + speed->x ) / BLOCK_SIZE;
	while(speed->y > 0){
		block_pyd = (crd->y + (BLOCK_SIZE / 2) + speed->y - 1 ) / BLOCK_SIZE;
		if((floor->block[block_pxr][block_pyd] == 0) && (floor->block[block_pxl][block_pyd] == 0)) break;
		speed->y--;
	}
	while(speed->y < 0){
		block_pyu = (crd->y - (BLOCK_SIZE / 2) + speed->y ) / BLOCK_SIZE;
		if((floor->block[block_pxr][block_pyu] == 0) && (floor->block[block_pxl][block_pyu] == 0)) break;
		speed->y++;
	}
}

int jump_before(COORD2 crd,FLOOR floor){

	int block_pyd;
	int block_pxr;
	int block_pxl;


	block_pyd = (crd.y + (BLOCK_SIZE / 2) ) / BLOCK_SIZE;
	block_pxr = (crd.x + (BLOCK_SIZE / 2)  -1) / BLOCK_SIZE;
	block_pxl = (crd.x - (BLOCK_SIZE / 2)  ) / BLOCK_SIZE;

	if(floor.block[block_pxl][block_pyd] ==0){
		return 0;
	}
	return 1;
}
