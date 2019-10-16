//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "title.h"
#include "debugProc.h"
#include "input.h"
#include "InputKeyboard.h"
#include "manager.h"
#include "fade.h"
#include "time.h"
#include "scene3D.h"
#include "scene2D.h"
#include "sceneX.h"
#include "sceneBillboard.h"
#include "SetObject.h"
#include "PlayerNumSelect.h"
//============================================================================
//	マクロ定義
//============================================================================

//============================================================================
//静的メンバ変数宣言
//============================================================================

//=============================================================================
//	コンストラクタ
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
void CTitle::Init(void)
{
	CScene3D::Create(D3DXVECTOR3(0,0,0),"BLOCK");
	CScene2D* p2D = NULL;
	p2D = CScene2D::Create(D3DXVECTOR3(200,100,0),"BLOCK");
	CSceneX::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_BOX,1);
	CSceneBillBoard::Create(D3DXVECTOR3(0, 0, 0),100,100, "BLOCK");
	CSetObject::Create();
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	//全ての終了処理
	CScene::ReleseAll();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTitle::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();

	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	//CXInputJoyPad *pXInput = NULL;
	//pXInput = CManager::GetXInput();
	//任意のキーENTER
	if (CCommand::GetCommand("ENTER"))
	{
		pFade->SetFade(pManager->MODE_SELECT, pFade->FADE_OUT);
	}


#ifdef _DEBUG
	CDebugProc::Print("c", "タイトル");
#endif
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTitle::Draw(void)
{

}
