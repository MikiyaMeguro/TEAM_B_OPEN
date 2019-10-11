//=============================================================================
//
// �J�����Ǘ����� [CameraManager.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "CameraManager.h"
#include "Manager.h"

#define CAMERANAME_SETCAMERA_NONE "NONE"	//�J�������܂��Z�b�g����ĂȂ�����m_SetCamera�ɓ���镶����
//===================================================================
// �R���X�g���N�^&�f�X�g���N�^
//===================================================================
CCameraManager::CCameraManager()
{

}
CCameraManager::~CCameraManager()
{

}

//===================================================================
// ����������
//===================================================================
HRESULT CCameraManager::Init(void)
{
	m_vecCameraState.clear();
	m_SetCamera = CAMERANAME_SETCAMERA_NONE;
	return S_OK;
}

//===================================================================
// �I������
//===================================================================
void CCameraManager::Uninit(void)
{
	for (auto itrCamera = m_vecCameraState.begin(); itrCamera != m_vecCameraState.end(); itrCamera++)
	{
		Release(itrCamera->pCamera);
	}
}

//===================================================================
// �X�V����
//===================================================================
void CCameraManager::Update(void)
{
	for (auto itrCamera = m_vecCameraState.begin(); itrCamera != m_vecCameraState.end(); itrCamera++)
	{
		if (itrCamera->pCamera != NULL)
		{
			itrCamera->pCamera->Update();
		}
	}
	m_SetCamera = CAMERANAME_SETCAMERA_NONE;
}

//===================================================================
// �J�����ݒ菈��
//===================================================================
bool CCameraManager::SetCamera(LPCSTR Tag)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (result != m_vecCameraState.end())
	{//�J����������`����Ă����
		if(result->CameraTag != m_SetCamera)
		{//���̖��O�̃J�������܂��Z�b�g����Ă��Ȃ����
			if (result->pCamera != NULL)
			{//�J�����|�C���^��NULL�łȂ����
				result->pCamera->SetCamera();
				m_SetCamera = result->CameraTag;

				// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
				pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

				return true;
			}
		}

	}

	return false;
}

//===================================================================
// �J������������
//===================================================================
bool CCameraManager::CreateCamera(LPCSTR Tag, CCamera::CAMERA_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (Tag != CAMERANAME_SETCAMERA_NONE)
	{//�J������������̖��O�łȂ����
		if (result == m_vecCameraState.end())
		{//�܂�Tag�Ɠ������O�̃J��������������ĂȂ����
			CAMERA_STATE CameraState;

			if (Create(CameraState.pCamera))
			{
				CameraState.pCamera->Set(type, pos, rot, fLength);
				CameraState.CameraTag = Tag;
				m_vecCameraState.emplace_back(CameraState);
				return true;
			}
		}
	}
	return false;
}

//===================================================================
// �J������������
//===================================================================
bool CCameraManager::SetCameraViewPort(LPCSTR Tag, int X, int Y, int Width, int Height, float MinZ, float MaxZ)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (result != m_vecCameraState.end())
	{//�J����������`����Ă����
		result->pCamera->SetViewPort(X,Y,Width,Height,MinZ,MaxZ);

		return true;
	}

	return false;
}