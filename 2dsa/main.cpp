//test
#include "Dxlib.h"
#include "prot.h"
#include "mypath.h"
#include <windows.h>
#include <string.h>




int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	if( DxLib_Init() == -1 ) return -1;
	SetBackgroundColor(255,255,255);
	SetDrawScreen( DX_SCREEN_BACK ); //�`���𗠉�ʂɐݒ�
	
	ClearDrawScreen();
	ScreenFlip(); //����ʂ�\��ʂɔ��f

	first_stg();

	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������
	return 0 ;				// �\�t�g�̏I�� 
}


//�ȉ��e�X�g�p���C���֐��i�����Ȃ��łˁj
/*
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	if( DxLib_Init() == -1 ) return -1;
	SetBackgroundColor(255,255,255);
	SetDrawScreen( DX_SCREEN_BACK ); //�`���𗠉�ʂɐݒ�
	ClearDrawScreen();
	ScreenFlip(); //����ʂ�\��ʂɔ��f
	ClearDrawScreen();
	char pic_name[]=PIC "test.jpg";
	int hand = LoadGraph(pic_name);
	DrawRotaGraph(2,2,1,0.0,hand,0,0);
	ScreenFlip(); //����ʂ�\��ʂɔ��f
	WaitKey();
	return 0;
}
*/
