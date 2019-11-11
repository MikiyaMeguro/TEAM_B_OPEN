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
		MODE_WALL_SMALL = 0,// ��������
		MODE_WALL_BIG,	// �傫����
		MODE_GEAR,		// ����
		MODEL_BOX,		// ��
		MODEL_DODAI,	// �y��
		MODE_DUST,		// �S�~
		MODEL_SAMPLE_PLAYER,	//�v���C���[(Sample)
		MODEL_CAR0,		// ��0
		MODEL_MIC,		// �}�C�N
		MODEL_DESK,		// ��
		MODEL_PULIN,	// �v����
		MODE_KNIFE,		// �i�C�t
		MODE_APPLE,		// �A�b�v��
		MODE_PALLET,	// �G��
		MODE_TAICO,		// �^�C��
		MODE_WHEEL,		// ����
		MODE_COIN,		// �R�C��
		MODE_SUIKA,		// ������
		MODE_TARAI,		// ���炢
		MODE_POT,		// �₩��
		MODE_IKARI,		// ������
		MODE_IKADA,		// ������
		MODEL_SAIHU,	// ���z
		MODEL_KARUTA,	// ���邽
		MODEL_CAMERA,	// �J����
		MODEL_TWIG,		// ������
		MODEL_STRAWBERRY,// �C�`�S
		MODEL_EGG,		// ���܂�
		MODEL_LANCE,	// �����X
		MODEL_KADANN,	// ������
		MODEL_KATANA,	// ��
		MODEL_LOG	,	// �܂邽
		MODEL_ICE,		// ���
		MODEL_DANGO,	// ����
		MODEL_MAKURA,	// �܂���
		MODEL_KUNAI,	// ���Ȃ�
		MODEL_FISH,		// ������
		MODEL_VOLCANO,	// ������
		MODEL_NAZCA,	// �Ȃ���
		MODEL_TANK,		// ����
		MODEL_YAGURA,	// �₮��
		MODEL_CHAIR,	// ������
		MODEL_CONGA,	// ����
		MODEL_DICE,		// ������
		MODEL_TREASURECHEST,	// ������
		MODEL_GRASS,	// �K���X
		MODEL_STRETCHER,	// ����
		MODEL_RING,	// �����O
		MODEL_KUSAYA,	// ������
		MODEL_SAZAE,	// �T�U�G
		MODEL_TILE,	// �^�C��
		MODEL_Rice,	// ���C�X
		MODEL_Comic,	// �}���K
		MODEL_Fuigo,	// �ӂ���
		MODEL_Namako,	// �i�}�R
		MODEL_Zugai,	// ������
		MODEL_Seaweed,	// �R���u
		MODEL_Laitc,	// �炢��
		MODEL_Mekabu,	// �߂���
		MODEL_Medic,	// ������
		MODEL_Kaiga,	// ������
		MODEL_MAX
	} MODEL;

	CLoad();		// �R���X�g���N�^
	~CLoad();	// �f�X�g���N�^

	static HRESULT LoadModel(void);
	static void UnloadModel(void);

	static LPD3DXMESH GetMesh(int nIdx);
	static LPD3DXBUFFER GetBuffMat(int nIdx);
	static DWORD GetNumMat(int nIdx);
	static void TextureSetting(int nModel);
	static LPDIRECT3DTEXTURE9 *GetTexture(MODEL Model);

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

	static LPDIRECT3DTEXTURE9	*m_pTexture[MODEL_MAX];			// �e�N�X�`���ւ̃|�C���^
};

#endif