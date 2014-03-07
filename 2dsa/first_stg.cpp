#include "DxLib.h"
#include "prot.h"
#include "mypath.h"
#include <stdio.h>
#include <string.h>



int playing(void){
	int i=0;
	int LRspeed=0,UDspeed =0;
	int turnflag=0;
    	int cr;
	char stage_name[]=PIC "stage_test.png";
	char main_name[]=PIC "tarou2.png";
	int stage_handle = LoadGraph(stage_name);
	int main_handle = LoadGraph(main_name);
	char key[256];	
	COORD2 crd;

	stage_handle = LoadGraph(stage_name);
	
	crd.x=250;crd.y=250; //test

	while( ProcessMessage() == 0){
		ScreenFlip();
		ClearDrawScreen();
		DrawGraph(0,0,stage_handle,0);
		GetHitKeyStateAll( key ) ;
		i++;
		cr=GetColor(100,100,100);

		if(key[KEY_INPUT_LEFT] >= 1){
		       	LRspeed =-2;
		}else if(key[KEY_INPUT_RIGHT] >= 1){ 
			LRspeed =2;
		}else{ 
			LRspeed=0;
	       	}
		if(key[KEY_INPUT_DOWN] >= 1){
			UDspeed = 2;
		}else if(key[KEY_INPUT_UP] >= 1){
			UDspeed = -2;
		}else{
		       UDspeed = 0;
		}
	        if(key[KEY_INPUT_RETURN] >= 1){
			break;
		}

		if(LRspeed < 0){
			turnflag = 1;
		} else if(LRspeed > 0){
	      		turnflag = 0;
		}
	
		DrawString(540,0,"END:[ENTER]",cr);
		move_obj(main_handle,&crd,UDspeed,LRspeed,turnflag);
	}
//	WaitKey();
	return 0;
}
void move_obj(int handle,COORD2 *crd,int UDspeed,int LRspeed,int turnflag){
	crd->y = crd->y + UDspeed;
	crd->x = crd->x + LRspeed;
	DrawRotaGraph(crd->x,crd->y,EXTRATE,0.0,handle,TRUE,turnflag);
}
