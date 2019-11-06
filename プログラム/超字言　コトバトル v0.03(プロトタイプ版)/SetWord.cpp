//---------------------------------------------------------------------
//	�����z�u����(SetWord.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "SetWord.h"
#include "game.h"
#include "fade.h"
#include "word.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME0				("data\\TEXT\\�@�B�X�e�[�W\\�����o���ʒu\\Machine_Stage_0.txt")

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------

//--------------------------------------------
//�I�u�W�F�N�g�N���X �R���X�g���N�^
//--------------------------------------------
CSetWord::CSetWord() : CScene(3, CScene::OBJTYPE_SETOBJECT)
{
	m_pWordPos = NULL;
	m_pWord = NULL;
}

//--------------------------------------------
//�I�u�W�F�N�g�N���X �f�X�g���N�^
//--------------------------------------------
CSetWord::~CSetWord()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CSetWord *CSetWord::Create()
{
	//�I�u�W�F�N�g�|�C���^
	CSetWord *pSetObject = NULL;
	if (pSetObject == NULL)
	{
		pSetObject = new CSetWord;
		if (pSetObject != NULL)
		{//�I�u�W�F�N�g�̏�����
			pSetObject->Init();
		}
	}
	//�I�u�W�F�N�g�̏���Ԃ�
	return pSetObject;
}

//=============================================================================
// �I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CSetWord::Init()
{
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_SETOBJECT);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CSetWord::Uninit(void)
{
	if (m_pWordPos != NULL)
	{
		delete[] m_pWordPos;
		m_pWordPos = NULL;
	}

	//����������(�I�u�W�F�N�g��j��)
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CSetWord::Update(void)
{
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CSetWord::Draw(void)
{
	//�f�o�C�X���擾
	//CRenderer *pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	//D3DXMATRIX mtxParent;

}


//=============================================================================
// �I�u�W�F�N�g�̔z�u����ǂݍ���
//=============================================================================
void CSetWord::LoadFile(char *pFileName)
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
	int nNum = 0;
	D3DXVECTOR3 ModelPos;	//���f���̈ʒu

	if (m_pWordPos != NULL)
	{
		delete[] m_pWordPos;
		m_pWordPos = NULL;
	}

	if (m_pWord != NULL)
	{
		m_pWord->Uninit();
		delete[] m_pWord;
		m_pWord = NULL;
	}

	//�t�@�C�����J�� �ǂݍ���
	pFile = fopen(pFileName, "r");
	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		while (1)
		{
			//������̐擪��ݒ�
			pStrcur = ReadLine(pFile, &aLine[0]);
			//����������o��
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "ANSWERNUM = ", strlen("ANSWERNUM = ")) == 0)
			{
				//���o��
				pStrcur += strlen("ANSWERNUM = ");
				//������̐擪��ݒ�
				strcpy(aStr, pStrcur);
				//�����񔲂��o��
				nNum = atoi(pStrcur);
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				if (m_pWord == NULL)
				{
					m_pWord = new CWord[nNum];
				}

				if (m_pWordPos == NULL)
				{
					m_pWordPos = new Word_Pos[nNum];
				}
				//CWordManager::SetWordAnswerNum(nAnswerNum);
			}

			//�I�u�W�F�N�g�ǂݍ���
			if (memcmp(pStrcur, "MODELSET", strlen("MODELSET")) == 0)
			{
				//���o��
				pStrcur += strlen("MODELSET");
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
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
			}
			//���f���𐶐�
			if (memcmp(pStrcur, "END_MODELSET", strlen("END_MODELSET")) == 0)
			{
				//CWord::Create(D3DXVECTOR3(380.0f, 0.0f, 380.0f), 12.0f, 12.0f, "WORD", 38);

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
char *CSetWord::ReadLine(FILE *pFile, char *pDst)
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
char * CSetWord::GetLineTop(char * pStr)
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
int CSetWord::PopString(char * pStr, char * pDest)
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
