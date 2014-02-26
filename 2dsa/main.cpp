#include "DxLib.h"
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
	SetBackgroundColor(255,0,0);
	SetDrawScreen( DX_SCREEN_BACK ); //描画先を裏画面に設定
	ClearDrawScreen(); // 画面を消す

	int Cr;
	Cr = GetColor( 200 , 200 , 200 ) ;
    	DrawString( 200 , 250 -0, "TああああああああうｍがｌがあああああEST。" , Cr ); // 文字列の描画
	ScreenFlip(); //裏画面を表画面に反映
	

	WaitKey() ;				// キー入力待ち

	int handle = LoadGraph(PIC "man.png");
	ClearDrawScreen(); // 画面を消す
	DrawGraph( 50,0,handle,TRUE);
	ScreenFlip(); //裏画面を表画面に反映
	
	WaitKey() ;
	
	playing();

	WaitKey() ;				// キー入力待ち
	DxLib_End() ;				// ＤＸライブラリ使用の終了処理
	return 0 ;				// ソフトの終了 
}
