//=============================================================================
//
// 管理クラス処理 [Manager.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "InputKeyboard.h"
#include "camera.h"
#include "CameraManager.h"
#include "light.h"
#include "DebugProc.h"
#include "texture.h"
#include "Command.h"
#include "sound.h"
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CRanking;
class CFade;
class CPause;
//==================================================================
//	クラスの定義
//==================================================================
//管理クラス
class CManager
{
public:
	typedef enum
	{
		DIR_UP,
		DIR_RIGHT,
		DIR_LEFT,
		DIR_DOWN,
		DIR_MAX
	}DIRECTION;

	typedef enum
	{//画面の定義
		MODE_NONE = 0,	//モード無(初期値)
		MODE_LOGO,		//ロゴ表示画面
		MODE_TITLE,		//タイトル画面
		MODE_SELECT,	//セレクト画面
		MODE_TUTORIAL,	//チュートリアル画面
		MODE_GAME,		//ゲーム画面
		MODE_RESULT,	//リザルト画面
		MODE_RANKING,	//ランキング画面
		MODE_OPTION,	//オプション画面
		MODE_MAX
	}MODE;

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance,HWND hWnd);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);


	static CRenderer*		GetRenderer(void) { return m_pRenderer; };
	static CInputKeyboard*  GetInputKeyboard(void) { return m_pInputKeyboard; };
	static CCameraManager*  GetCameraManager(void) { return m_pCameraManager; };
	static CLight*  GetLight(void) { return m_pLight; };
	static CDebugProc* GetDebugProc(void) { return m_pDebugProc; };
	static CFade* GetFade(void) { return m_pFade; };
	static CPause* GetPause(void) { return m_pPause; };
	static CSound* GetSound(void) { return m_pSound; };


	static CGame* GetGame(void) { return m_pGame; };
	static HRESULT SetMode(MODE mode);
	static LPCSTR GetModeName(void);

	static bool GetPauseFlag(void) { return m_bPauseFlag; };
	static void ChangePauseFlag(void) { m_bPauseFlag ^= 1; };		//フラグ反転

private:
	static CRenderer*		m_pRenderer;
	static CInputKeyboard*	m_pInputKeyboard;
	static CCameraManager* m_pCameraManager;
	static CLight*			m_pLight;
	static CDebugProc*		m_pDebugProc;
	static CPause*			m_pPause;
	static CSound*			m_pSound;

	static CFade*			m_pFade;
	//状態遷移用ポインタ
	static CTitle*			m_pTitle;			//タイトル
	static CTutorial*		m_pTutorial;		//チュートリアル
	static CGame*			m_pGame;			//ゲーム
	static CResult*			m_pResult;			//リザルト
	static CRanking*		m_pRanking;			//ランキング


	//その他変数
	static MODE m_Mode;		//現在の画面状態
	static MODE m_OrgMode;	//一つ前の画面状態

	static bool m_bPauseFlag;		//ポーズ処理
};

//==================================================================================================//
//     テンプレート定義(Scene系以外の生成)
//==================================================================================================//
template<class T> bool Create(T *&pObj)
{
	pObj = NULL;
	pObj = new T;
	if (pObj != NULL) { pObj->Init(); return true; }
	return false;
}

//==================================================================================================//
//     テンプレート定義(Scene系以外の解放)
//==================================================================================================//
template<class T> bool Release(T *&pObj)
{
	if (pObj != NULL)
	{
		pObj->Uninit();
		delete pObj;
		pObj = NULL;
		return true;
	}
	return false;
}

#endif // !_MANAGER_H_

