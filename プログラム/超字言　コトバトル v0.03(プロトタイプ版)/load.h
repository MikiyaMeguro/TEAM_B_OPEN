//=============================================================================
//
// ���f���̓ǂݍ��ݏ��� [load.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _LOAD_H_
#define _LOAD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CLoad
{
public:
	typedef enum // cpp�̂�Ɛ��ƕ��т𑵂���
	{
		MODEL_CAR0 = 0,	// ��0
		MODEL_CAR1,		// ��1
		MODEL_DESK,		// ��
		MODEL_PULIN,	// �v����
		MODE_KNIFE,		// �i�C�t
		MODE_APPLE,		// �A�b�v��
		MODE_PALLET,	// �G��
		MODE_TAICO,		// �^�C��
		MODE_WHEEL,		// ����
		MODE_COIN,		// �R�C��
		MODEL_BOX,		// ��
		MODEL_SAMPLE_PLAYER,	//�v���C���[(Sample)
		MODEL_MAX,
	} MODEL;

	CLoad();		// �R���X�g���N�^
	~CLoad();	// �f�X�g���N�^

	static HRESULT LoadModel(void);
	static void UnloadModel(void);

	static LPD3DXMESH GetMesh(int nIdx);
	static LPD3DXBUFFER GetBuffMat(int nIdx);
	static DWORD GetNumMat(int nIdx);


	static void LoadFile(void);
	static char *ReadLine(FILE *pFile, char *pDst);	//1�s�ǂݍ���
	static char *GetLineTop(char *pStr);			//�s�̐擪���擾
	static int  PopString(char *pStr, char *pDest);	//�s�̍Ō��؂�̂�

private:
	static LPD3DXMESH		*m_pMesh;		// ���b�V�����i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER		*m_pBuffMat;		// �}�e���A�����ւ̃|�C���^
	static DWORD			*m_nNumMat;		// �}�e���A�����̐�
	static char m_apModelName[MODEL_MAX][256];
	static const char *m_apModelFilename[];
	static int m_nCntModel;
	static int m_nMaxModel;
};

#endif