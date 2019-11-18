//=============================================================================
//
// �����N���X [explosion.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "explosion.h"

#include "manager.h"

//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CExplosion3D::CExplosion3D(int pri, OBJTYPE type) : CMeshSphere(pri, type)
{

}
CExplosion3D::~CExplosion3D()
{

}

//=============================================================================
// ��������
//=============================================================================
CExplosion3D* CExplosion3D::Create(void)
{
	CExplosion3D* pExplosion = NULL;

	pExplosion = new CExplosion3D(1, OBJTYPE_PARTICLE);

	if (pExplosion != NULL)
	{
		pExplosion->Init();
	}

	return pExplosion;
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CExplosion3D::Set(D3DXVECTOR3 pos, float fSize, int nLife)
{
	CMeshSphere::Set(pos, "EXPLOSION", 20, 20, D3DXVECTOR3(fSize, fSize, fSize));

	m_fOrgSize = fSize;
	m_fSize = fSize;
	m_nLife = nLife;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CExplosion3D::Init(void)
{
	m_nCount = 0;
	CMeshSphere::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CExplosion3D::Uninit(void)
{
	CMeshSphere::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CExplosion3D::Update(void)
{
	m_fSize = m_fOrgSize + ((sinf(((float)m_nCount+1) / m_nLife)) * 100.0f);

	GetScale() = D3DXVECTOR3(m_fSize,m_fSize,m_fSize);
	CMeshSphere::Update();

	if (m_nCount > m_nLife)
	{
		Uninit();
	}
	m_nCount++;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CExplosion3D::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CMeshSphere::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}