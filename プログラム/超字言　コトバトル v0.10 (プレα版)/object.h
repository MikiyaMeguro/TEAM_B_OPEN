//=============================================================================
//
// オブジェクト処理 [object.h]
// Author : 横道 駿
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "scenex.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//========================================
// クラスの定義
//========================================
class CScene3D;

//=====================
// オブジェクトクラス
//=====================
class CObject : public CSceneX
{
public:
	typedef enum
	{	// ギミックの種類
		GIMMICK_NONE = 0,
		GIMMICK_MOYE_Y,
		GIMMICK_MAX
	}GIMMICKTYPE;

	typedef enum
	{	// ステージ変化時の変数
		REALTIME_NONE = 0,	// 何もなし
		REALTIME_INITPOS,	// 最初の位置から出現
		REALTIME_NOTMOVE,	// 指定時間まで動かない
		REALTIME_ENDPOS,	// 最後の位置に向けて移動
		REALTIME_MAX		// 総数
	}REALTIME;

	CObject();					// コンストラクタ
	~CObject();									// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos);				// 3Dオブジェクト初期化処理
	void Uninit(void);							// 3Dオブジェクト終了処理
	void Update(void);							// 3Dオブジェクト更新処理
	void Draw(void);							// 3Dオブジェクト描画処理

	static bool GetSwitch(void) { return m_bSwitch; }
	void SwitchBeltConveyor(bool bSwitch);					// スイッチの処理
	void BeltConveyor(D3DXVECTOR3 *pMove,bool bSwitch);			// 移動床の処理
	void KnockBack(D3DXVECTOR3 *pMove, int nID);			// ノックバック
	void AffectedLanding(D3DXVECTOR3 *pMove, int nID);		// モデルの着地時の影響

	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale,CSceneX::COLLISIONTYPE type, CLoad::MODEL mode , CObject::GIMMICKTYPE realtime);	// オブジェクトの生成
	static HRESULT Load(void);
	static void UnLoad(void);

	// 設定 取得の関数
	REALTIME GetRealTimeType(void) { return m_nRealTime; }
	static bool GetCreateFlag(void) { return m_bCreateFlag; }

private:
	void ModelMove(CSceneX::COLLISIONTYPE Type, D3DXVECTOR3 *pos, float fMove);
	void Rot(CSceneX::COLLISIONTYPE type);

	static bool m_bCreateFlag;					// 生成するフラグ
	void ModelMove(CSceneX::COLLISIONTYPE Type, D3DXVECTOR3 pos);
	void BGModelMove( D3DXVECTOR3 pos);

	void AnimationIcon(void);					// アイコンのアニメーション
	void IconCreate(CSceneX::COLLISIONTYPE Type, D3DXVECTOR3 pos);	// アイコンの生成
	void Vibration(D3DXVECTOR3 *Pos);			// 振動

	bool m_bMoveFlag;				// 移動フラグ
	REALTIME m_nRealTime;			// リアルタイムで移動するFlagの変数
	D3DXVECTOR3 m_posOld;			// 位置保管
	CScene3D *m_pIcon;
	float m_fMove;
	int m_nCntAnim;
	int m_nCntPattan;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_InitPos;
	int m_MoveState;
	int m_nCounter;
	GIMMICKTYPE m_nTypeGimmick;


	//	SWITCH
	static bool m_bSwitch;				//	スイッチ

};

#endif