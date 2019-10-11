//=============================================================================
//
// オブジェクト処理 [scene.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
//===================================================================
//	マクロ定義
//===================================================================
#define NUM_PRIORITY (8)	//レイヤー数

//===================================================================
//	クラスの定義
//===================================================================
class CScene
{
public:
	//オブジェクトの種類列挙
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_2D,
		OBJTYPE_3D,
		OBJTYPE_XFILE,
		OBJTYPE_BILLBOARD,
		OBJTYPE_FADE,
		OBJTYPE_BAGGAGE,
		OBJTYPE_MAX
	}OBJTYPE;

	typedef enum
	{
		PRIORITY_1,
		PRIORITY_2,
		PRIORITY_3,
		PRIORITY_4,
		PRIORITY_5,
		PRIORITY_6,
		PRIORITY_7,
		PRIORITY_8,
		PRIORITY_MAX
	}PRIORITY;	//レイヤー番号(数字が小さい順に処理される)

	CScene() {};
	CScene(PRIORITY pri = PRIORITY_3,OBJTYPE type = OBJTYPE_NONE);

	virtual ~CScene() {}

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(bool bFadeRelease);			//一括終了

	static void UpdateAll(void);			//一括更新
	static void DrawAll(void);				//一括描画
	static void DeadCheck(PRIORITY pri);	//死亡フラグチェック

	void AddList(PRIORITY pri);				//リストに追加
	void DeleteList(PRIORITY pri);			//リストから削除

	static CScene* GetTop(PRIORITY pri) { return m_apTop[pri]; };
	CScene* GetNext(void) { return m_pNext; };

	void	 SetPriority(PRIORITY pri);
	PRIORITY GetPriority(void) { return m_Priority; };

	void		SetObjType(OBJTYPE type) { m_objType = type; };
	OBJTYPE		GetObjType(void) { return m_objType; };

private:
	static CScene* m_apTop[PRIORITY_MAX];
	static CScene* m_apCur[PRIORITY_MAX];
	CScene* m_pPrev;
	CScene* m_pNext;

	bool m_bDeath;
protected:
	void Release(void);						//削除

	static int	   m_nNumAll[PRIORITY_MAX];	//オブジェクト数(優先順位別)
	int			m_nCount = 0;				//カウンタ
	PRIORITY	   m_Priority;				//優先順位(レイヤー番号)
	OBJTYPE m_objType;						//オブジェクトの種類
};

//==================================================================================================//
//     テンプレート(Scene系のオブジェクトの生成)
//==================================================================================================//
template<class T> T* SceneCreate(T *&pScene, CScene::PRIORITY Priority)
{
	pScene = NULL;
	pScene = new T(Priority);
	if (pScene != NULL) { pScene->Init(); return pScene; }

	return NULL;
}


#endif // !_SCENE_H_

