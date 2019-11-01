//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "camera.h"
#include "InputKeyboard.h"
#include "Manager.h"
#include "renderer.h"
#include "debugProc.h"

#include "charactor.h"
#define ANGLE_MOVE  (0.03f) //カメラ角度の移動量
#define CAMERA_POSR_COEFFICIENT (0.50f);	//カメラ注視点の係数
#define CAMERA_POSV_COEFFICIENT (0.18f);	//カメラ視点の係数

#define CAMERA_POS_INTERVAL (20.0f)			//カメラの注視点の位置

//=============================================================================
// コンストラクタ&デストラクタ
//=============================================================================
CCamera::CCamera()
{
	m_fCameraAngle = 45.0f;
	m_pHomingChara = NULL;
	m_pLockOnChara = NULL;
}
CCamera::~CCamera()
{

}
//=============================================================================
// 設定処理
//=============================================================================
void CCamera::Set(CAMERA_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength)
{
	m_Type = type;		//タイプの設定

	m_rot = rot;
	m_fLength = fLength;

	switch (m_Type)
	{
	case CCamera::TYPE_FPS:
		m_posV = pos;
		m_posR = pos + D3DXVECTOR3(sinf(rot.y) * fLength, sinf(rot.x) * fLength, cosf(rot.y) * fLength);
		break;
	case CCamera::TYPE_TPS:
		m_posR = pos;
		m_posV = pos - D3DXVECTOR3(sinf(rot.y) * fLength, sinf(rot.x) * fLength, cosf(rot.y) * fLength);
		break;
	case CCamera::TYPE_SPECTOR:
		break;
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
void CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVdest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRdest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update(void)
{
	CInputKeyboard* pInput = CManager::GetInputKeyboard();

	switch (m_Type)
	{
	case TYPE_FPS:
		break;
	case TYPE_TPS:
		if (m_pHomingChara != NULL)
		{
			if (m_pLockOnChara != NULL)
			{
				//角度
				m_rot.y = atan2f(m_pLockOnChara->GetCameraPosR().x - m_pHomingChara->GetCameraPosR().x ,
					m_pLockOnChara->GetCameraPosR().z - m_pHomingChara->GetCameraPosR().z);
				m_pHomingChara->GetSpin().y = m_rot.y;

				//座標
				D3DXVec3Lerp(&m_posRdest, &m_pLockOnChara->GetCameraPosR(), &m_pHomingChara->GetCameraPosR(), 1.0f);
				//m_posRdest = m_pLockOnChara->GetCameraPosR();
				m_posR += (m_posRdest - m_posR) * CAMERA_POSR_COEFFICIENT;

				m_posVdest = m_pHomingChara->GetCameraPosR() - D3DXVECTOR3(sinf(m_rot.y) * m_fLength * 2.0f,
					sinf(m_rot.x) * m_fLength * 2.0f,
					cosf(m_rot.y) * m_fLength * 2.0f);
				m_posV += (m_posVdest - m_posV) * CAMERA_POSV_COEFFICIENT;

			}
			else
			{
				m_posRdest = m_pHomingChara->GetCameraPosR();
				m_posR += (m_posRdest - m_posR) * CAMERA_POSR_COEFFICIENT;
				m_posVdest = m_posR - D3DXVECTOR3(sinf(m_rot.y) * m_fLength,
					sinf(m_rot.x) * m_fLength,
					cosf(m_rot.y) * m_fLength);
				m_posV += (m_posVdest - m_posV) * CAMERA_POSV_COEFFICIENT;
			}
		}


		break;
	case TYPE_SPECTOR:
		break;
	}


	//角度Yの補正
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

}

//=============================================================================
// 設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	CRenderer* pRenderder = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderder->GetDevice();	// デバイスの取得

	pDevice->SetViewport(&m_ViewPort);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(m_fCameraAngle),
		(float)m_ViewPort.Width / (float)m_ViewPort.Height,
		10.0f,
		10000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);


	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

#ifdef _DEBUG
	CDebugProc::Print("cff", "Camera.PosV :", m_posV.x, m_posV.y, m_posV.z);
	CDebugProc::Print("cff","Camera.PosR :", m_posR.x, m_posR.y, m_posR.z);
#endif

}