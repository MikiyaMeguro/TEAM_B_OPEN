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

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_MODELNUM (30)		//モデルの最大数
#define MAX_KEY			(30)		//キーの最大数
#define MAX_MOTION		(30)		//モーションの最大数
#define MOTION_BLENDTIME (8)		//モーションブレンド時の補間秒数
//=============================================================================
// 前方宣言
//=============================================================================
class CScene3D;
class CSceneX;
class CWordManager;

//=============================================================================
// クラスの定義
//=============================================================================
class CPlayer : public CScene
{
public:
	//キャラクタータイプ
	typedef enum
	{
		TYPE_BARANCE = 0,			//ノーマル
		TYPE_POWER,					//パワー
		TYPE_SPEED,					//スピード
		TYPE_REACH,					//リーチ
		TYPE_RANDOM,				//ランダム
		TYPE_MAX
	}PLAYER_TYPE;

	//体情報
	typedef enum
	{
		LOWER_BODY = 0,		//下半身
		UPPER_BODY,			//上半身
		BODY_MAX,
	}BODY;

	//モーション列挙(上半身)
	typedef enum
	{
		MOTION_UPPER_NONE = 0,				//モーション無し
		MOTION_UPPER_NEUTRAL,				//待機(弾無し)
		MOTION_UPPER_WALK,					//歩行(弾無し)
		MOTION_UPPER_SETUP_NEUTRAL,			//待機(弾有り)
		MOTION_UPPER_SETUP_WALK,			//歩行(弾有り)
		MOTION_UPPER_STEP,					//ステップ回避
		MOTION_UPPER_SHOT,					//弾を打つ
		MOTION_UPPER_DAMAGE,				//ダメージを受ける
		MOTION_UPPER_WINNER,				//一位の時
		MOTION_UPPER_LOSER,					//最下位の時
		MOTION_UPPER_MAX
	}MOTION_UPPER;

	//モーション列挙(下半身)
	typedef enum
	{
		MOTION_LOWER_NONE = 0,				//モーション無し
		MOTION_LOWER_NEUTRAL,				//待機(弾無し)
		MOTION_LOWER_WALK_FRONT,			//正面移動
		MOTION_LOWER_WALK_RIGHT,			//右移動
		MOTION_LOWER_WALK_LEFT,				//左移動
		MOTION_LOWER_STEP,					//ステップ回避
		MOTION_LOWER_SHOT,					//弾を打つ
		MOTION_LOWER_DAMAGE,				//ダメージを受ける
		MOTION_LOWER_WINNER,				//一位の時
		MOTION_LOWER_LOSER,					//最下位の時
		MOTION_LOWER_MAX
	}MOTION_LOWER;

	//モーション遷移時の情報
	typedef enum
	{
		STATE_NORMAL,		//モーションを通常遷移させる
		STATE_BLEND,		//モーションブレンドをかける
	}MOTION_STATE;

	//キーフレームごとの情報
	typedef struct
	{
		int nFrame;							//フレーム数
		D3DXVECTOR3 Pos[PLAYER_MODELNUM];	//位置
		D3DXVECTOR3 Rot[PLAYER_MODELNUM];	//向き

		//初期化用
		void operator()(void)
		{
			nFrame = 0;
			for (int nCntPlayer = 0; nCntPlayer < PLAYER_MODELNUM; nCntPlayer++)
			{
				Pos[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				Rot[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}KeyProperty;

	//モーション情報(
	typedef struct
	{
		int	  nLoop;								//ループするかどうか	:1ならループ
		int   nKeyNum;								//キー数
		KeyProperty key[MAX_KEY];					//キー情報

		//初期化用
		void operator()(void)
		{
			nLoop = 0;
			nKeyNum = 0;
			for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
			{
				key[nCntKey].nFrame = 0;
				for (int nCntPlayer = 0; nCntPlayer < PLAYER_MODELNUM; nCntPlayer++)
				{
					key[nCntKey].Pos[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					key[nCntKey].Rot[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
		}
	}MotionProperty;

	//キャラパーツの情報格納構造体
	typedef struct
	{
		int nIndex;				//パーツインデックス
		int nParent;			//パーツの親番号
		D3DXVECTOR3 pos;		//位置
		D3DXVECTOR3 rot;		//角度
		char FileName[256];		//ファイル名
	}PartsLoadInfo;

	//プレイヤーの情報格納構造体
	typedef struct
	{
		PartsLoadInfo info[PLAYER_MODELNUM];		//パーツ情報
		MotionProperty prop[MAX_MOTION];			//モーション情報
		int nPartsNum;								//パーツ数
		bool bLoad;									//ロードされたか
	}PlayerLoadState;

	//コンストラクタ&デストラクタ
	CPlayer(int nPriority = 3);
	~CPlayer();

	//基本メンバ関数
	static CPlayer* Create(void);

	void Set(D3DXVECTOR3 pos,CCharaBase::CHARACTOR_MOVE_TYPE MoveType, int nPlayerID, PLAYER_TYPE PlayerType,D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f));

	HRESULT ModelLoad(LPCSTR pFileName, PLAYER_TYPE type, BODY body,bool bReLoad = false);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	//各種変数取得&代入処理
	CCharaBase*		GetCharaMover(void)				{ return m_pCharactorMove; };
	D3DXVECTOR3		GetPosition(void)				{ return (GetCharaMover() != NULL) ? GetCharaMover()->GetPosition() : D3DXVECTOR3(0.0f,0.0f,0.0f); };//GetCharaMover()->GetPosition()
	D3DXVECTOR3		GetRotation(void)				{ return (GetCharaMover() != NULL) ? GetCharaMover()->GetRotation() : D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	};
	int				GetID(void)						{ return m_nID; };
	LPCSTR			GetCameraName(void)				{ return m_ChildCameraName; };
	void			SetCameraName(LPCSTR name)		{ m_ChildCameraName = name; };
	void			SetTransTime(int nTime)			{ m_nCntTransTime = nTime; };
	CWordManager*   GetWordManager(void)			{ return m_pWordManager; }
	void			SetbSetupBullet(bool bBullet)	{ m_bSetupBullet = bBullet; };
	bool			GetbSetupBullet(void)			{ return m_bSetupBullet; };	//弾が撃てる状態の判定用
	void			SetOldPosition(D3DXVECTOR3 pos) { m_posOld = pos; }
	D3DXVECTOR3		GetOldPosition(void)			{ return m_posOld; };
	C3DCharactor*   GetLockOnCharactor(void)		{ return m_pLockOnCharactor;};
	D3DXVECTOR3     GetBulletMuzzle(void);
	bool			GetVision(int nPlayer)			{ return m_bVision[nPlayer]; };
	void			SetVision(int nPlayer, bool Vision) { m_bVision[nPlayer] = Vision; };
	bool			GetStealth(void)				{ return m_bStealth; };
	void			SetStealth(bool bStealth)		{  m_bStealth = bStealth; };
	CCharaBase::CHARACTOR_MOVE_TYPE GetMovetype(void) { return m_pCharactorMove->GetMoveType(); }
	int				GetLandObjNumber(void)			{ return m_nObjNumber; };
	bool			GetbMachineGun(void)			{ return m_bMachineGun; };
	//モーション
	void		SetMotion(int motion, BODY body, MOTION_STATE state = STATE_BLEND);
	int			GetMotion(BODY body = BODY::LOWER_BODY) { return m_motion[body]; };

	PLAYER_TYPE GetPlayerType(void) { return m_PlayerType; }

	void SetPartsAlpha(float fAlpha);
private:
	bool			CollisionDamageObj(void);			//弾との当たり判定
	void			DamageReaction(float fDamageValue,D3DXVECTOR3 HitRotation);	//fDamageValue = ダメージ量 | HitRotation = 攻撃を受けた向き
	bool			CollisonObject(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);	// 当たり判定
	void			MotionUpdate(BODY body = BODY::LOWER_BODY);			//モーション更新
	int				GetNearPlayer(void);		//近いプレイヤーを取得
	void			PlayerAlpha(float fAlpha);
	void			BulletUI(void);				// 弾発射UI表示
	void			BulletUIUninit(void);		// 弾発射準備の終了

	static PlayerLoadState m_PlayerLoadState[TYPE_MAX][BODY_MAX];	//パーツ情報

	int m_nID;	//識別ID(0～3の間)
	PLAYER_TYPE m_PlayerType;
	LPCSTR m_ChildCameraName;								//このプレイヤに追従するカメラの名前
	C3DCharactor* m_pCharactorMove;							//キャラクターの移動管理
	CCharaParts* m_pPlayerParts[PLAYER_MODELNUM][BODY_MAX];	//キャラクターの構成パーツ

	bool m_bLand;											// モデルに乗っているかどうか
	D3DXVECTOR3 m_posOld;									//前フレームの座標
	int m_nCntTransTime;									//無敵時間
	CWordManager *m_pWordManager;							//文字管理クラスのポインタ

	bool m_bSetupBullet;									//弾が撃てる状態の判定用
	bool m_bAssist;											//エイムアシストのフラグ
	C3DCharactor* m_pLockOnCharactor;						//ロックオンしているキャラクターの情報
	bool m_bStealth;										//ステルス状態
	bool m_bVision[4];										//見えているかどうか
	int	 m_nStealthTimer;									//見えている時間をカウント
	int  m_nObjNumber;										//今いるオブジェクトの番号
	D3DXVECTOR3 m_BulletRot;								//弾発射方向保持
	int m_nMachineGunTime;									//マシンガン発射時間
	bool m_bMachineGun;										//マシンガンフラグ
	D3DXVECTOR3 m_MachineGunPos;							//マシンガン発射位置
	CScene3D	*m_pBulletUI;								//弾のUI

	/* Motion */
	MotionProperty m_propMotion[MOTION_UPPER_MAX][BODY_MAX];			//モーション情報
	int m_motion[BODY_MAX];												//現在のモーション
	int m_OldMotion[BODY_MAX];											//一つ前のモーション
	int m_Mstate[BODY_MAX];												//モーションの状態
	int m_nCntFlame[BODY_MAX];											//フレーム用カウンタ
	int m_nCntKey[BODY_MAX];											//キー用カウンタ
	int m_nCntBlendMotion[BODY_MAX];									//モーションブレンド用のカウンタ
};

#endif // !_PLAYER_H_
