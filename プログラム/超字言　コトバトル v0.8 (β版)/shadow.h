//=============================================================================
//
// 影の処理 [Shadow.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define MAX_SHADOW	(2)

//*********************************************************************
//影のクラスの定義
//*********************************************************************
class CShadow : public  CScene3D//派生クラス
{
public:
	CShadow();
	~CShadow();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CShadow *Create(D3DXVECTOR3 pos, float fWidth, float fDepth);
	//メンバ変数
private:
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff = NULL;	//頂点バッファへのポインタ
	float								m_Height;
	D3DXVECTOR3							m_pos;							//位置
	D3DXVECTOR3							m_rot;							//向き
	D3DXCOLOR							m_col;
	D3DXMATRIX							m_mtxWorld;						//ワールドマトリックス
	float								m_fWidth, m_fDepth;				//幅　奥行き
};

#endif