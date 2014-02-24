#include "DxLib.h"
#include <windows.h>
#include <string.h>

int click_moji(char *moji){
//if( DxLib_Init() == -1 ) return -1 ;
	int x,y;
	int Cr;
	Cr = GetColor(0,0,0);
	while(( GetMouseInput() & MOUSE_INPUT_LEFT ) == 0){
	}
	GetMousePoint( &x , &y );
	ClearDrawScreen(); // 画面を消す
	DrawString(x,y,moji,Cr);

	ScreenFlip(); //裏画面を表画面に反映
	return 0 ;				// ソフトの終了 
}
