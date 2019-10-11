//=============================================================================
//
// キャラクター処理 [charactor.h]
// Author : Kodama Yuto
//
//	クラスの概要
//	・PositionやRotationなど、姿勢制御に使う変数を持ったクラス群
//	・クラス内で姿勢制御を行い、Get関数でそれらを取得する
//
//	C2DCharactor
//	・2Dのキャラクター用のクラス
//	・マトリックスを持たず、PositionとRotationで制御する
//
//	C3DCharactor
//	・3Dのキャラクター用のクラス
//	・PositionとRotationに加えて,マトリックスを使って姿勢制御を行う
//
//=============================================================================
#ifndef _CHARACTOR_H_
#define _CHARACTOR_H_

#include "scene.h"
class CPlayer;

class CCharaBase
{
public:
	typedef enum
	{
		MOVETYPE_PLAYER_INPUT,		//プレイヤーの操作
		MOVETYPE_NPC_AI,			//NPCのAIの操作
		MOVETYPE_MAX
	}CHARACTOR_MOVE_TYPE;

	CCharaBase() {};
	~CCharaBase() {};

	virtual void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHARACTOR_MOVE_TYPE type, CPlayer* pThis);

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;

	D3DXVECTOR3& GetPosition(void) { return m_pos; };
	D3DXVECTOR3& GetRotation(void) { return m_rot; };
	D3DXVECTOR3& GetMove(void) { return m_Move; };
	D3DXVECTOR3& GetSpin(void) { return m_Spin; };
	float&		 GetSpeed(void) { return m_fSpeed; };

	CHARACTOR_MOVE_TYPE GetMoveType(void) { return m_type; };

	void SetThisCharactor(CPlayer* pThis) { m_pThisCharactor = pThis; };

protected:
	CPlayer* GetThisCharactor(void) { return m_pThisCharactor; };
	int m_nCntStepCoolTime;		//ステップ移動のクールダウン時間測定用
private:
	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_rot;				//角度
	D3DXVECTOR3 m_Move;				//移動量
	D3DXVECTOR3 m_Spin;				//回転量
	float m_fSpeed;					//移動速度

	CHARACTOR_MOVE_TYPE m_type;		//移動タイプ

	CPlayer* m_pThisCharactor;		//このインスタンスを所持しているプレイヤー

};

class C2DCharactor : public CCharaBase
{
public:
	C2DCharactor() {};
	~C2DCharactor() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHARACTOR_MOVE_TYPE type, CPlayer* pThis) { CCharaBase::Set(pos, rot, type, pThis); };

	HRESULT Init(void);
	void Uninit(void) {};
	void Update(void);
private:
};

class C3DCharactor : public CCharaBase
{
public:
	C3DCharactor() {};
	~C3DCharactor() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHARACTOR_MOVE_TYPE type, CPlayer* pThis) { CCharaBase::Set(pos, rot, type, pThis); };

	HRESULT Init(void);
	void Uninit(void) {};
	void Update(void);

	D3DXVECTOR3 GetCameraPosR(void) { return m_CameraPosR; };
	D3DXMATRIX* GetMatrix(void) { return &m_mtxWorld; };
private:
	void CharaMove_Input(void);

	D3DXVECTOR3 m_CameraPosR;
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
};

#endif // !_CHARACTOR_H_
