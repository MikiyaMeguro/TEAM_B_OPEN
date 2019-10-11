//=============================================================================
//
// �J�����Ǘ����� [CameraManager.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v
//	�E�J�����𕡐����I�z��ŊǗ����AInit��Uninit,Update,SetCamera���ꊇ�ōs���N���X
//	�ECreateCamera���ĂԂ��ƂŃJ�������쐬����(���łɍ쐬����Ă���Ώ������̍X�V�̂ݍs��)
//	�ETexture�N���X��Command�N���X�Ɠ��l��Tag�ŊǗ������
//
//=============================================================================
#ifndef _CAMERA_MANAGER_H_
#define _CAMERA_MANAGER_H_

#include "main.h"
#include "camera.h"

class C3DCharactor;
//===================================================================
// �N���X�̒�`
//===================================================================
class CCameraManager
{
public:
	struct CAMERA_STATE
	{//�J�������̍\����
		CCamera* pCamera;	//�J�����̃|�C���^
		LPCSTR CameraTag;	//�J�������ʗp�̃^�O

		bool operator == (const LPCSTR Tag)
		{//�^�O��r(�����Ȃ�true)
			return (strcmp(CameraTag, Tag) == 0);
		}
	};

	CCameraManager();
	~CCameraManager();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);

	//�J�����̃Z�b�g
	bool SetCamera(LPCSTR Tag);

	//�J��������
	bool CreateCamera(LPCSTR Tag, CCamera::CAMERA_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength);

	//�J�����̃r���[�|�[�g�ݒ�
	bool SetCameraViewPort(LPCSTR Tag, int X, int Y, int Width, int Height, float MinZ = 0.0f, float MaxZ = 1.0f);

	//�Ǐ]����Ώۂ̐ݒ�
	bool SetCameraHomingChara(LPCSTR Tag, C3DCharactor* pHomingChara);

	//���b�N�I������Ώۂ̐ݒ�
	bool SetCameraLockOnChara(LPCSTR Tag, C3DCharactor* pLockOnChara);


	//�J�����폜
	bool DeleteCamera(LPCSTR Tag);

	CCamera* GetCamera(LPCSTR Tag);
	int GetCameraNum(void) { return m_vecCameraState.size(); };
private:
	std::vector<CAMERA_STATE> m_vecCameraState;	//�J�������̓��I�z��

	LPCSTR m_SetCamera;		//���݃Z�b�g���Ă���J�����̖��O
};
#endif // !_CAMERA_MANAGER_H_
