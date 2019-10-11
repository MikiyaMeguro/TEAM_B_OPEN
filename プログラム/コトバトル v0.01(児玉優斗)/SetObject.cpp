//---------------------------------------------------------------------
//	�I�u�W�F�N�g�z�u����(SetObject.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "SetObject.h"
#include "game.h"
#include "fade.h"
#include "sceneX.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_SPEED     (5.0f)
#define MODEL_DEPTH     (50.0f)

#define PLAYER_DEPTH	(15)		// �v���C���[�̕������p
#define PLAYER_HEIGHT	(50.0f)		// �v���C���[�̔w�̍���

#define FILE_NAME0				("data\\TEXT\\SetModel.txt")

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPD3DXMESH					CSetObject::m_pMesh[MODELTYPE_MAX] = {};
LPD3DXBUFFER				CSetObject::m_pBuffMat[MODELTYPE_MAX] = {};
LPDIRECT3DTEXTURE9			CSetObject::m_pTexture[MODELTYPE_MAX] = {};
DWORD						CSetObject::m_nNumMat[MODELTYPE_MAX] = {};
int							CSetObject::m_nMaxModel = 0;
char						CSetObject::m_aFileName[MODELTYPE_MAX][256] = { NULL };


//--------------------------------------------
//�I�u�W�F�N�g�N���X �R���X�g���N�^
//--------------------------------------------
CSetObject::CSetObject() : CScene(3, CScene::OBJTYPE_SCENEX)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//�ʒu
	m_posold = D3DXVECTOR3(0, 0, 0);				//�O��̈ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					//�ړ���
	m_ModelMove = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);					//����
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_nCollision = 0;
	m_nCount = 0;
	m_Type = CSetObject::MODELTYPE_BOX000;
	m_nType = 0;
	m_bBillboard = false;
	m_nRange = 0;
	//m_nMaxModel = 0;
	m_pObject = NULL;
}

//--------------------------------------------
//�I�u�W�F�N�g�N���X �f�X�g���N�^
//--------------------------------------------
CSetObject::~CSetObject()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CSetObject *CSetObject::Create(D3DXVECTOR3 pos)
{
	//�I�u�W�F�N�g�|�C���^
	CSetObject *pObjectBG;
	pObjectBG = new CSetObject;
	//�����l���������� pos���
	pObjectBG->m_pos = pos;
	//�I�u�W�F�N�g�̏�����
	pObjectBG->Init();
	//�I�u�W�F�N�g�̏���Ԃ�
	return pObjectBG;
}

//=============================================================================
// �I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CSetObject::Init()
{
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_SCENEX);

	m_rot = D3DXVECTOR3(0, D3DX_PI * 0.0f, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;
	m_nRange = (int)MODEL_DEPTH;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	////���f���𐶐�	�I�t�Z�b�g�ݒ�
	//m_pObject = CSceneObject::Create(m_pos, m_rot);
	////���f�������蓖��
	//m_pObject->BindModel(m_nNumMat[m_Type], m_pMesh[m_Type], m_pBuffMat[m_Type]);
	////���f���̐e���w��
	//m_pObject->SetParent(NULL);
	////�ʒu�ݒ�
	//m_pObject->Setpos(m_pos);
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CSetObject::Uninit(void)
{
	//����������(�I�u�W�F�N�g��j��)
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CSetObject::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	if (pInput->GetTrigger(DIK_RSHIFT) == true)
	{	//�t�@�C���Z�[�u
		SaveFile();
	}
	else if (pInput->GetTrigger(DIK_RCONTROL) == true)
	{	//�t�@�C�����[�h
		LoadFile();
	}

#if 0

	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�J�������擾
	CCamera *pCamera = CGame::GetCamera();
	//�ߋ��̈ʒu��ݒ�
	m_posold = m_pos;

	// �ړ��ʂ̏�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�����̑��
	D3DXVECTOR3 rot = m_pObject->GetRot();

	//�C�ӂ̃L�[A
	if (pInput->GetPress(DIK_A) == true)
	{

		if (pInput->GetPress(DIK_W) == true)
		{//����ړ�
		 //���f���̈ړ�	���f���̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.75f) * MODEL_SPEED;
			m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.75f) * MODEL_SPEED;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.75f);
		}
		else if (pInput->GetPress(DIK_S) == true)
		{//�����ړ�
		 //���f���̈ړ�	���f���̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.25f) * MODEL_SPEED;
			m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.25f) * MODEL_SPEED;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.25f);
		}
		else
		{	//���f���̈ړ�	���f���̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f) * MODEL_SPEED;
			m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f) * MODEL_SPEED;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f);
		}
	}
	//�C�ӂ̃L�[D
	else if (pInput->GetPress(DIK_D) == true)
	{
		if (pInput->GetPress(DIK_W) == true)
		{//�E��ړ�
		 //���f���̈ړ�	���f���̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.75f) * MODEL_SPEED;
			m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.75f) * MODEL_SPEED;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.75f);
		}
		else if (pInput->GetPress(DIK_S) == true)
		{//�E���ړ�
		 //���f���̈ړ�	���f���̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.25f) * MODEL_SPEED;
			m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.25f) * MODEL_SPEED;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.25f);
		}
		else
		{	//���f���̈ړ�	���f���̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f) * MODEL_SPEED;
			m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f) * MODEL_SPEED;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f);
		}
	}
	//�C�ӂ̃L�[W
	else if (pInput->GetPress(DIK_W) == true)
	{	//���f���̈ړ�	���f���̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
		m_pos.x += sinf(pCamera->GetCamera().rotCamera.y) * MODEL_SPEED;
		m_pos.z += cosf(pCamera->GetCamera().rotCamera.y) * MODEL_SPEED;
		m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 1.0f);

	}
	//�C�ӂ̃L�[S
	else if (pInput->GetPress(DIK_S) == true)
	{
		//���f���̈ړ�	���f���̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
		m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y) * MODEL_SPEED;
		m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y) * MODEL_SPEED;
		m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.0f);
	}

	if (pInput->GetTrigger(DIK_1) == true)
	{
		//���f����؂�ւ�
		m_nType -= 1;

		//3D�I�u�W�F�N�g�ƃr���{�[�h�̐؂�ւ�
		if (m_nType == m_nMaxModel)
		{
			m_bBillboard = false;
			m_pBBItem->GetpBillBoard()->bDrawSet(m_bBillboard);
		}
		//0�ȉ��Ȃ�Ō�̃��f����
		if (m_nType < 0)
		{
			m_nType = m_nMaxModel;
			m_bBillboard = true;
			m_pBBItem->GetpBillBoard()->bDrawSet(m_bBillboard);
		}
		if (m_bBillboard == false)
		{	//�r���{�[�h�ł͂Ȃ��Ƃ�
			//���f�������蓖��
			m_pObject->BindModel(m_nNumMat[m_nType], m_pMesh[m_nType], m_pBuffMat[m_nType]);
		}
	}
	else if (pInput->GetTrigger(DIK_2) == true)
	{
		m_nType += 1;
		if (m_nType == m_nMaxModel)
		{
			m_bBillboard = true;
			m_pBBItem->GetpBillBoard()->bDrawSet(m_bBillboard);
		}

		//���f���ő吔�ȏ�Ȃ�0�Ԗڂ̃��f����
		if (m_nType > m_nMaxModel)
		{
			m_nType = 0;
			m_bBillboard = false;
			m_pBBItem->GetpBillBoard()->bDrawSet(m_bBillboard);
		}

		if (m_bBillboard == false)
		{	//�r���{�[�h�ł͂Ȃ��Ƃ�
			//���f�������蓖��
			m_pObject->BindModel(m_nNumMat[m_nType], m_pMesh[m_nType], m_pBuffMat[m_nType]);
		}
	}

	if (pInput->GetTrigger(DIK_RETURN) == true)
	{
		CObjectBG::Create(m_pos, m_rot, D3DXVECTOR3(0.0f, 0.0f, 0.0f)
			, (CObjectBG::MODELTYPE)m_nType, CObjectBG::MOVETYPE_NONE, 1);
	}

	if (pInput->GetTrigger(DIK_BACKSPACE) == true)
	{
		CScene *pScene;
		//�v���C�I���e�B�[�`�F�b�N
		pScene = CScene::GetTop(3);

		//NULL�`�F�b�N
		while (pScene != NULL)
		{
			//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
			CScene *pSceneNext = pScene->GetNext();
			if (pScene->GetDeath() == false)
			{
				//�^�C�v���I�u�W�F�N�g��������
				if (pScene->GetObjType() == OBJTYPE_BGMODEL)
				{
					D3DXVECTOR3 ModelPos;
					ModelPos = ((CObjectBG*)pScene)->GetPos();

					if (m_pos.x + (float)m_nRange >= ModelPos.x && m_pos.x - (float)m_nRange <= ModelPos.x)
					{// Z�͈͓̔��ɂ���
						if (m_pos.z + (float)m_nRange >= ModelPos.z && m_pos.z - (float)m_nRange <= ModelPos.z)
						{// X�͈͓̔��ɂ���
							((CObjectBG*)pScene)->Uninit();
						}
					}
				}
			}
			//Next�Ɏ���Scene������
			pScene = pSceneNext;
		}
	}

	if (pInput->GetTrigger(DIK_RSHIFT) == true)
	{	//�t�@�C���Z�[�u
		SaveFile();
	}
	else if (pInput->GetTrigger(DIK_RCONTROL) == true)
	{	//�t�@�C�����[�h
		LoadFile();
	}
	//�폜�͈͊g��k��
	if (pInput->GetPress(DIK_0) == true)
	{
		m_nRange++;
	}
	else if (pInput->GetPress(DIK_9) == true)
	{
		if (m_nRange > 0)
		{
			m_nRange--;
		}
	}

	//�I�u�W�F�N�g�̉�]����
	if (pInput->GetPress(DIK_F) == true)
	{
		m_rot.y += 0.01f;
	}
	else if (pInput->GetPress(DIK_G) == true)
	{
		m_rot.y -= 0.01f;
	}
	else if (pInput->GetTrigger(DIK_H) == true)
	{
		m_rot.y += D3DX_PI / 2;
	}
	else if (pInput->GetTrigger(DIK_J) == true)
	{
		m_rot.y -= D3DX_PI / 2;
	}
	else if (pInput->GetTrigger(DIK_K) == true)
	{
		m_rot.y = 0;
	}

	//�ʒu�Ɖ�]�̍X�V
	m_pObject->Setpos(m_pos);
	m_pObject->Setrot(m_rot);
	//
	m_pBBItem->SetPosItem(m_pos);

#ifdef  _DEBUG
	CDebugProc::Print(1, " [������@]\n W,A,S,D�ňړ� F,G�Ń��f����] H,J��90�x��] K�ŉ�]���Z�b�g  \n");
	CDebugProc::Print(1, " 1,2�L�[�Ń��f���؂�ւ� ENTER�L�[�Ŕz�u BACKSPACE�L�[�Ŕ͈͍폜\n");
	CDebugProc::Print(1, " �EShift�ŕۑ� �ECONTROL�œǂݍ��� 0�L�[�Ŕ͈͑��� 9�L�[�Ŕ͈͌���\n\n");
	CDebugProc::Print(1, " �폜�͈�        : ( %d )\n", m_nRange);
	CDebugProc::Print(1, " ���f���̈ʒu    : ( %.1f ,%.1f ,%.1f )\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print(1, " ���f���̃^�C�v  : ( No.%d )\n", m_nType + 1);

#endif

#endif // 0
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CSetObject::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;

	////�r���{�[�h�ł͂Ȃ��Ƃ�
	//if (m_bBillboard == false)
	//{
	//	// ���[���h�}�g���b�N�X�̏�����
	//	D3DXMatrixIdentity(&m_mtxWorld);
	//	// ��]�𔽉f
	//	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//	// �ʒu�𔽉f
	//	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//	//�e�̕`�揈��
	//	D3DXMATRIX	mtxShadow;
	//	D3DXPLANE	planeField;
	//	D3DXVECTOR4 VecLight;
	//	D3DXVECTOR3 pos, normal;

	//	// ���C�g�𖳌��ɂ���
	//	pDevice->LightEnable(0, FALSE);
	//	pDevice->LightEnable(1, FALSE);
	//	pDevice->LightEnable(2, FALSE);
	//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//	//���Z����
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//	//�V���h�E�}�g���b�N�X�̏�����
	//	D3DXMatrixIdentity(&mtxShadow);
	//	//���C�g�̐ݒ�
	//	VecLight = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f);
	//	//�e�̈ʒu�ݒ�
	//	pos = D3DXVECTOR3(0.0f, 0.01f, 0.0f);
	//	//�@���̐ݒ�
	//	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//	//���ʂ��쐬
	//	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	//	//�e�}�g���b�N�X�̐ݒ�
	//	D3DXMatrixShadow(&mtxShadow, &VecLight, &planeField);
	//	//���[���h�}�g���b�N�X�Ɗ|�����킹��
	//	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);
	//	//���[���h�}�g���b�N�X�̐ݒ�
	//	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//	//if (m_pObject != NULL)
	//	//{
	//	//	m_pObject->Draw();
	//	//}
	//	//�����_�[�X�e�C�g�����ɖ߂�
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//	// ���C�g��L���ɂ���
	//	pDevice->LightEnable(0, TRUE);
	//	pDevice->LightEnable(1, TRUE);
	//	pDevice->LightEnable(2, TRUE);
	//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//	// ���[���h�}�g���b�N�X�̐ݒ�
	//	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	//	//if (m_pObject != NULL)
	//	//{
	//	//	m_pObject->Draw();
	//	//}
	//}
}

//=============================================================================
// �I�u�W�F�N�g�̈ʒu�ݒ�
//=============================================================================
void CSetObject::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CSetObject::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	//�t�@�C���ǂݍ��ݗp�ϐ�
	FILE *pFile;			//�t�@�C���|�C���^
	char *pStrcur;			//���݂̐擪�̕�����
	char aLine[256];		//������
	char aStr[256];			//�ꎞ�ۑ�������
	int nIndex = 0;			//���݂̃C���f�b�N�X
	int nWord = 0;			//�|�b�v�ŕԂ��ꂽ�l��ێ�
	int nNumModel = 0;		//���f���̐�
	char aFileName[MODELTYPE_MAX][256];	//���f���̃t�@�C����
	int nCntModel = 0;		//���f���J�E���g�p

							//�t�@�C�����J�� �ǂݍ���
	pFile = fopen(FILE_NAME0, "r");
	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		while (1)
		{
			//������̐擪��ݒ�
			pStrcur = ReadLine(pFile, &aLine[0]);
			//����������o��
			strcpy(aStr, pStrcur);

			//������̃f�[�^ ��r���镶���� ��r���镶����
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//���o��
				pStrcur += strlen("NUM_MODEL = ");
				//������̐擪��ݒ�
				strcpy(aStr, pStrcur);
				//�����񔲂��o��
				nNumModel = atoi(pStrcur);
				m_nMaxModel = nNumModel;
			}

			if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
			{
				//���o��
				pStrcur += strlen("MODEL_FILENAME = ");

				//�������ݒ�
				strcpy(aStr, pStrcur);

				//�K�v�ȕ�����̍Ō�̕����܂ł̕������𐔂���
				int nNullNum = PopString(pStrcur, &aStr[0]);

				//����������߂�
				strcpy(aStr, pStrcur);

				//�Ō�̕�����NULL����������
				aStr[nNullNum - 1] = '\0';

				//�Ώۂ̕����񂩂甲���o��
				strcpy(&aFileName[nCntModel][0], aStr);

				strcpy(&m_aFileName[nCntModel][0], &aFileName[nCntModel][0]);

				// X�t�@�C���̓ǂݍ���
				D3DXLoadMeshFromX(&aFileName[nCntModel][0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&m_pBuffMat[nCntModel], NULL, &m_nNumMat[nCntModel], &m_pMesh[nCntModel]);

				nCntModel++;
			}

			//�X�N���v�g�̏I���
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}
	//�t�@�C�������
	fclose(pFile);


	//�e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; nCnt < m_nMaxModel; nCnt++)
	{
		//�}�e���A����񂩂�e�N�X�`���̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMat[nCnt]->GetBufferPointer();

		//�}�e���A���̐���
		for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat[nCnt]; nCntMatTex++)
		{
			if (pMat[nCntMatTex].pTextureFilename != NULL)
			{
				// �e�N�X�`���̐ݒ�
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					pMat[nCntMatTex].pTextureFilename,	// �t�@�C���̖��O
					&m_pTexture[nCnt]);					// �e�N�X�`���ւ̃|�C���^
				//�F�̕ω�
				pMat[nCntMatTex].MatD3D.Diffuse.a = 0.6f;
			}
		}
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j������
//=============================================================================
void CSetObject::UnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nMaxModel; nCnt++)
	{
		// ���b�V���̊J��
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		// �}�e���A���̊J��
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}

		//�e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
//=============================================================================
// �I�u�W�F�N�g�̈ʒu
//=============================================================================
D3DXVECTOR3 CSetObject::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �I�u�W�F�N�g�̔z�u����ۑ�
//=============================================================================
void CSetObject::SaveFile(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�@�C��
//	FILE *pFile;
#if 0
	//��������
	pFile = fopen(FILE_NAME0, "w");
	//NULL�`�F�b�N
	if (pFile != NULL)
	{	//�t�@�C����������
		fprintf(pFile, "#============================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# [���f���z�u�c�[��]�X�N���v�g�t�@�C�� [%s]\n", FILE_NAME0);
		fprintf(pFile, "#  Author : MIKIYA MEGURO\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#============================================================\n");

		fprintf(pFile, "SCRIPT			# ���̍s�͐�Ώ����Ȃ����ƁI\n\n");

		fprintf(pFile, "#------------------------------------------------------------\n");
		fprintf(pFile, "#                      ���f���� \n");
		fprintf(pFile, "#------------------------------------------------------------\n");
		fprintf(pFile, "NUM_MODEL = %d\n\n", m_nMaxModel);




		fprintf(pFile, "#------------------------------------------------------------\n");
		fprintf(pFile, "#                      ���f���t�@�C����\n");
		fprintf(pFile, "#------------------------------------------------------------\n");

		//�e�N�X�`���̓ǂݍ���
		for (int nCnt = 0; nCnt < m_nMaxModel; nCnt++)
		{
			fprintf(pFile, "MODEL_FILENAME = %s\n", &m_aFileName[nCnt]);
		}

		fprintf(pFile, "\n#------------------------------------------------------------\n");
		fprintf(pFile, "#                      ���f���z�u��� \n");
		fprintf(pFile, "#------------------------------------------------------------\n\n");

		CScene *pScene;
		//�v���C�I���e�B�[�`�F�b�N
		pScene = CScene::GetTop(3);

		//NULL�`�F�b�N
		while (pScene != NULL)
		{
			//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
			CScene *pSceneNext = pScene->GetNext();
			if (pScene->GetDeath() == false)
			{
				//�^�C�v���I�u�W�F�N�g��������
				if (pScene->GetObjType() == OBJTYPE_BGMODEL)
				{
					D3DXVECTOR3 Pos;
					D3DXVECTOR3 Rot;
					int nType = 0;
					Pos = ((CObjectBG*)pScene)->GetPos();
					Rot = ((CObjectBG*)pScene)->GetRot();
					nType = ((CObjectBG*)pScene)->GetModelType();

					fprintf(pFile, "MODELSET \n");
					fprintf(pFile, "\tTYPE = %d\n", nType);
					fprintf(pFile, "\tPOS = %.1f %.1f %.1f\n", Pos.x, Pos.y, Pos.z);
					fprintf(pFile, "\tROT = %.1f %.1f %.1f\n", Rot.x, Rot.y, Rot.z);
					fprintf(pFile, "END_MODELSET\n\n");

				}
			}
			//Next�Ɏ���Scene������
			pScene = pSceneNext;
		}
		fprintf(pFile, "END_SCRIPT		# ���̍s�͐�Ώ����Ȃ����ƁI");
	}
	else
	{	//�t�@�C�����J���Ȃ�����
		//printf("�t�@�C�����J���܂���ł���\n");
	}
	//�t�@�C�������
	fclose(pFile);
#endif

#if 0
	////��������
	//pFile = fopen(FILE_NAME1, "wb");
	////NULL�`�F�b�N
	//if (pFile != NULL)
	//{	//�t�@�C���ǂݍ���
	//	//fwrite(&g_aHeght[0][0], sizeof(float), m_nSplitX * m_nSplitZ, pFile);
	//}
	//else
	//{	//�t�@�C�����J���Ȃ�����
	//	printf("�t�@�C�����J���܂���ł���\n");
	//}
	////�t�@�C�������
	//fclose(pFile);
#endif

}

//=============================================================================
// �I�u�W�F�N�g�̔z�u����ǂݍ���
//=============================================================================
void CSetObject::LoadFile(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�@�C���ǂݍ��ݗp�ϐ�
	FILE *pFile;			//�t�@�C���|�C���^
	char *pStrcur;			//���݂̐擪�̕�����
	char aLine[256];		//������
	char aStr[256];			//�ꎞ�ۑ�������
	int nIndex = 0;			//���݂̃C���f�b�N�X
	int nWord = 0;			//�|�b�v�ŕԂ��ꂽ�l��ێ�
	int nNumModel = 0;		//���f���̐�
	int nType = 0;			//���f���̎��
	D3DXVECTOR3 ModelPos;	//���f���̈ʒu
	D3DXVECTOR3 ModelRot;
	//�t�@�C�����J�� �ǂݍ���
	pFile = fopen(FILE_NAME0, "r");
	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		while (1)
		{
			//������̐擪��ݒ�
			pStrcur = ReadLine(pFile, &aLine[0]);
			//����������o��
			strcpy(aStr, pStrcur);

			//�I�u�W�F�N�g�ǂݍ���
			if (memcmp(pStrcur, "MODELSET", strlen("MODELSET")) == 0)
			{
				//���o��
				pStrcur += strlen("MODELSET");
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				//���
				if (memcmp(pStrcur, "TYPE = ", strlen("TYPE = ")) == 0)
				{
					//���o��
					pStrcur += strlen("TYPE = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);
					//�����񔲂��o��
					nType = atoi(pStrcur);
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//�ʒu
				if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
				{
					//���o��
					pStrcur += strlen("POS = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.X���
					ModelPos.x = (float)atof(pStrcur);
					//���������i�߂�
					pStrcur += nWord;

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Y���
					ModelPos.y = (float)atof(pStrcur);
					//���������i�߂�
					pStrcur += nWord;

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Z���
					ModelPos.z = (float)atof(pStrcur);
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//ROT��ǂݍ���
				if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
				{
					//���o��
					pStrcur += strlen("ROT = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					ModelRot.x = (float)atof(pStrcur);

					//���������i�߂�
					pStrcur += nWord;
					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					ModelRot.y = (float)atof(pStrcur);

					//���������i�߂�
					pStrcur += nWord;
					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					ModelRot.z = (float)atof(pStrcur);
				}
			}
			//���f���𐶐�
			if (memcmp(pStrcur, "END_MODELSET", strlen("END_MODELSET")) == 0)
			{
				//CObjectBG::Create(ModelPos, ModelRot, D3DXVECTOR3(0.0f, 0.0f, 0.0f)
				//	, (CObjectBG::MODELTYPE)nType, CObjectBG::MOVETYPE_NONE, 1);
				CSceneX::Create(ModelPos, (CLoad::MODEL)nType);
			}
			//�X�N���v�g�̏I���
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}

	//�t�@�C�������
	fclose(pFile);
}


//=============================================================================
//�@�t�@�C���ǂݍ��ݖ�������r��
//=============================================================================
char *CSetObject::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//�P�s���ǂݍ���
		fgets(&pDst[0], 256, pFile);

		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//�@�t�@�C���ǂݍ��ݐ擪��r��
//=============================================================================
char * CSetObject::GetLineTop(char * pStr)
{
	while (1)
	{
		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//�@��������Ԃ�
//=============================================================================
int CSetObject::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//���o��
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//���o��
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//���o��
			pStr = "\0";
			nWord += strlen("\t");
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//���o��
			nWord += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//������̐���Ԃ�
	return nWord;
}
