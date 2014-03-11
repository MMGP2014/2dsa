//test
#include "Dxlib.h"
#include "prot.h"
#include "mypath.h"
#include <windows.h>
#include <string.h>




int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	if( DxLib_Init() == -1 ) return -1;
	SetBackgroundColor(255,255,255);
	SetDrawScreen( DX_SCREEN_BACK ); //描画先を裏画面に設定
	
	ClearDrawScreen();
	ScreenFlip(); //裏画面を表画面に反映

	first_stg();

	DxLib_End() ;				// ＤＸライブラリ使用の終了処理
	return 0 ;				// ソフトの終了 
}


//以下テスト用メイン関数（消さないでね）
/*
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	if( DxLib_Init() == -1 ) return -1;
	SetBackgroundColor(255,255,255);
	SetDrawScreen( DX_SCREEN_BACK ); //描画先を裏画面に設定
	ClearDrawScreen();
	ScreenFlip(); //裏画面を表画面に反映
	ClearDrawScreen();
	char pic_name[]=PIC "test.jpg";
	int hand = LoadGraph(pic_name);
	DrawRotaGraph(2,2,1,0.0,hand,0,0);
	ScreenFlip(); //裏画面を表画面に反映
	WaitKey();
	return 0;
}
*/
