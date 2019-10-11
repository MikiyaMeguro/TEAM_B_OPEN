//=============================================================================
//
// オブジェクト配置処理 [SetObject.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _SETOBJECT_H_
#define _SETOBJECT_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CSceneX;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MATTEX	(20)

//*********************************************************************
//プレイヤークラスの定義
//*********************************************************************
class CSetObject : public CScene //派生クラス
{
public:
	//モデルの種類
	typedef enum
	{
		MODELTYPE_BOX000 = 0,	//BOX
		MODELTYPE_MAX,			//最大数
	}MODELTYPE;

	CSetObject();
	~CSetObject();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CSetObject *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void UnLoad(void);
	D3DXVECTOR3 GetPos(void);

	static void SaveFile(void);
	static void LoadFile(void);

	static char *ReadLine(FILE *pFile, char *pDst);	//1行読み込み
	static char *GetLineTop(char *pStr);			//行の先頭を取得
	static int  PopString(char *pStr, char *pDest);	//行の最後を切り捨て


private:
	//メンバ変数
	D3DXVECTOR3					m_pos;				//位置
	D3DXVECTOR3					m_posold;			//前回の位置
	D3DXVECTOR3					m_move;				//移動量
	D3DXVECTOR3					m_ModelMove;		//移動の仕方
	D3DXVECTOR3					m_rot;				//向き
	D3DXMATRIX					m_mtxWorld;			//ワールドマトリックス
	MODELTYPE					m_Type;				//タイプ
	int							m_nType;			//タイプint型
	static int					m_nMaxModel;
	bool						m_bBillboard;		//


	int							m_nRange;			//削除の範囲

	float						m_fDestAngle;		//角度
	float						m_fDiffAngle;		//差分

	static LPD3DXMESH			m_pMesh[MODELTYPE_MAX];			//メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMat[MODELTYPE_MAX];		//マテリアル情報へのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture[MODELTYPE_MAX];		//テクスチャへのポインタ
	static DWORD				m_nNumMat[MODELTYPE_MAX];		//マテリアル情報の数

	int							m_nCount;						//カウンター
	int							m_nCollision;					//当たり判定のONOFF
	static char					m_aFileName[MODELTYPE_MAX][256];		//ファイルの名前
public:
	CSceneX						*m_pObject;
};

#endif