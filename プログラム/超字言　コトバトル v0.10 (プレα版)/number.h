//=============================================================================
//
// �������� [number.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "scene2D.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CNumber
{
public:
	CNumber();
	~CNumber();

	HRESULT Init(D3DXVECTOR3 pos, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);
	void SetCol(D3DXCOLOR col);
	void SetSize(D3DXVECTOR2 size, D3DXVECTOR2 pos);

	D3DXVECTOR2 GetSize(void) { return m_size; }
	D3DXVECTOR2 GetPos(void) { return m_pos; }
	D3DXCOLOR GetCol(void) { return m_col; }
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	int							m_nType;				// �e�N�X�`���̔ԍ�
	D3DXVECTOR2					m_size;					// �T�C�Y
	D3DXVECTOR2					m_pos;					// �ʒu
	D3DXCOLOR					m_col;					// �F
};

class CBillNumber
{
public:
	CBillNumber();
	~CBillNumber();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);
	void SetCol(D3DXCOLOR col);
	void SetSize(D3DXVECTOR3 size);
	void SetPos(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXCOLOR GetCol(void) { return m_col; }

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	int							m_nType;				// �e�N�X�`���̔ԍ�
	D3DXVECTOR3					m_size;					// �T�C�Y
	D3DXVECTOR3					m_pos;					// �ʒu
	D3DXCOLOR					m_col;					// �F
	D3DXMATRIX					m_mtrxWorld;			// ���[���h�}�g���b�N�X

};
#endif