//=============================================================================
//
// マネージャ処理 [manager.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "sound.h"
#include "renderer.h"

#include "texture.h"
#include "Command.h"
//=============================================================================
// 前方宣言
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CCamera;
class CLight;
class CDebugProc;
class CMask;
class CFade;
class CGame;
class CTitle;
class CSelect;
class CResult;
class CUltimate;
class CCharacterMove;
class CInputXPad;
class CSound;
class CTutorial;
class CCharaSelect;
class CStageSelect;
class CCameraManager;
//=============================================================================
// マクロ
//=============================================================================
#define PLAYER_RIGHT		(DIK_D)
#define PLAYER_LEFT			(DIK_A)
#define PLAYER_A_BUTTON		(DIK_F)
#define PLAYER_B_BUTTON		(DIK_G)
#define PLAYER_C_BUTTON		(DIK_S)

#define ENEMY_RIGHT			(DIK_NUMPAD6)
#define ENEMY_LEFT			(DIK_NUMPAD4)
#define ENEMY_A_BUTTON		(DIK_ADD)
#define ENEMY_B_BUTTON		(DIK_NUMPADENTER)
#define ENEMY_C_BUTTON		(DIK_NUMPAD5)
#define PLAYER_C_BUTTON		(DIK_S)
#define MAX_SOUND			(3)
#define MAX_PLAYER			(4)
//=============================================================================
// マクロ(コントローラー)
//=============================================================================

//=============================================================================
// クラスの定義
//=============================================================================
//=====================
// マネージャクラス
//=====================
class CManager
{
public:

	typedef enum
	{//モードの構造体
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_SELECT,
		MODE_TUTORIAL,
		MODE_STAGESELECT,
		MODE_CHARASELECT,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	}MODE;

	CManager();		// コンストラクタ
	~CManager();	// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	//static CCamera *GetCamera(void);
	static CMask *GetMask(void);
	static CCharacterMove *GetCharacterMove(void);
	static CFade *GetFade(void) { return m_pFade; };
	static MODE GetMode(void) { return m_mode; };
	static void SetMode(MODE mode);
	static CGame *GetGame(void) { return m_pGame; }
	static CTitle *GetTitle(void) { return m_pTitle; }
	static CSelect *GetSelect(void) { return m_pSelect; }
	static CTutorial *GetTutorial(void) { return m_pTutorial; }
	static CCharaSelect *GetCharaSelect(void) { return m_pCharaSelect; }
	static CStageSelect *GetStageSelect(void) { return m_pStageSelect; }
	static CResult *GetResult(void) { return m_pResult; }
	static CInputXPad *GetXInput(int nID) { return m_pXInput[nID]; }
	static CSound *GetSound(int nNum);

	static CCameraManager* GetCameraManager(void) { return m_pCameraManager; };
private:
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	//static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CDebugProc *m_pDebugProc;

	static CMask *m_pMask;
	static CFade *m_pFade;
	static CCharacterMove *m_pCharacterMove;
	static CGame *m_pGame;
	static CTitle *m_pTitle;
	static CSelect *m_pSelect;
	static CTutorial *m_pTutorial;
	static CResult *m_pResult;
	static CCharaSelect *m_pCharaSelect;
	static CStageSelect *m_pStageSelect;

	static CCameraManager* m_pCameraManager;
	static CInputXPad *m_pXInput[MAX_PLAYER];
	static MODE m_mode;
	static CSound			*m_pSound[MAX_SOUND];	// サウンドのポインタ
};

//==================================================================================================//
//     テンプレート定義(Scene系以外の生成)
//==================================================================================================//
template<class T> bool ObjCreate(T *&pObj)
{
	pObj = NULL;
	pObj = new T;
	if (pObj != NULL) { pObj->Init(); return true; }
	return false;
}

//==================================================================================================//
//     テンプレート定義(Scene系以外の解放)
//==================================================================================================//
template<class T> bool ObjRelease(T *&pObj)
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

#endif