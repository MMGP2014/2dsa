#include "DxLib.h"
#include <windows.h>
#include <string.h>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	if( DxLib_Init() == -1 )		// �c�w���C�u��������������
	{
		return -1 ;			// �G���[���N�����璼���ɏI��
	}
	SetBackgroundColor(255,255,255);

	SetDrawScreen( DX_SCREEN_BACK ); //�`���𗠉�ʂɐݒ�
	int Cr;
    ClearDrawScreen(); // ��ʂ�����

	Cr = GetColor( 0 , 0 , 0 ) ;

    DrawString( 250 , 240 - 32 , "MAINnew!!\n" , Cr ); // ������̕`��


		ScreenFlip(); //����ʂ�\��ʂɔ��f


	WaitKey() ;				// �L�[���͑҂�
	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������
	return 0 ;				// �\�t�g�̏I�� 
}
