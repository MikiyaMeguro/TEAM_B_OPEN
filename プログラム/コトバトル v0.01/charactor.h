//=============================================================================
//
// �L�����N�^�[���� [charactor.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v
//	�EPosition��Rotation�ȂǁA�p������Ɏg���ϐ����������N���X�Q
//	�E�N���X���Ŏp��������s���AGet�֐��ł������擾����
//
//	C2DCharactor
//	�E2D�̃L�����N�^�[�p�̃N���X
//	�E�}�g���b�N�X���������APosition��Rotation�Ő��䂷��
//
//	C3DCharactor
//	�E3D�̃L�����N�^�[�p�̃N���X
//	�EPosition��Rotation�ɉ�����,�}�g���b�N�X���g���Ďp��������s��
//
//=============================================================================
#ifndef _CHARACTOR_H_
#define _CHARACTOR_H_

#include "scene.h"
class CCharaBase : public CScene
{
public:
	typedef enum
	{
		MOVETYPE_PLAYER_INPUT,		//�v���C���[�̑���
		MOVETYPE_AI,
		MOVETYPE_MAX
	}CHARACTOR_MOVE_TYPE;

private:
};

class C2DCharactor : public CCharaBase
{

};

class C3DCharactor : public CCharaBase
{

};

#endif // !_CHARACTOR_H_
