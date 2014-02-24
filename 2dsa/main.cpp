#include "DxLib.h"
#include "prot.h"
#include "mypath.h"
#include <windows.h>
#include <string.h>

// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	if( DxLib_Init() == -1 ) return -1;
	SetBackgroundColor(255,255,255);
	SetDrawScreen( DX_SCREEN_BACK ); //描画先を裏画面に設定
	ClearDrawScreen(); // 画面を消す

	int Cr;
	Cr = GetColor( 0 , 0 , 0 ) ;
    	DrawString( 250 , 240 - 32 , "べ、別にあなたに弄られても、何も感じないんだからねっ！!\n" , Cr ); // 文字列の描画
	ScreenFlip(); //裏画面を表画面に反映
	click_moji(" ぃ．．．うぅぅ。．．．ぁん！");

	WaitKey() ;				// キー入力待ち

	int handle = LoadGraph(PIC "man.jpg");
	
	
	ClearDrawScreen(); // 画面を消す
	DrawGraph(100,100,handle,TRUE);
	ScreenFlip(); //裏画面を表画面に反映


	WaitKey() ;				// キー入力待ち
	DxLib_End() ;				// ＤＸライブラリ使用の終了処理
	return 0 ;				// ソフトの終了 
}
