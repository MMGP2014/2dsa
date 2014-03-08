#include "Dxlib.h"
#include "prot.h"
#include "mypath.h"
#include <windows.h>
#include <string.h>
//////
// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	if( DxLib_Init() == -1 ) return -1;
	SetBackgroundColor(255,255,255);
	SetDrawScreen( DX_SCREEN_BACK ); //描画先を裏画面に設定
	
	ClearDrawScreen();
	ScreenFlip(); //裏画面を表画面に反映

	playing();

	DxLib_End() ;				// ＤＸライブラリ使用の終了処理
	return 0 ;				// ソフトの終了 
}
