//=============================================================================
//
// キャラセレクト処理 [CharaSelect.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "CharaSelect.h"
#include "manager.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"
#include "game.h"
#include "debugProc.h"
#include "scene.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include <time.h>

//============================================================================
//	マクロ定義
//============================================================================
#define SIZE_X (SCREEN_WIDTH)
#define SIZE_Y (SCREEN_HEIGHT)
#define COLISIONSIZE (20.0f)
#define TIME_INI		(60)
//============================================================================
//静的メンバ変数宣言
//============================================================================

//=============================================================================
//	コンストラクタ
//=============================================================================
CCharaSelect::CCharaSelect()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CCharaSelect::~CCharaSelect()
{

}

//=============================================================================
// キャラセレクトの初期化処理
//=============================================================================
void CCharaSelect::Init(void)
{
	//インスタンス
	CManager *pManager = NULL;

	CScene2D* p2D = NULL;
	p2D = CScene2D::Create(D3DXVECTOR3(300, 100, 0), "BLOCK");

}

//=============================================================================
// キャラセレクトの終了処理
//=============================================================================
void CCharaSelect::Uninit(void)
{
	//全ての終了処理
	CScene::ReleseAll();
}

//=============================================================================
// キャラセレクトの更新処理
//=============================================================================
void CCharaSelect::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();

	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//任意のキーENTER
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		pFade->SetFade(pManager->MODE_STAGESELECT, pFade->FADE_OUT);
	}

#ifdef _DEBUG
	CDebugProc::Print("c", "キャラセレクト");
#endif

}

//=============================================================================
// キャラセレクトの描画処理
//=============================================================================
void CCharaSelect::Draw(void)
{

}