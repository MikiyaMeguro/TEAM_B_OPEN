//=============================================================================
//
// �I�u�W�F�N�g���� [object.h]
// Author : ���� �x
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "scenex.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CObject : public CSceneX
{
public:
	CObject();					// �R���X�g���N�^
	~CObject();									// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos);				// 3D�I�u�W�F�N�g����������
	void Uninit(void);							// 3D�I�u�W�F�N�g�I������
	void Update(void);							// 3D�I�u�W�F�N�g�X�V����
	void Draw(void);							// 3D�I�u�W�F�N�g�`�揈��

	// �ړ����̏���
	void BeltConveyor(D3DXVECTOR3 *pMove);
	void KnockBack(D3DXVECTOR3 *pMove);
	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale,CSceneX::COLLISIONTYPE type, CLoad::MODEL model);	// �I�u�W�F�N�g�̐���
	static HRESULT Load(void);
	static void UnLoad(void);


private:
};

#endif