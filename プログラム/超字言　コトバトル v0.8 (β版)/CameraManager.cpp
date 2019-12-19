//=============================================================================
//
// カメラ管理処理 [CameraManager.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "CameraManager.h"
#include "Manager.h"


#define CAMERANAME_SETCAMERA_NONE "NONE"	//カメラがまだセットされてない時にm_SetCameraに入れる文字列
#define BACK_DEFAULT_COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))

LPCSTR CCameraManager::m_SetCamera = CAMERANAME_SETCAMERA_NONE;


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
				WindowClear(pDevice,result->Property,result->BackgroundColor);

				return true;
			}
		}

	}

	return false;
}

//===================================================================
// カメラ生成処理
//===================================================================
bool CCameraManager::CreateCamera(LPCSTR Tag, CCamera::CAMERA_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength,DRAW_PROPERTY prop)
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
				CameraState.BackgroundColor = BACK_DEFAULT_COLOR;
				CameraState.Property = prop;
				m_vecCameraState.emplace_back(CameraState);

				return true;
			}
		}
		else
		{//既にカメラが生成されていれば
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
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		pCamera->SetViewPort(X,Y,Width,Height,MinZ,MaxZ);
		return true;
	}

	return false;
}

//===================================================================
// カメラの追従対象設定処理
//===================================================================
bool CCameraManager::SetCameraHomingChara(LPCSTR Tag, C3DCharactor* pHomingChara)
{
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		pCamera->SetHomingChara(pHomingChara);
		return true;
	}

	return false;

}

//===================================================================
// カメラの長さ設定処理
//===================================================================
bool CCameraManager::SetCameraLength(LPCSTR Tag, float fLength)
{
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		pCamera->SetLength(fLength);
		return true;
	}

	return false;

}
float CCameraManager::GetLength(LPCSTR Tag)
{
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		return pCamera->GetLength();
	}

	return -10000000000.0f;
}

//===================================================================
// カメラの追跡対象設定処理
//===================================================================
bool CCameraManager::SetCameraLockOnChara(LPCSTR Tag, C3DCharactor* pLockOnChara)
{
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		pCamera->SetLockOnChara(pLockOnChara);
		return true;
	}

	return false;

}

//===================================================================
// カメラの画角設定処理
//===================================================================
bool CCameraManager::SetCameraAngle(LPCSTR Tag, float fAngle)
{
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		pCamera->SetCameraAngle(fAngle);
		return true;
	}
	return false;
}

//===================================================================
// カメラの注視点設定処理
//===================================================================
bool CCameraManager::SetCameraPosR(LPCSTR Tag, D3DXVECTOR3 posR, bool bLeap)
{
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		pCamera->SetPosRDest(posR);//差分値に値を入れる
		if (bLeap == false)
		{//ワープさせる時は直接posRにも入れる
			pCamera->SetPosR(posR);
		}
		return true;
	}
	return false;
}

//===================================================================
// 背景色設定処理
//===================================================================
bool CCameraManager::SetBackGroundColor(LPCSTR Tag, D3DXCOLOR col)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (result != m_vecCameraState.end())
	{//カメラ名が定義されていれば
		result->BackgroundColor = col;

		return true;
	}

	return false;


}

//===================================================================
// カメラ取得処理
//===================================================================
CCamera* CCameraManager::GetCamera(LPCSTR Tag)
{
	return CameraSearch(Tag);
}

//===================================================================
// カメラ取得処理
//===================================================================
CCamera* CCameraManager::CameraSearch(LPCSTR Tag)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (result != m_vecCameraState.end())
	{//カメラ名が定義されていれば
		return result->pCamera;
	}
	return NULL;
}
//===================================================================
// ウィンドウ初期化処理
//===================================================================
void CCameraManager::WindowClear(LPDIRECT3DDEVICE9 pDev, DRAW_PROPERTY prop, D3DXCOLOR BG_Color)
{
	switch (prop)
	{
	case PROP_DEFAULT:
		pDev->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), BG_Color, 1.0f, 0);
		break;
	case PROP_INIT_ZONLY:
		pDev->Clear(0, NULL, (D3DCLEAR_ZBUFFER), BG_Color, 1.0f, 0);
		break;
	}


}