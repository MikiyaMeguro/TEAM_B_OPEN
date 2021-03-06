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
	// ランダムな値を更新
	srand((unsigned int)time(NULL));
	//任意のキーENTER
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
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