#include "DxLib.h"
#include "prot.h"
#include "mypath.h"
#include <stdio.h>



<<<<<<< HEAD
int playing(void){
	int i;
	int a;
	int LRspeed=0;
	int UDspeed =0;
	int left = LEFT;
	int right = RIGHT;
	int up = UP;
	int down = DOWN;
	int jump = JUMP;

	COORD2 crd;
	
	crd.x=250;
	crd.y=250;
	

	int handle = LoadGraph(PIC "tarou.png");
	ClearDrawScreen(); // 画面を消す
	DrawGraph( 150,20,handle,TRUE);
	ScreenFlip(); //裏画面を表画面に反映
	WaitKey();
	char aa[100];
	sprintf(aa,"%d%d%d%d%d",left,right,up,down,jump);
	click_moji(aa);
	WaitKey();
	i=0;
	char buf[256];	

    int cr;
	int i1,i2;
	char kb[100];
		LRspeed=1;

	while(1){
		GetHitKeyStateAll( buf ) ;
		i++;
		cr=GetColor(100,100,100);
=======
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
	char main_name[]=PIC "tarou2.png";
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
>>>>>>> 87824626ad5ea71436b410bdbf14a1db8b1ac5e0
		ScreenFlip();
		ClearDrawScreen();
	/*

<<<<<<< HEAD
		for(i1=0;i1<8;i1++){
			for(i2=0;i2<32;i2++){
				sprintf(kb,"%d",buf[i1*32+i2]);
				DrawString(i1*40,i2*15,kb,cr);
			}
		}
=======
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
		if(get_key_action(&speed,&turnflag)) break;
		check_contact(&crd,&speed,&floor[flr_crd.x][flr_crd.y]);
		move_obj(main_handle,&crd,&speed,turnflag,&floor[flr_crd.x][flr_crd.y]);
	}
	return 0;
}
void move_obj(int handle,COORD2 *crd,SPEED *speed,int turnflag,FLOOR *floor){
	crd->y = crd->y + speed->y;
	crd->x = crd->x + speed->x;
	DrawRotaGraph(crd->x,crd->y,EXTRATE,0.0,handle,0,turnflag);
}


int get_key_action(SPEED *speed,int *turnflag){
	/************************************************* 
	/キー入力を読み取り、上下左右のスピードを計算する
	/また移動方向によりキャラの向きも算出する
	/終了のキーを受けたら1を返す
	 *************************************************/
	char key[256];	
	GetHitKeyStateAll( key ) ;

	//左右のキー入力
	if(key[KEY_INPUT_LEFT] >= 1){
	       	speed->x =-2;
	}else if(key[KEY_INPUT_RIGHT] >= 1){ 
		speed->x =2;
	}else{ 
		speed->x=0;
       	}

	//上下のキー入力
	if(key[KEY_INPUT_DOWN] >= 1){
		speed->y = 2;
	}else if(key[KEY_INPUT_UP] >= 1){
		speed->y = -2;
	}else{
	        speed->y = 0;
	}

	//エンターのキー入力(exit)
        if(key[KEY_INPUT_RETURN] >= 1) return 1; 
>>>>>>> 87824626ad5ea71436b410bdbf14a1db8b1ac5e0

*/
/*

	if (i>1000)break;
		if(buf[KEY_INPUT_LEFT] >= 1){
//		DrawString(100,100,"left",cr);
			LRspeed =-1;
		}
		if(buf[KEY_INPUT_RIGHT] >= 1){
//		DrawString(100,100,"right",cr);
			LRspeed =1;
		}
		if(buf[KEY_INPUT_DOWN] >= 1){
//		DrawString(100,100,"do",cr);
			UDspeed = 1;
		}
		if(buf[KEY_INPUT_UP] >= 1){
//		DrawString(100,100,"up",cr);
			UDspeed = -1;
		}
		if(buf[KEY_INPUT_SPACE] >= 1){
			break;
		}
//	DrawString(100,i,"up",cr);
*/
		if((i%10) == 0 ){
			LRspeed *= -1;
		}
	move_obj("tarou.png",&crd,UDspeed,LRspeed);
	}
<<<<<<< HEAD
//	WaitKey();
	return 0;
}
void move_obj(char *name,COORD2 *crd,int UDspeed,int LRspeed){
	crd->y = crd->y + UDspeed;
	crd->x = crd->x + LRspeed;
	char pname[10000];
		sprintf(pname,"%s%s",PIC,name);

	int handle = LoadGraph(pname);
	ClearDrawScreen();
	DrawGraph(crd->x,crd->y,handle,TRUE);
=======
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
		if((floor->block[block_pxr][block_pyu] == 0) && (floor->block[block_pxl][block_pyd] == 0)) break;
		speed->y--;
	}
	while(speed->y < 0){
		block_pyu = (crd->y - (BLOCK_SIZE / 2) + speed->y ) / BLOCK_SIZE;
		if((floor->block[block_pxr][block_pyu] == 0) && (floor->block[block_pxl][block_pyd] == 0)) break;
		speed->y++;
	}
>>>>>>> 87824626ad5ea71436b410bdbf14a1db8b1ac5e0
}


