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
LPDIRECT3DTEXTURE9 CWall::m_pTexture[MAX_WALL_TEX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CWall::CWall() : CScene3D(4, CScene::OBJTYPE_WALL)
{
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
	CScene3D::SetSizeY(size.y, size.x);
	if (nType == 0){SetInitAll(pos, rot, size, col, TexUV, SCENE3DTYPE_NORMAL);}
	else{SetInitAll(pos, rot, size, col, TexUV, SCENE3DTYPE_BILLBOARD); }

	if (nTexType == 0){CScene3D::BindTexture("FIELD");}
	else if (nTexType == 1){CScene3D::BindTexture("PAD");}
	else if (nTexType == 2) { CScene3D::BindTexture("TUROFLOW"); }


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

	CScene3D::SetPos(WallPos);						//	位置の設定
	CScene3D::SetRot(WallRot);						//	回転の設定
	CScene3D::SetSizeY(WallSizeY, WallSizeX);		//	大きさの設定

	CScene3D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CWall::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// カリングなくす
	CScene3D::Draw();
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリングに戻す

}
