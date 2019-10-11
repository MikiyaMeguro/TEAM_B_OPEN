//=============================================================================
//
// カメラ管理処理 [CameraManager.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "CameraManager.h"
#include "Manager.h"


#define CAMERANAME_SETCAMERA_NONE "NONE"	//カメラがまだセットされてない時にm_SetCameraに入れる文字列
//===================================================================
// コンストラクタ&デストラクタ
//===================================================================
CCameraManager::CCameraManager()
{

}
CCameraManager::~CCameraManager()
{

}

//===================================================================
// 初期化処理
//===================================================================
HRESULT CCameraManager::Init(void)
{
	m_vecCameraState.clear();
	m_SetCamera = CAMERANAME_SETCAMERA_NONE;
	return S_OK;
}

//===================================================================
// 終了処理
//===================================================================
void CCameraManager::Uninit(void)
{
	for (auto itrCamera = m_vecCameraState.begin(); itrCamera != m_vecCameraState.end(); itrCamera++)
	{
		ObjRelease(itrCamera->pCamera);
	}
}

//===================================================================
// 更新処理
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
// カメラ設定処理
//===================================================================
bool CCameraManager::SetCamera(LPCSTR Tag)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (result != m_vecCameraState.end())
	{//カメラ名が定義されていれば
		if(result->CameraTag != m_SetCamera)
		{//この名前のカメラがまだセットされていなければ
			if (result->pCamera != NULL)
			{//カメラポインタがNULLでなければ
				result->pCamera->SetCamera();
				m_SetCamera = result->CameraTag;

				// バックバッファ＆Ｚバッファのクリア
				pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

				return true;
			}
		}

	}

	return false;
}

//===================================================================
// カメラ生成処理
//===================================================================
bool CCameraManager::CreateCamera(LPCSTR Tag, CCamera::CAMERA_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (Tag != CAMERANAME_SETCAMERA_NONE)
	{//カメラ名が既定の名前でなければ
		if (result == m_vecCameraState.end())
		{//まだTagと同じ名前のカメラが生成されてなければ
			CAMERA_STATE CameraState;

			if (ObjCreate(CameraState.pCamera))
			{
				CameraState.pCamera->Set(type, pos, rot, fLength);
				CameraState.CameraTag = Tag;
				m_vecCameraState.emplace_back(CameraState);
				return true;
			}
		}
		else
		{
			result->pCamera->Set(type, pos, rot, fLength);
		}
	}
	return false;
}

//===================================================================
// カメラの削除処理
//===================================================================
bool CCameraManager::DeleteCamera(LPCSTR Tag)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (result != m_vecCameraState.end())
	{//カメラ名が定義されていれば
		if (result->pCamera != NULL)
		{
			result->pCamera->Uninit();

			delete result->pCamera;
			result->pCamera = NULL;
		}

		m_vecCameraState.erase(result);
		return true;
	}

	return false;

}

//===================================================================
// カメラのビューポート設定処理
//===================================================================
bool CCameraManager::SetCameraViewPort(LPCSTR Tag, int X, int Y, int Width, int Height, float MinZ, float MaxZ)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (result != m_vecCameraState.end())
	{//カメラ名が定義されていれば
		result->pCamera->SetViewPort(X,Y,Width,Height,MinZ,MaxZ);

		return true;
	}

	return false;
}

//===================================================================
// カメラの追従対象設定処理
//===================================================================
bool CCameraManager::SetCameraHomingChara(LPCSTR Tag, C3DCharactor* pHomingChara)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (result != m_vecCameraState.end())
	{//カメラ名が定義されていれば
		result->pCamera->SetHomingChara(pHomingChara);
		return true;
	}

	return false;

}

//===================================================================
// カメラの追跡対象設定処理
//===================================================================
bool CCameraManager::SetCameraLockOnChara(LPCSTR Tag, C3DCharactor* pLockOnChara)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (result != m_vecCameraState.end())
	{//カメラ名が定義されていれば
		result->pCamera->SetLockOnChara(pLockOnChara);

		return true;
	}

	return false;

}

CCamera* CCameraManager::GetCamera(LPCSTR Tag)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (result != m_vecCameraState.end())
	{//カメラ名が定義されていれば
		return result->pCamera;
	}

	return NULL;

}