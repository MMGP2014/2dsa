<<<<<<< HEAD
#include "DxLib.h"

int Key[256]; // �L�[��������Ă���t���[�������i�[����

// �L�[�̓��͏�Ԃ��X�V����
int gpUpdateKey(){
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll( tmpKey ); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for( int i=0; i<256; i++ ){ 
		if( tmpKey[i] != 0 ){ // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		} else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
        ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

        int x=320, y=240;
        int Handle = LoadGraph("�摜/�L�����N�^01.png");
int k=0;
		int cr;
cr=GetColor(100,100,100);
        // while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A, �L�[�̍X�V)
        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && gpUpdateKey()==0 ){
=======
#include "Dxlib.h"
#include "prot.h"
#include "mypath.h"
#include <windows.h>
#include <string.h>
//////
// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	if( DxLib_Init() == -1 ) return -1;
	SetBackgroundColor(255,0,0);
	SetDrawScreen( DX_SCREEN_BACK ); //�`���𗠉�ʂɐݒ�
	ClearDrawScreen(); // ��ʂ�����

	int Cr;
	Cr = GetColor( 200 , 200 , 200 ) ;
    	DrawString( 200 , 250 -0, "T������������������������������������EST�B" , Cr ); // ������̕`��
	ScreenFlip(); //����ʂ�\��ʂɔ��f
	
>>>>>>> 8582e4ccb8925e7ea6ec51d32ed4b08e800bf1bd

                if( Key[ KEY_INPUT_RIGHT ] >= 1 ){ // �E�L�[��������Ă�����
			x++;                       // �E�ֈړ�
		}
		if( Key[ KEY_INPUT_DOWN  ] >= 1 ){ // ���L�[��������Ă�����
			y++;                       // ���ֈړ�
		}
		if( Key[ KEY_INPUT_LEFT  ] >= 1 ){ // ���L�[��������Ă�����
			x--;                       // ���ֈړ�
		}
		if( Key[ KEY_INPUT_UP    ] >= 1 ){ // ��L�[��������Ă�����
			y--;                       // ��ֈړ�
		}
			k++;
				if((k%50)==0){
					k=0;
				}
				DrawString(100,k*5,"up",cr);
		
		DrawRotaGraph( k*3, y, 1.0, 0.0, Handle, TRUE ); // x,y �̈ʒu�ɃL������`��

	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}
