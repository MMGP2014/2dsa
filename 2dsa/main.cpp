#include "DxLib.h"
#include "prot.h"
#include "mypath.h"
#include <windows.h>
#include <string.h>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	if( DxLib_Init() == -1 ) return -1;
	SetBackgroundColor(255,255,255);
	SetDrawScreen( DX_SCREEN_BACK ); //�`���𗠉�ʂɐݒ�
	ClearDrawScreen(); // ��ʂ�����

	int Cr;
	Cr = GetColor( 0 , 0 , 0 ) ;
    	DrawString( 250 , 240 - 32 , "�ׁA�ʂɂ��Ȃ��ɘM���Ă��A���������Ȃ��񂾂���˂��I!\n" , Cr ); // ������̕`��
	ScreenFlip(); //����ʂ�\��ʂɔ��f
	click_moji(" ���D�D�D�������B�D�D�D����I");

	WaitKey() ;				// �L�[���͑҂�

	int handle = LoadGraph(PIC "man.jpg");
	
	
	ClearDrawScreen(); // ��ʂ�����
	DrawGraph(100,100,handle,TRUE);
	ScreenFlip(); //����ʂ�\��ʂɔ��f


	WaitKey() ;				// �L�[���͑҂�
	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������
	return 0 ;				// �\�t�g�̏I�� 
}
