//=============================================================================
//
// �v���C���[�̑̃p�[�c���� [CharaParts.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v
//
//=============================================================================
#ifndef _CHARA_PARTS_H_
#define _CHARA_PARTS_H_

#include "main.h"
#include "sceneX.h"
//=============================================================================
//	�N���X��`
//=============================================================================
class CCharaParts : public CScene
{
public:
	CCharaParts();
	CCharaParts(int nPriority = 1);
	~CCharaParts();

	static CCharaParts* Create(void);

	void Set(LPCSTR ModelFile,D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXMATRIX* pParent);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos) { m_Pos = pos; };
	D3DXVECTOR3 GetPosition(void) { return m_Pos; };

	void SetRotation(D3DXVECTOR3 rot) { m_Rot = rot; };
	D3DXVECTOR3 GetRotation(void) { return m_Rot; };

	void SetParent(D3DXMATRIX* pParent) { m_pParent = pParent;};
	D3DXMATRIX* GetMatrix(void) { return &m_mtxWorld; };

private:
	LPDIRECT3DTEXTURE9*     m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH				m_pMesh;			// ���b�V�����i���_���j�ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	DWORD					m_nNumMat;			// �}�e���A�����̐�
	D3DXMATRIX				m_mtxWorld;			// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Rot;
	D3DXMATRIX* m_pParent;
};
#endif // !_CHARA_PARTS_H_
