//=============================================================================
//
// シーン処理 [scene.h]
// Author : 目黒 未来也
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "sceneX.h"
#include "debugProc.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "player.h"
#include "tutorial.h"
#include "game.h"
#include "avoidui.h"

#include "point.h"
#include "CameraManager.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
int CScene::m_nNumAll = 0;
int CScene::m_nNumPriority[NUM_PRIORITY] = {};
CScene *CScene::m_apTop[NUM_PRIORITY] = {};
CScene *CScene::m_apCur[NUM_PRIORITY] = {};
bool    CScene::m_bPause = false;
bool    CScene::m_bDebug2Ddraw = false;
//=============================================================================
// シーンクラスのコンストラクタ
//=============================================================================
CScene::CScene(int nPriority, OBJTYPE objType)
{
	// 値のクリア
	m_nID = 0;
	m_pPrev = NULL;
	m_pNext = NULL;
	m_bDeath = false;
	m_bPause = false;

	if (m_apCur[nPriority] == NULL)
	{// カレントがNULLなら現在の位置が先頭
		m_apTop[nPriority] = this;
	}
	else
	{// カレントがNULLじゃなかったら
	 // 前回のSceneのm_pNextに今作ったSceneを入れる
		m_apCur[nPriority]->m_pNext = this;
	}

	m_pPrev = m_apCur[nPriority];	// 今作ったSceneのm_pPrevに前回のSceneを入れる
	m_pNext = NULL;					// 次のシーンはまだ作られていないからNULL
	m_apCur[nPriority] = this;		// カレントの位置を今作ったSceneに移動する
	m_nPriority = nPriority;		// プライオリティを保存
	m_objType = objType;			// オブジェクトの種類を保存
	m_nNumPriority[nPriority]++;

}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// 全てのオブジェクトの解放処理
//=============================================================================
void CScene::ReleseAll(void)
{
	CScene *pScene = NULL;

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// 優先順位の数分繰り返す
	 // 先頭を取得する
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{// 空になるまでアップデートする
		 // Updateの最中に消える可能性があるから先に記録しておく
			CScene *pSceneNext = pScene->m_pNext;

			// 更新
			pScene->Uninit();

			// 次のシーンに進める
			pScene = pSceneNext;
		}
	}

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// 優先順位の数分繰り返す
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{
			// Updateの最中に消える可能性があるから先に記録しておく
			CScene *pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				// フラグが立っているオブジェクトを消していく
				pScene->DeleteAll();
			}

			// 次のシーンに進める
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// 全てのオブジェクトの更新処理
//=============================================================================
void CScene::UpdeteAll(void)
{
	CScene *pScene = NULL;

	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//フェードしていないときにポーズできる
	if (CCommand::GetCommand("PAUSE") && CFade::GetFade() == CFade::FADE_NONE && CManager::GetMode() == CManager::MODE_GAME)
	{
		m_bPause = m_bPause ? false : true;
	}

	if (CCommand::GetCommand("DEBUG2D") == true)
	{
		m_bDebug2Ddraw = m_bDebug2Ddraw ? false : true;
	}

	if (m_bPause == false)
	{
		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{// 優先順位の数分繰り返す
		 // 先頭を取得する
			pScene = m_apTop[nCntPriority];

			while (pScene != NULL)
			{// 空になるまでアップデートする

			 // Updateの最中に消える可能性があるから先に記録しておく
				CScene *pSceneNext = pScene->m_pNext;
				// 更新
				if (pScene->GetObjType() != OBJTYPE_PAUSE)
				{
					if (pScene->m_bDeath == false)
					{
						pScene->Update();
					}
				}
				// 次のシーンに進める
				pScene = pSceneNext;
			}
		}

		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{// 優先順位の数分繰り返す
			pScene = m_apTop[nCntPriority];

			while (pScene != NULL)
			{
				// Updateの最中に消える可能性があるから先に記録しておく
				CScene *pSceneNext = pScene->m_pNext;

				if (pScene->GetObjType() != OBJTYPE_PAUSE)
				{
					if (pScene->m_bDeath == true)
					{
						// フラグが立っているオブジェクトを消していく
						pScene->DeleteAll();
					}
				}
				// 次のシーンに進める
				pScene = pSceneNext;
			}
		}
	}
	else
	{
		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{// 優先順位の数分繰り返す
		 // 先頭を取得する
			pScene = m_apTop[nCntPriority];

			while (pScene != NULL)
			{// 空になるまでアップデートする

			 // Updateの最中に消える可能性があるから先に記録しておく
				CScene *pSceneNext = pScene->m_pNext;
				if (pScene->GetObjType() == OBJTYPE_PAUSE)
				{
					// 更新
					pScene->Update();
				}
				// 次のシーンに進める
				pScene = pSceneNext;
			}
		}

		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{// 優先順位の数分繰り返す
			pScene = m_apTop[nCntPriority];

			while (pScene != NULL)
			{
				// Updateの最中に消える可能性があるから先に記録しておく
				CScene *pSceneNext = pScene->m_pNext;

				if (pScene->m_bDeath == true)
				{
					// フラグが立っているオブジェクトを消していく
					pScene->DeleteAll();
				}

				// 次のシーンに進める
				pScene = pSceneNext;
			}
		}
	}
}

//=============================================================================
// 全てのオブジェクトの描画処理
//=============================================================================
void CScene::DrawAll(int nCamera)
{
	CPlayer *pPlayer = NULL;
	CPoint *pPioint = NULL;

	pPlayer = CManager::GetPlayer(nCamera - 1);//プレイヤーの取得
	//pPioint = CManager::GetPoint(nCamera - 1);	// ポイント取得

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// 優先順位の数分繰り返す
	 // 先頭の場所を取得
		CScene *pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{// 空になるまで描画する
		 // Drawの最中に消える可能性があるから先に記録しておく
			CScene *pSceneNext = pScene->m_pNext;
			if (pScene->GetObjType() == OBJTYPE_PLAYER && nCamera != 5&& CCameraManager::GetCameraName() != "PAUSE_CAMERA")
			{
				CPlayer *pPlayerScene = ((CPlayer*)pScene);
				if (pPlayerScene->GetID() == nCamera - 1)
				{	// 自分を描画
					int ntest = pPlayerScene->GetID();
					pScene->Draw();

					CPlayer *pPlayerOld = CManager::GetPlayer(pPlayerScene->GetID()); // ポイントのID取得
					CScene3D *pScene3D = ((CScene3D*)pPlayerOld->GetBulletUI());
					if (pScene3D != NULL) { pScene3D->Draw(); }
				}
				else
				{	// 他プレイヤー描画
					if (pPlayer->GetVision(pPlayerScene->GetID()) == true)
					{
						int ntest = pPlayerScene->GetID();
						pScene->Draw();
					}
				}
			}
			else if (pScene->GetObjType() == OBJTYPE_POINT && nCamera != 5 && CCameraManager::GetCameraName() != "PAUSE_CAMERA")
			{
				CPoint *pPlayerScene = ((CPoint*)pScene);

				if (pPlayerScene->GetID() == nCamera - 1)
				{	// 自分を描画
					int ntest = pPlayerScene->GetID();
					pPlayerScene->Draw();

					pPioint = CManager::GetPoint(pPlayerScene->GetID()); // ポイントのID取得

					if (pPioint->GetID() == nCamera - 1)
					{	// 自分を描画
						CSceneBillBoard *pBill = ((CSceneBillBoard*)pPioint->GetCrwon());
						if (pBill != NULL) { pBill->Draw(); }
					}
				}
				else
				{	// 他プレイヤー描画
					if (pPlayer->GetVision(pPlayerScene->GetID()) == true)
					{
						int ntest = pPlayerScene->GetID();
						pPlayerScene->Draw();

						pPioint = CManager::GetPoint(pPlayerScene->GetID());
						CSceneBillBoard *pBill = ((CSceneBillBoard*)pPioint->GetCrwon());
						if (pBill != NULL) { pBill->Draw(); }
					}
				}
			}
			else if (pScene->GetObjType() == OBJTYPE_SCENEX&& CCameraManager::GetCameraName() != "PAUSE_CAMERA")
			{
				CSceneX *pSceneX = ((CSceneX*)pScene);
				if (pSceneX->GetModelType() == CLoad::MODEL_BUSH)
				{	//草むらのみ判定
					//どのプレイヤーカメラかを渡す
					pSceneX->SetCameraNum(nCamera - 1);
					// モデル描画
					pScene->Draw();
				}
				else
				{	//草むら以外を描画
					pScene->Draw();
				}
			}
			else if (pScene->GetObjType() == OBJTYPE_AVOIDUI&& CCameraManager::GetCameraName() != "PAUSE_CAMERA")
			{
				CAvoidUi *pAvoidUI = ((CAvoidUi*)pScene);
				//どのプレイヤーカメラかを渡す
				pAvoidUI->SetCameraNum(nCamera - 1);
				//モデル描画
				pScene->Draw();
			}
			else if (pScene->GetObjType() == OBJTYPE_PAUSE)
			{//ポーズ用カメラの時はポーズのみ描画する
				if (m_bPause == true)
				{
					pScene->Draw();
				}
			}
			else if ((pScene->GetObjType() == OBJTYPE_SCENE2D || pScene->GetObjType() == OBJTYPE_BILLBOARD
					|| pScene->GetObjType() == OBJTYPE_TIME || pScene->GetObjType() == OBJTYPE_POINT)
						&& CCameraManager::GetCameraName() != "PAUSE_CAMERA")
			{//
				if (m_bDebug2Ddraw == false)
				{
					pScene->Draw();
				}
			}
			else if(CCameraManager::GetCameraName() != "PAUSE_CAMERA" && pScene->GetObjType() != OBJTYPE_CROWN && pScene->GetObjType() != OBJTYPE_BULLETUI)
			{
				// 描画
				pScene->Draw();
			}

			// 次のシーンに進める
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// オブジェクトの解放処理
//=============================================================================
void CScene::Release(void)
{
	// 死亡フラグを立てる
	m_bDeath = true;
}

//=============================================================================
// フラグが立ったオブジェクトの解放処理
//=============================================================================
void CScene::DeleteAll(void)
{
	int nPriority;
	nPriority = m_nPriority;

	// 消えるオブジェクトの前がいるかどうか
	if (m_pPrev == NULL)
	{// 前がいない時
	 // 先頭を次にずらす
		m_apTop[nPriority] = m_pNext;
	}
	else
	{// 前がいる時
	 // 前のオブジェクトにある自分の情報を次のオブジェクトに渡す
		m_pPrev->m_pNext = m_pNext;
	}

	// 消えるオブジェクトの次がいるかどうか
	if (m_pNext == NULL)
	{// 次がいない時
	 // 現在（最後尾）のオブジェクトを前のオブジェクトに渡す
		m_apCur[nPriority] = m_pPrev;
	}
	else
	{// 次がいる時
	 // 次にいるオブジェクトにある自分の情報を前のオブジェクトに渡す
		m_pNext->m_pPrev = m_pPrev;
	}

	// 自分を消す
	delete this;

	m_nNumPriority[nPriority]--;
}

//=============================================================================
// オブジェクトの種類の設定
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// 優先順位の取得
//=============================================================================
int CScene::GetPriority(void)
{
	return m_nPriority;
}

//=============================================================================
// 先頭のオブジェクトを取得
//=============================================================================
CScene *CScene::GetTop(int nPriority)
{
	return m_apTop[nPriority];
}

//=============================================================================
// 次のオブジェクトのポインタを取得
//=============================================================================
CScene *CScene::GetNext(void)
{
	return m_pNext;
}

//=============================================================================
// 死亡フラグを取得
//=============================================================================
bool CScene::GetDeath(void)
{
	return m_bDeath;
}

//=============================================================================
// オブジェクトの種類の取得
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}