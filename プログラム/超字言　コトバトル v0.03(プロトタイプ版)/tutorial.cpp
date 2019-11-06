//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "tutorial.h"
#include "manager.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"
#include "sceneX.h"
#include "game.h"
#include "debugProc.h"
#include "scene.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include <time.h>
#include "load.h"
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
CTutorial::CTutorial()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
void CTutorial::Init(void)
{
	//インスタンス
	CManager *pManager = NULL;

	CScene2D* p2D = NULL;
	p2D = CScene2D::Create(D3DXVECTOR3(300, 200, 0), "WORD");
	p2D->SetWidthHeight(200.0f,200.0f);
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	//全ての終了処理
	CScene::ReleseAll();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTutorial::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();

	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	//任意のキーENTER
	if (CCommand::GetCommand("DECISION"))
	{
		pFade->SetFade(pManager->MODE_CHARASELECT, pFade->FADE_OUT);
	}

#ifdef _DEBUG
	CDebugProc::Print("c", "チュートリアル");
#endif

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}