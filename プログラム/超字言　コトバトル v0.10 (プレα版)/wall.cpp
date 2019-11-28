//=============================================================================
//
// 壁処理 [wall.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene3D.h"		// シーン3D
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラー
#include "wall.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CWall::CWall() : CScene3D(4, CScene::OBJTYPE_WALL)
{
	m_nType = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
	m_nAnimCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CWall::~CWall()
{
}

//=============================================================================
//	アイテムの生成
//=============================================================================
CWall *CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int nType, int nTexType)
{
	CWall *pWall = {};

	if (pWall == NULL)
	{//	アイテムの生成
		pWall = new CWall;
		if (pWall != NULL)
		{//アイテムの初期化
			pWall->Init(pos, rot, size, col, TexUV, nType, nTexType);
		}
	}
	return pWall;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int nType, int nTexType)
{
	CScene3D::SetTexUV(TexUV);
	CScene3D::SetPos(pos);
	CScene3D::SetRot(rot);
	CScene3D::Init();
	CScene3D::SetColor(col);
	if (size.z > 0.1f)
	{
		CScene3D::SetSize(size.z, size.x);
	}
	else if (size.y > 0.1f) { CScene3D::SetSizeY(size.y, size.x); }
	m_nType = nTexType;
	if (nType == 0) { SetInitAll(pos, rot, size, col, TexUV, SCENE3DTYPE_NORMAL); }
	else { SetInitAll(pos, rot, size, col, TexUV, SCENE3DTYPE_BILLBOARD); }

	if (m_nType == 0) { CScene3D::BindTexture("FIELD"); }
	else if (m_nType == 1) { CScene3D::BindTexture("PAD"); }
	else if (m_nType == 2) { CScene3D::BindTexture("TUROFLOW000"); }
	else if (m_nType == 3) { CScene3D::BindTexture("TUROFLOW001"); }
	else if (m_nType == 4) { CScene3D::BindTexture("NEXT"); }
	else if (m_nType == 5) { CScene3D::BindTexture("FIELD002"); }
	else if (m_nType == 6) { CScene3D::BindTexture("FIELD002"); }
	else if (m_nType == 7) { CScene3D::BindTexture("FIELD002"); }


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CWall::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CWall::Update(void)
{
	D3DXVECTOR3 WallPos = CScene3D::GetPos();		//	位置の取得
	D3DXVECTOR3 WallRot = CScene3D::GetRot();		//	回転の取得
	float WallSizeY = CScene3D::GetSizeY();			//	幅の取得
	float WallSizeX = CScene3D::GetSizeX();			//	幅の取得

	if (m_nType == 4)
	{//	ボタン　表示
		m_nCounter++;
		if (m_nCounter < 60) { m_move.y = 0.3f; }
		else if (m_nCounter < 120) { m_move.y = -0.3f; }
		else if (m_nCounter == 120) { m_nCounter = 0; }
	}

	if (m_nType == 5)
	{//	川の流れる
		m_nCounter++;
		if (m_nCounter > 3750)
		{
			Uninit();
		}
	}
	else if (m_nType == 6)
	{//	川の流れる
		m_nCounter++;
		if (m_nCounter % 10 == 0)
		{
			m_nAnimCounter++;
			SetAnimation(m_nAnimCounter, 0.9f, 1.0f);
		}
		if (m_nCounter > 3750)
		{
			CWall::Create(D3DXVECTOR3(-200.0f, 5.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(40.0f, 400.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), D3DXVECTOR2(5.0f, 5.0f), 0, 7);
			Uninit();
		}
	}

	WallPos += m_move;
	CScene3D::SetPos(WallPos);						//	位置の設定
	CScene3D::SetRot(WallRot);						//	回転の設定
	CScene3D::SetSizeY(WallSizeY, WallSizeX);		//	大きさの設定
}

//=============================================================================
// 描画処理
//=============================================================================
void CWall::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_nType == 6 || m_nType == 5)
	{//	川は両面化する
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// カリングなくす
	}
	CScene3D::Draw();
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリングに戻す

}
