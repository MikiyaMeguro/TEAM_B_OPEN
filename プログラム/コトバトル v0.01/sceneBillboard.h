//=============================================================================
//
// ビルボード処理 [sceneBillboard.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCENE_BILLBOARD_H_
#define _SCENE_BILLBOARD_H_

#include "scene.h"

//==================================================================
//	クラスの定義
//==================================================================
class CSceneBillboard : public CScene
{
public:

	CSceneBillboard();
	CSceneBillboard(CScene::PRIORITY pri);
	~CSceneBillboard();

	void Set(D3DXVECTOR3 pos,LPCSTR TexTag,
		D3DXVECTOR2 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);



	void        SetPosition(D3DXVECTOR3 pos);
	void        SetSize(D3DXVECTOR2 Size);
	D3DXVECTOR3 GetPosition(void) { return m_pos; };

	void		BindTexture(LPCSTR TexTag);


protected:

private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;			// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;						//ポリゴンの位置
	D3DXVECTOR3				m_rot;
	D3DXMATRIX				m_mtxWorld;					//ポリゴンのマトリックス
	D3DXVECTOR2				m_Size;
};
#endif //!_SCENE_BILLBOARD_H_