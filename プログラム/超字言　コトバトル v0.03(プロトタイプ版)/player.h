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
#include "sceneBillboard.h"
#include "CharaParts.h"


#define PLAYER_MODELNUM (20)

//class CScene3D;
class CSceneX;
class CWordManager;

class CPlayer : public CScene
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,			//ノーマル
		TYPE_POWER,					//パワー
		TYPE_SPEED,					//スピード
		TYPE_REACH,					//リーチ
	}PLAYER_TYPE;	//プレイヤーの操作タイプ

	typedef enum
	{
		MOTION_NEUTRAL = 0,		//待機(弾無し)
		MOTION_WALK,			//歩行(弾無し)
		MOTION_SETUP_NEUTRAL,	//待機(弾有り)
		MOTION_SETUP_WALK,		//歩行(弾有り)
		MOTION_STEP,			//ステップ回避
		MOTION_SHOT,			//弾を打つ
		MOTION_DAMAGE,			//ダメージを受ける
		MOTION_WINNER,			//一位の時
		MOTION_LOSER,			//最下位の時
		MOTION_MAX
	}MOTION;
	typedef enum
	{
		STATE_NORMAL,		//モーション再生状態
		STATE_BLEND,		//モーションブレンド状態
	}MOTION_STATE;

	typedef struct
	{
		int nFrame;							//フレーム数
		D3DXVECTOR3 Pos[PLAYER_MODELNUM];	//位置
		D3DXVECTOR3 Rot[PLAYER_MODELNUM];	//向き
	}KeyProperty;

	typedef struct
	{
		LPCSTR MotionName;							//モーション名
		int	  nLoop;								//ループするかどうか : -1 無限ループ | 0 ループなし
		int   nKeyNum;								//キー数
		std::vector<KeyProperty> vecKey;			//キー情報
	}MotionProperty;

	typedef struct
	{
		int nIndex;
		int nParent;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		char FileName[256];
	}PartsLoadInfo;

	CPlayer(int nPriority = 3);
	~CPlayer();

	static CPlayer* Create(void);

	void Set(D3DXVECTOR3 pos,CCharaBase::CHARACTOR_MOVE_TYPE type, int nPlayerID,D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f));

	HRESULT ModelLoad(LPCSTR pFileName);
	void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	CCharaBase* GetCharaMover(void) { return m_pCharactorMove; };

	D3DXVECTOR3 GetPosition(void) { return GetCharaMover()->GetPosition(); };
	D3DXVECTOR3 GetRotation(void) { return GetCharaMover()->GetRotation(); };
	int GetID(void) { return m_nID; };
	LPCSTR GetCameraName(void) { return m_ChildCameraName; };
	void SetCameraName(LPCSTR name) { m_ChildCameraName = name; };

	void SetTransTime(int nTime) { m_nCntTransTime = nTime; };
	CWordManager *GetWordManager(void) { return m_pWordManager; }				// 言葉管理クラスの取得


	void SetbSetupBullet(bool bBullet) { m_bSetupBullet = bBullet; };
	bool GetbSetupBullet(void) { return m_bSetupBullet; };	//弾が撃てる状態の判定用
private:
	bool CollisionBullet(void);
	void DamageReaction(float fDamageValue,D3DXVECTOR3 HitRotation);	//fDamageValue = ダメージ量 | HitRotation = 攻撃を受けた向き
	bool CollisonObject(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);	// 当たり判定


	C3DCharactor* m_pCharactorMove;			//キャラクターの移動管理
	int m_nID;	//識別ID(0～3の間)
	PLAYER_TYPE m_PlayerType;
	LPCSTR m_ChildCameraName;		//このプレイヤに追従するカメラの名前
	bool m_bLand;					// モデルに乗っているかどうか
	D3DXVECTOR3 m_posOld;
	int m_nCntTransTime;			//無敵時間

	CSceneX* m_pPlayerModel;							//プレイヤーのモデル(仮、後で↓の変数に差し替える)

	CCharaParts* m_pPlayerParts[PLAYER_MODELNUM];	//キャラクターの構成パーツ
	CWordManager *m_pWordManager;
	CSceneBillBoard *m_pPlayerNum;					// プレイヤー番号

	bool m_bSetupBullet;					//弾が撃てる状態の判定用
};
#endif // !_PLAYER_H_
