//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "scene.h"
#include "DebugProc.h"

//===================================================================
//	静的メンバ変数宣言
//===================================================================
int     CScene::m_nNumAll[PRIORITY_MAX] = {};
CScene* CScene::m_apTop[PRIORITY_MAX] = {};
CScene* CScene::m_apCur[PRIORITY_MAX] = {};

//===================================================================
//	コンストラクタ
//===================================================================
CScene::CScene(PRIORITY pri, OBJTYPE type)
{
	CScene* pScene = this;

	pScene->AddList(pri);

	m_Priority = pri;
	m_objType = type;
	m_bDeath = false;
}

//===================================================================
//	死亡フラグ立て
//===================================================================
void CScene::Release(void)
{
	m_bDeath = true; //死亡フラグ
}

//===================================================================
//	一括メモリ解放
//===================================================================
void CScene::ReleaseAll(bool bFadeRelease)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene* pScene = m_apTop[nCntPri];
		if (pScene != NULL)
		{
			do
			{
				CScene* pSceneNext = pScene->m_pNext;
				if (bFadeRelease == false)
				{//フェードは消さないなら
					if (pScene->GetObjType() != OBJTYPE_FADE)
					{//オブジェクトがフェードポリゴンでなければ
						pScene->Uninit();
					}
				}
				else
				{
					pScene->Uninit();
				}
					pScene = pSceneNext;
			} while (pScene != NULL);
		}

		if (m_nNumAll[nCntPri] <= 0)
		{
			m_apTop[nCntPri] = NULL;
			m_apCur[nCntPri] = NULL;
		}

		DeadCheck((PRIORITY)nCntPri);

		m_nNumAll[nCntPri] = 0;
	}

}

//===================================================================
//	一括更新
//===================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene* pScene = m_apTop[nCntPri];
		if (pScene != NULL)
		{
			do
			{
				CScene* pSceneNext = pScene->m_pNext;		//いったん退避させる
				pScene->Update();
				pScene = pSceneNext;
			} while (pScene != NULL); //(pScene)← これと同じ条件式
		}

		DeadCheck((PRIORITY)nCntPri);
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		DeadCheck((PRIORITY)nCntPri);
	}

#ifdef _DEBUG
	//デバッグ
	int  nSum = 0;
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CDebugProc::Print("OBJECT_%d:%d\n", nCntPri, m_nNumAll[nCntPri]);
		nSum += m_nNumAll[nCntPri];
	}
	CDebugProc::Print("OBJECT_SUM:%d\n", nSum);
#endif


}

//===================================================================
//	一括描画
//===================================================================
void CScene::DrawAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene* pScene = m_apTop[nCntPri];
		if (pScene != NULL)
		{
			do
			{
				CScene* pSceneNext = pScene->m_pNext;
				pScene->Draw();
				pScene = pSceneNext;
			} while (pScene != NULL);
		}
	}

}

//===================================================================
//	リストに追加
//===================================================================
void CScene::AddList(CScene::PRIORITY pri)
{
	//先端と末端を決める
	if (m_apTop[pri] == NULL)
	{//1つ目の場合
		m_apTop[pri] = this;
		m_apCur[pri] = this;
	}
	else
	{//それ以降の場合
		CScene* pScene = m_apCur[pri];		//いったん退避

		m_apCur[pri] = this;
		m_apCur[pri]->m_pPrev = pScene;
		m_apCur[pri]->m_pNext = NULL;
		pScene->m_pNext = m_apCur[pri];
	}

	//m_nID = m_nNumAll[pri];
	m_nNumAll[pri]++;
}

//===================================================================
//	リストから削除
//===================================================================
void CScene::DeleteList(CScene::PRIORITY pri)
{
	//退避
	CScene* pScene = this;
	CScene* pScenePrev = pScene->m_pPrev;
	CScene* pSceneNext = pScene->m_pNext;

	if (pScene == m_apTop[pri])
	{//このオブジェクトが先端なら
		m_apTop[pri] = pSceneNext;
		if (m_apTop[pri] != NULL)
		{
			m_apTop[pri]->m_pPrev = NULL;
		}
	}
	else if (pScene == m_apCur[pri])
	{//このオブジェクトが末端なら
		m_apCur[pri] = pScenePrev;
		if (m_apTop[pri] != NULL)
		{
			m_apCur[pri]->m_pNext = NULL;
		}
	}
	else
	{//それ以外なら
		pScenePrev->m_pNext = pSceneNext;
		pSceneNext->m_pPrev = pScenePrev;
	}

	m_nNumAll[pri]--;
}

//===================================================================
//	死亡チェック(死亡フラグが立っているものを消す処理)
//===================================================================
void CScene::DeadCheck(CScene::PRIORITY pri)
{
	CScene* pScene = m_apTop[pri];
	if (pScene != NULL)
	{
		do
		{
			CScene* pSceneNext = pScene->m_pNext;		//いったん退避させる
			if (pScene->m_bDeath == true)
			{
				pScene->DeleteList(pri);
				//削除
				delete pScene;
				pScene = NULL;
			}
			pScene = pSceneNext;
		} while (pScene != NULL); //(pScene)← これと同じ条件式
	}
}

//===================================================================
//	優先順位(レイヤー)の変更
//===================================================================
void CScene::SetPriority(PRIORITY pri)
{
	CScene* pScene = this;	//いったん逃がす
	PRIORITY priority = pScene->GetPriority();

	pScene->DeleteList(priority);	//現在のリストから消す

	pScene->m_Priority = pri;					//優先順位変更

	pScene->AddList(pri);						//新しいリストに追加


}