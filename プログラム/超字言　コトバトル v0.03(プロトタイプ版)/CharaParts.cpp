//=============================================================================
//
// �v���C���[�̑̃p�[�c���� [CharaParts.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "CharaParts.h"
#include "manager.h"

//=============================================================================
//	�R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CCharaParts::CCharaParts(){
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = 0;
}
CCharaParts::~CCharaParts()
{

}

//=============================================================================
//	�ݒ菈��
//=============================================================================
void CCharaParts::Set(LPCSTR ModelFile, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXMATRIX* pParent)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pParent = pParent;
	m_Pos = pos;
	m_Rot = rot;

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(ModelFile,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	// �}�e���A����񂩂�e�N�X�`���������o��
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[m_nNumMat];
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];

	for (DWORD nCntMat = 0; nCntMat < m_nNumMat; nCntMat++)
	{// ���_���̐������J��Ԃ�
	 // �}�e���A������ǂݍ���
		pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

		// ����������������
		pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

		// �e�N�X�`������������
		m_pTexture[nCntMat] = NULL;

		// �e�N�X�`���̏���ǂݍ���
		if (pMat[nCntMat].pTextureFilename != NULL &&
			lstrlen(pMat[nCntMat].pTextureFilename) > 0)
		{// �e�N�X�`���̃t�@�C����������
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat]);
		}
	}
	delete[] pMatBuff;


}

//=============================================================================
//	����������
//=============================================================================
HRESULT CCharaParts::Init(void)
{
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = 0;

	return S_OK;
}
//=============================================================================
//	�I������
//=============================================================================
void CCharaParts::Uninit(void)
{
	// ���b�V���̉��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//�e�N�X�`���̊J��
	for (DWORD nCntMat = 0; nCntMat < m_nNumMat; nCntMat++)
	{
		if (m_pTexture[nCntMat] != NULL)
		{
			m_pTexture[nCntMat]->Release();
			m_pTexture[nCntMat] = NULL;
		}
	}
	delete m_pTexture;

	//�}�e���A���̉��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
//	�X�V����
//=============================================================================
void CCharaParts::Update(void)
{

}

//=============================================================================
//	�`�揈��
//=============================================================================
void CCharaParts::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�̃|�C���^

								// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_Rot.y,
		m_Rot.x,
		m_Rot.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_Pos.x,
		m_Pos.y,
		m_Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	if (m_pParent != NULL)
	{
		//�e�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld,
			m_pParent);
	}

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		/*�e�N�X�`���̐ݒ�*/
		pDevice->SetTexture(0, m_pTexture[nCntMat]);//�e�N�X�`���̐ݒ�(�g��Ȃ����NULL������)

													// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

}