//=============================================================================
//
// �J�����Ǘ����� [CameraManager.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _CAMERA_MANAGER_H_
#define _CAMERA_MANAGER_H_

#include "main.h"
#include "camera.h"
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

	////�J�����폜
	//bool DeleteCamera(LPCSTR Tag);

	int GetCameraNum(void) { return m_vecCameraState.size(); };
private:
	std::vector<CAMERA_STATE> m_vecCameraState;	//�J�������̓��I�z��

	LPCSTR m_SetCamera;		//���݃Z�b�g���Ă���J�����̖��O
};
#endif // !_CAMERA_MANAGER_H_
