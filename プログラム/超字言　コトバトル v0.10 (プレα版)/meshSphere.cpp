//=============================================================================
//
// �����b�V���N���X [meshSphere.cpp]
// Author : Kodama Yuto
//	���Ӂ@�����p�Ȃ̂ŒP�̂ł͎g��Ȃ����ƁI�I
//
//=============================================================================
#include "meshSphere.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CMeshSphere::CMeshSphere(int pri, OBJTYPE type) : CScene(pri,type)
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pTexture = NULL;
	m_VecNor = NULL;
}
CMeshSphere::~CMeshSphere()
{

}

//=============================================================================
// ��������
//=============================================================================
CMeshSphere* CMeshSphere::Create(void)
{
	CMeshSphere* pSphere = NULL;

	pSphere = new CMeshSphere(1, OBJTYPE_PARTICLE);

	if (pSphere != NULL)
	{
		pSphere->Init();
	}

	return pSphere;
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CMeshSphere::Set(D3DXVECTOR3 pos, LPCSTR Tag, int nMeshWidth, int nMeshHeight, D3DXVECTOR3 Size, D3DXCOLOR Col,D3DXVECTOR3 rot)
{
	//�f�o�C�X���擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�l�̐ݒ�
	m_pos = pos;
	m_rot = rot;
	m_Size = Size;
	m_Color = Col;

	m_nMeshWidth = nMeshWidth;
	m_nMeshHeight = nMeshHeight;

	// ���_��
	m_nVtxNum = (m_nMeshWidth + 1) * (m_nMeshHeight + 1);

	// �C���f�b�N�X��
	m_nIdxNum = (m_nMeshWidth + 1) * (m_nMeshHeight + 1)
		+ (2 * (m_nMeshHeight - 1))
		+ (m_nMeshWidth + 1) * (m_nMeshHeight - 1);

	// �|���S����
	m_nPolygonNum = m_nIdxNum - 2;
	if (m_VecNor != NULL)
	{
		delete[] m_VecNor;
		m_VecNor = NULL;
	}
	m_VecNor = new D3DXVECTOR3[m_nPolygonNum];

	//���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�̐ݒ�
	CreateVertex(pDevice);
	CreateIndex(pDevice);

	//�e�N�X�`���̐ݒ�
	m_pTexture = CTexture::GetTexture(Tag);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshSphere::Init(void)
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pTexture = NULL;
	m_VecNor = NULL;

	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_nMeshWidth = 2;
	m_nMeshHeight = 2;
	m_nVtxNum = 2;

	m_AnimTexUV = D3DXVECTOR2(0.0f,0.0f);
	m_nCntTexAnim = 2;
	m_nCount = 0;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshSphere::Uninit(void)
{
	//�@�����̍폜
	if (m_VecNor != NULL)
	{
		delete[] m_VecNor;
		m_VecNor = NULL;
	}
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}


	// �I�u�W�F�N�g�̉��
	Release();

}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshSphere::Update(void)
{
	m_nCount++;

	if (m_nCount % m_nCntTexAnim == 0)
	{
		// ���_���̐ݒ�
		VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^
							// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtxY = 0; nCntVtxY <= m_nMeshHeight; nCntVtxY++)
		{
			for (int nCntVtxX = 0; nCntVtxX < m_nMeshWidth; nCntVtxX++)
			{
				int nNum = (m_nMeshWidth * nCntVtxY) + nCntVtxX;
				pVtx[nNum].tex += m_AnimTexUV;

			}
		}

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshSphere::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�g��k���̔��f
	D3DXMatrixScaling(&mtxScale, m_Size.x, m_Size.y, m_Size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,
		m_nVtxNum, 0, m_nPolygonNum);

}

//=============================================================================
// ���_�o�b�t�@��������
//=============================================================================
void CMeshSphere::CreateVertex(LPDIRECT3DDEVICE9 pDev)
{
	//���ɍ���Ă����炢������폜
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// ���_�o�b�t�@�𐶐�
	pDev->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVtxNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^
						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtxY = 0; nCntVtxY <= m_nMeshHeight; nCntVtxY++)
	{
		for (int nCntVtxX = 0; nCntVtxX < m_nMeshWidth; nCntVtxX++)
		{
			int nNum = (m_nMeshWidth * nCntVtxY) + nCntVtxX;

			float fTheta = D3DXToRadian((180.0f * nCntVtxY) / m_nMeshHeight);
			float fPhi = D3DXToRadian((360.0f * nCntVtxX) / m_nMeshWidth);

			pVtx[nNum].pos = D3DXVECTOR3(sinf(fTheta) * sinf(fPhi),
				cosf(fTheta),
				sinf(fTheta) * cosf(fPhi));

			pVtx[nNum].tex =
				D3DXVECTOR2((nCntVtxX * (1.0f / (float)m_nMeshWidth)),
					(nCntVtxY * (1.0f / (float)m_nMeshHeight)));

			pVtx[nNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[nNum].col = m_Color;

		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�@���̍X�V
	UpdateNormal();
}

//=============================================================================
// �C���f�b�N�X�o�b�t�@��������
//=============================================================================
void CMeshSphere::CreateIndex(LPDIRECT3DDEVICE9 pDev)
{
	//���ɍ���Ă����炢������폜
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̐���
	pDev->CreateIndexBuffer(sizeof(WORD) * m_nIdxNum,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,										// 16�r�b�g�̃f�[�^���m��
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD *pIdx;	// �C���f�b�N�X�f�[�^�ւ̃|�C���^
	int nIdxCounter = 0;

				// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdxY = 0; nCntIdxY <= m_nMeshHeight; nCntIdxY++) {
		for (int nCntIdxX = 0; nCntIdxX < m_nMeshWidth; nCntIdxX++) {
			if (nCntIdxX == m_nMeshWidth) {
				pIdx[nIdxCounter++] = nCntIdxY * m_nMeshWidth;
				pIdx[nIdxCounter++] = (nCntIdxY + 1) * m_nMeshWidth;
			}
			else {
				pIdx[nIdxCounter++] = (nCntIdxY * m_nMeshWidth) + nCntIdxX;
				pIdx[nIdxCounter++] = pIdx[nIdxCounter - 1] + m_nMeshWidth;
			}
		}
	}
	// �C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

}

//=============================================================================
// �@������
//=============================================================================
void CMeshSphere::UpdateNormal(void)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int nVecNum = 0;

	//�|���S���̖@���ݒ�
	D3DXVECTOR3 VecA, VecB;

	for (int nCntHeight = 0; nCntHeight <= m_nMeshHeight; nCntHeight++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		for (int nCntWidth = 0; nCntWidth < m_nMeshWidth; nCntWidth++)
		{
			int nNum = (m_nMeshWidth * nCntHeight) + nCntWidth;

			VecA = pVtx[nNum + (m_nMeshWidth + 2)].pos - pVtx[nNum].pos;
			VecB = pVtx[nNum + (m_nMeshWidth + 1)].pos - pVtx[nNum].pos;
			D3DXVec3Cross(&m_VecNor[nVecNum], &VecA, &VecB);

			D3DXVec3Normalize(&m_VecNor[nVecNum], &m_VecNor[nVecNum]);
			nVecNum++;

			VecA = pVtx[nNum + 1].pos - pVtx[nNum].pos;
			VecB = pVtx[nNum + (m_nMeshWidth + 2)].pos - pVtx[nNum].pos;
			D3DXVec3Cross(&m_VecNor[nVecNum], &VecA, &VecB);

			D3DXVec3Normalize(&m_VecNor[nVecNum], &m_VecNor[nVecNum]);
			nVecNum++;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();


	//���_���Ƃ̖@���ݒ�
	D3DXVECTOR3 VecC;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntHeight = 0; nCntHeight <= m_nMeshHeight; nCntHeight++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		for (int nCntWidth = 0; nCntWidth < m_nMeshWidth; nCntWidth++)
		{
			if (nCntWidth == 0)
			{
				if (nCntHeight == 0)
				{
					VecC = (m_VecNor[0] + m_VecNor[1]) / 2;
					D3DXVec3Normalize(&pVtx[0].nor, &VecC);
				}
				else if (nCntHeight == m_nMeshHeight)
				{
					VecC = m_VecNor[((m_nMeshWidth) * 2) * (m_nMeshHeight - 1)];
					D3DXVec3Normalize(&pVtx[(m_nMeshWidth + 1) * m_nMeshHeight].nor, &VecC);
				}
				else
				{
					int nA = (m_nMeshWidth * 2) * (nCntHeight - 1);
					VecC = (m_VecNor[nA] + m_VecNor[nA + (m_nMeshWidth * 2)] + m_VecNor[nA + (m_nMeshWidth * 2) + 1]) / 3;
					D3DXVec3Normalize(&pVtx[(m_nMeshWidth + 1) * nCntHeight].nor, &VecC);
				}
			}
			else if (nCntWidth == m_nMeshWidth)
			{
				if (nCntHeight == 0)
				{
					VecC = m_VecNor[(m_nMeshWidth * 2) - 1];
					D3DXVec3Normalize(&pVtx[m_nMeshWidth].nor, &VecC);
				}
				else if (nCntHeight == m_nMeshHeight)
				{
					VecC = (m_VecNor[(m_nMeshWidth * m_nMeshHeight * 2) - 2] + m_VecNor[(m_nMeshWidth * m_nMeshHeight * 2) - 1]) / 2;
					D3DXVec3Normalize(&pVtx[((m_nMeshHeight + 1) * (m_nMeshWidth + 1)) - 1].nor, &VecC);

				}
				else
				{
					int nB = m_nMeshWidth * 2;
					VecC = (m_VecNor[(nB * nCntHeight) - 2] + m_VecNor[(nB * nCntHeight) - 1] + m_VecNor[(nB * (nCntHeight + 1)) - 1]) / 3;
					D3DXVec3Normalize(&pVtx[((m_nMeshWidth + 1) * (nCntHeight + 1)) - 1].nor, &VecC);
				}
			}
			else
			{
				if (nCntHeight == 0)
				{
					int nC = (nCntWidth * 2) - 1;
					VecC = (m_VecNor[nC] + m_VecNor[nC + 1] + m_VecNor[nC + 2]) / 3;
					D3DXVec3Normalize(&pVtx[nCntWidth].nor, &VecC);

				}
				else if (nCntHeight == m_nMeshHeight)
				{
					int nD = ((m_nMeshWidth * 2) * (m_nMeshHeight - 1)) + ((nCntWidth - 1) * 2);
					VecC = (m_VecNor[nD] + m_VecNor[nD + 1] + m_VecNor[nD + 2]) / 3;
					D3DXVec3Normalize(&pVtx[((m_nMeshWidth + 1) * m_nMeshHeight) + nCntWidth].nor, &VecC);
				}
				else
				{
					int nE = ((nCntWidth - 1) * 2) + ((m_nMeshWidth * 2) * (nCntHeight - 1));
					int nF = nE + ((m_nMeshWidth) * 2) + 1;
					VecC = (m_VecNor[nE] + m_VecNor[nE + 1] + m_VecNor[nE + 2] +
						m_VecNor[nF] + m_VecNor[nF + 1] + m_VecNor[nF + 2]) / 6;
					D3DXVec3Normalize(&pVtx[nCntWidth + ((m_nMeshWidth + 1) * nCntHeight)].nor, &VecC);

				}
			}
		}
	}


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();


}