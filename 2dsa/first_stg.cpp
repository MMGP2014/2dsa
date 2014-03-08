#include "DxLib.h"
#include "prot.h"
#include "mypath.h"
#include <stdio.h>



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
	ClearDrawScreen(); // âÊñ Çè¡Ç∑
	DrawGraph( 150,20,handle,TRUE);
	ScreenFlip(); //ó†âÊñ Çï\âÊñ Ç…îΩâf
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
		ScreenFlip();
		ClearDrawScreen();
	/*

		for(i1=0;i1<8;i1++){
			for(i2=0;i2<32;i2++){
				sprintf(kb,"%d",buf[i1*32+i2]);
				DrawString(i1*40,i2*15,kb,cr);
			}
		}

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
}
