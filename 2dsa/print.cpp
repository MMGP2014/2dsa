#include "DxLib.h"
#include "prot.h"
#include <windows.h>
#include <string.h>
#include <limits.h>

int print_char(char *str){
//if( DxLib_Init() == -1 ) return -1 ;
	int Cr;
	Cr = GetColor(0,0,0);
	DrawString(WIDTH/2,HIGHT/2,str,Cr);
	return 0 ;				// ソフトの終了 
}

int print_int(int num){
	int Cr;
	char str[100];
	sprintf_s(str,"%d",num);
	Cr = GetColor(0,0,0);
	DrawString(WIDTH/2,HIGHT/2,str,Cr);
	return 0 ;				// ソフトの終了 
}

int print_double(double num){
	int Cr;
	char str[100];
	sprintf_s(str,"%lf",num);
	Cr = GetColor(0,0,0);
	DrawString(WIDTH/2,HIGHT/2,str,Cr);
	return 0 ;				// ソフトの終了 
}
