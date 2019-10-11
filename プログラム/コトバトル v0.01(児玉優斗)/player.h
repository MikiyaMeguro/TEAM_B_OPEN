//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : Kodama Yuto
//
//	クラスの概要
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "charactor.h"
#include "scene.h"

//class CScene3D;
class CSceneX;

class CPlayer : public CScene
{
public:
	CPlayer(int nPriority = 3);
	~CPlayer();

	static CPlayer* Create(void);

	void Set(D3DXVECTOR3 pos,CCharaBase::CHARACTOR_MOVE_TYPE type, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f));
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void DamageReaction(float fDamageValue) {};

	CCharaBase* GetCharaMover(void) { return m_pCharactorMove; };

	D3DXVECTOR3 GetPosition(void) { return GetCharaMover()->GetPosition(); };
	D3DXVECTOR3 GetRotation(void) { return GetCharaMover()->GetRotation(); };

	LPCSTR GetCameraName(void) { return m_ChildCameraName; };
	void SetCameraName(LPCSTR name) { m_ChildCameraName = name; };
private:
	C3DCharactor* m_pCharactorMove;			//キャラクターの移動管理

	CSceneX* m_pPlayerModel;				//プレイヤーのモデル(仮、後で↓の変数に差し替える)
	//std::vector<CCharaParts*> m_pVecPlayerParts;	//キャラクターの構成パーツ

	LPCSTR m_ChildCameraName;		//このプレイヤに追従するカメラの名前
};
#endif // !_PLAYER_H_
