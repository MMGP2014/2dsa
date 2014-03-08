<<<<<<< HEAD
#include "DxLib.h"

int Key[256]; // キーが押されているフレーム数を格納する

// キーの入力状態を更新する
int gpUpdateKey(){
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll( tmpKey ); // 全てのキーの入力状態を得る
	for( int i=0; i<256; i++ ){ 
		if( tmpKey[i] != 0 ){ // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		} else {              // 押されていなければ
			Key[i] = 0;   // 0にする
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
        ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

        int x=320, y=240;
        int Handle = LoadGraph("画像/キャラクタ01.png");
int k=0;
		int cr;
cr=GetColor(100,100,100);
        // while(裏画面を表画面に反映, メッセージ処理, 画面クリア, キーの更新)
        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && gpUpdateKey()==0 ){
=======
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
	SetBackgroundColor(255,0,0);
	SetDrawScreen( DX_SCREEN_BACK ); //描画先を裏画面に設定
	ClearDrawScreen(); // 画面を消す

	int Cr;
	Cr = GetColor( 200 , 200 , 200 ) ;
    	DrawString( 200 , 250 -0, "TああああああああうｍがｌがあああああEST。" , Cr ); // 文字列の描画
	ScreenFlip(); //裏画面を表画面に反映
	
>>>>>>> 8582e4ccb8925e7ea6ec51d32ed4b08e800bf1bd

                if( Key[ KEY_INPUT_RIGHT ] >= 1 ){ // 右キーが押されていたら
			x++;                       // 右へ移動
		}
		if( Key[ KEY_INPUT_DOWN  ] >= 1 ){ // 下キーが押されていたら
			y++;                       // 下へ移動
		}
		if( Key[ KEY_INPUT_LEFT  ] >= 1 ){ // 左キーが押されていたら
			x--;                       // 左へ移動
		}
		if( Key[ KEY_INPUT_UP    ] >= 1 ){ // 上キーが押されていたら
			y--;                       // 上へ移動
		}
			k++;
				if((k%50)==0){
					k=0;
				}
				DrawString(100,k*5,"up",cr);
		
		DrawRotaGraph( k*3, y, 1.0, 0.0, Handle, TRUE ); // x,y の位置にキャラを描画

	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}
