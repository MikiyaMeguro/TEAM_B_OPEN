//=============================================================================
//
// �����N���X [explosion.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v:
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "meshSphere.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TUBE_EFFECT_NUM (3)	//���G�t�F�N�g�̐�

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CExplosion3D : public CMeshSphere
{
public:
	CExplosion3D();
	CExplosion3D(int pri = 1, OBJTYPE type = OBJTYPE_SCENE3D);
	~CExplosion3D();

	static CExplosion3D* Create(void);
	void Set(D3DXVECTOR3 pos, float fStartSize, float fDestSize, int nLife, float fAnimSpeed,LPCSTR Tag = "EXPLOSION");

	void SetEX(D3DXVECTOR3 pos,float fStartSize,float fDestSize,int nLife,float fAnimSpeed,
		D3DXVECTOR3 rot,D3DXCOLOR col,LPCSTR Tag,int nMesh,int nExpandTime,
		D3DXVECTOR3 spinSpeed = D3DXVECTOR3(0.0f,0.0f,0.0f));

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);



	bool Collision(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld);

	void SetPosition(D3DXVECTOR3 pos) { CMeshSphere::GetPosition() = pos; };
	void SetRotation(D3DXVECTOR3 rot) { CMeshSphere::GetRotation() = rot; };
	void SetColor(D3DXCOLOR col) { CMeshSphere::SetColor(col); };

	void SetSpinSpeed(D3DXVECTOR3 spinspeed) { m_spinSpeed = spinspeed; };
private:
	void IsNotDup(bool bDup) { m_bNotDup = bDup; };
	float m_fSize;		//�T�C�Y
	float m_fDestSize;	//�ڕW�̃T�C�Y
	int m_nLife;		//�̗�

	int m_nExpandTime;	//�g��Ɏg������
	bool m_bNotDup;		//�d�˂ĕ\�����邩

	D3DXVECTOR3 m_spinSpeed;//��]���x
};

#endif // !_EXPLOSION_H_
