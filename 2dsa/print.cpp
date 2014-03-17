#include "DxLib.h"
#include "prot.h"
#include <string.h>

void print_char(char str[]){
//if( DxLib_Init() == -1 ) return -1 ;
	int Cr;
	Cr = GetColor(0,0,0);
	DrawString(0,SCREEN_HIGHT/2,str,Cr);
}

void print_int(int num){
//if( DxLib_Init() == -1 ) return -1 ;
	int Cr;
	Cr = GetColor(0,0,0);
	char str[1000];
	sprintf_s(str,"%d",num);
	DrawString(SCREEN_WIDTH/2,SCREEN_HIGHT/2,str,Cr);
}
