#include "DxLib.h"
#include <windows.h>
#include <string.h>

// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	if( DxLib_Init() == -1 )		// ＤＸライブラリ初期化処理
	{
		return -1 ;			// エラーが起きたら直ちに終了
	}
	SetBackgroundColor(255,255,255);

	SetDrawScreen( DX_SCREEN_BACK ); //描画先を裏画面に設定
	int Cr;
    ClearDrawScreen(); // 画面を消す

	Cr = GetColor( 0 , 0 , 0 ) ;

    DrawString( 250 , 240 - 32 , "MAINnew!!\n" , Cr ); // 文字列の描画


		ScreenFlip(); //裏画面を表画面に反映


	WaitKey() ;				// キー入力待ち
	DxLib_End() ;				// ＤＸライブラリ使用の終了処理
	return 0 ;				// ソフトの終了 
}
