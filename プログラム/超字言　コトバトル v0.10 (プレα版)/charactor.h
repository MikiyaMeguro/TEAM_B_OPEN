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


class CWaypoint;

class CPlayer;

class CCharaBase
{
public:
	typedef enum
	{
		MOVETYPE_PLAYER_INPUT,		//プレイヤーの操作
		MOVETYPE_NPC_AI,			//NPCのAIの操作
		MOVETYPE_RANKING_CHARA,		//ランキングのキャラ
		MOVETYPE_MAX
	}CHARACTOR_MOVE_TYPE;

	typedef enum
	{
		THINK_NONE,				//何も考えてない
		THINK_WORD,				//文字を考える
		THINK_SIGHT,			//敵が見えたとき
		THINK_MISSING,			//敵を見失ったとき
		THINK_HAVEBULLET,		//弾を持っているとき
		THINK_NOTBULLET,		//弾を持ってないとき
		THINK_PICKUP,			//弾を拾いに行く
		THINK_ENEMY_HAVEBULLET,	//敵が弾を持っているとき
		THINK_ENEMY_NOBULLET,	//敵が弾を持ってないとき
		THINK_ESCAPE,			//逃げる
		THINK_DODGE,			//かわす
		THINK_ATTACK,			//攻撃をするとき
		THINK_NEAR_ENEMY,		//近い
		THINK_FUR_ENEMY,		//遠い
		THINK_MOVE,				//移動
		THINK_ROTATION,			//回転
		THINK_PATROL,			//巡回
		THINK_HOMING,			//追いかける
		THINK_WATCH,			//見る
		THINK_WAYPOINTMOVE,		//経路情報
		THINK_WAYPOINTROUTE,	//最短の道探し
		THINK_MAX
	}CPU_THINK;

	typedef enum
	{
		CPU_MOVE_FRONT,			//前へ移動
		CPU_MOVE_RIGHT,			//右へ移動
		CPU_MOVE_LEFT,			//左へ移動
		CPU_MOVE_BACK,			//後ろへ移動
		CPU_MOVE_PATROL,		//巡回
		CPU_MOVE_NONE,			//移動していない
		CPU_MOVE_MAX
	}CPU_MOVE;

	typedef enum
	{
		CPU_ROTATION_RIGHT,			//右へ回転
		CPU_ROTATION_LEFT,			//左へ回転
		CPU_ROTATION_BACK,			//後ろへ回転
		CPU_ROTATION_MAX
	}CPU_ROTATION;

	typedef enum
	{
		CPU_NODE_NONE,			//何もしていない
		CPU_NODE_RUN,			//実行中
		CPU_NODE_SUCCESS,		//成功した
		CPU_NODE_FAILURE,		//失敗した
		CPU_NODE_MAX
	}CPU_NODE;

	typedef enum
	{
		CPU_TYPE_NONE,			//特になし
		CPU_TYPE_PATROL,		//巡回型
		CPU_TYPE_ESCAPE,		//逃走
		CPU_TYPE_HOMING,		//追尾
		CPU_TYPE_MAX
	}CPU_TYPE;

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
	float&		GetStep(void) { return m_fStep; };
	float&		 GetMoveCoeffient(void) { return m_fMoveCoeffient; };
	float&		GetSpinCoeffient(void) { return m_fSpinCoeffient; };
	float&		GetMoveCofBlend(void) { return m_fCofMoveBlend; };

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
	float m_fStep;					//ステップ移動の移動量
	float m_fMoveCoeffient;			//移動の慣性
	float m_fSpinCoeffient;			//回転の慣性

	CHARACTOR_MOVE_TYPE m_type;		//移動タイプ

	CPlayer* m_pThisCharactor;		//このインスタンスを所持しているプレイヤー
public:
	CPU_THINK m_CpuThink;		//現在の考え
	CPU_THINK m_OldCpuThink;	//過去の考え
	CPU_MOVE m_CpuMove;			//行動
	CPU_ROTATION m_CpuRotation;	//回転
	CPU_NODE m_CpuNode;			//ノードの状態
	CPU_TYPE m_Type;
	D3DXVECTOR3 m_RespawnPos;	//出現位置
	CWaypoint *m_pWayPoint;		//経路情報
	float m_fCofMoveBlend;	//スティック角に応じた移動係数
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
	void CharaMove_CPU(void);
	void Think_CPU(void);		//考える
	void Action_CPU(void);		//行動
	void DiffAngle(float fDiffAngle);		//回転差分
	void Rotation_CPU(void);	//回転
	void Escape_CPU(void);		//逃避
	void Homing_CPU(void);		//追尾
	void Attack_CPU(void);		//攻撃
	void PickUP_CPU(void);		//文字拾う
	void HaveBullet_CPU(void);	//弾をもっている
	void NotBullet_CPU(void);	//弾をもっていない
	void NearOrFur_CPU(void);	//近いか遠いか
	void WayPointMove_CPU(void);	//経路情報移動
	void WayPointRoute_CPU(void);	//最短ルート移動

	void StepMove(D3DXVECTOR3& move,float& fRot);

	D3DXVECTOR3 m_CameraPosR;	//カメラの注視点決定に使う変数
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	//CPUで使うメンバ変数
	int m_nThinkTimer;			//考える時間
	int m_nActionTimer;			//行動している時間
	int m_nSameCnt;				//同じ行動を何度したか
	float m_fCompareRange;		//文字までの距離を比較する
	int m_PatrolTimer;			//巡回のタイマー
	bool m_bNear[4];			//近い敵のフラグ
	bool m_bWordNear;
	bool m_bJyougai;
	D3DXVECTOR3 *m_pWayPointPos;	//経路情報の位置情報ポインタ
	D3DXVECTOR3 m_MarkWayPoint;		//移動先の位置
	bool m_bGoal;					//移動先到着フラグ
	bool m_bSearch;					//移動先探索フラグ
	bool m_bNearWard;				//文字が近くにあるフラグ
	bool m_bBlock;					//移動先障害物フラグ
	int	m_nTargetWP;				//目標のマス番号
	D3DXVECTOR3 m_MarkWardPos;		//移動先の位置

	int nTestCnt = 0;
public:
	bool m_bFront;
};

#endif // !_CHARACTOR_H_
