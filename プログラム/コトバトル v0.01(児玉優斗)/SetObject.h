//=============================================================================
//
// �I�u�W�F�N�g�z�u���� [SetObject.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _SETOBJECT_H_
#define _SETOBJECT_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CSceneX;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MATTEX	(20)

//*********************************************************************
//�v���C���[�N���X�̒�`
//*********************************************************************
class CSetObject : public CScene //�h���N���X
{
public:
	//���f���̎��
	typedef enum
	{
		MODELTYPE_BOX000 = 0,	//BOX
		MODELTYPE_MAX,			//�ő吔
	}MODELTYPE;

	CSetObject();
	~CSetObject();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CSetObject *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void UnLoad(void);
	D3DXVECTOR3 GetPos(void);

	static void SaveFile(void);
	static void LoadFile(void);

	static char *ReadLine(FILE *pFile, char *pDst);	//1�s�ǂݍ���
	static char *GetLineTop(char *pStr);			//�s�̐擪���擾
	static int  PopString(char *pStr, char *pDest);	//�s�̍Ō��؂�̂�


private:
	//�����o�ϐ�
	D3DXVECTOR3					m_pos;				//�ʒu
	D3DXVECTOR3					m_posold;			//�O��̈ʒu
	D3DXVECTOR3					m_move;				//�ړ���
	D3DXVECTOR3					m_ModelMove;		//�ړ��̎d��
	D3DXVECTOR3					m_rot;				//����
	D3DXMATRIX					m_mtxWorld;			//���[���h�}�g���b�N�X
	MODELTYPE					m_Type;				//�^�C�v
	int							m_nType;			//�^�C�vint�^
	static int					m_nMaxModel;
	bool						m_bBillboard;		//


	int							m_nRange;			//�폜�͈̔�

	float						m_fDestAngle;		//�p�x
	float						m_fDiffAngle;		//����

	static LPD3DXMESH			m_pMesh[MODELTYPE_MAX];			//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pBuffMat[MODELTYPE_MAX];		//�}�e���A�����ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTexture[MODELTYPE_MAX];		//�e�N�X�`���ւ̃|�C���^
	static DWORD				m_nNumMat[MODELTYPE_MAX];		//�}�e���A�����̐�

	int							m_nCount;						//�J�E���^�[
	int							m_nCollision;					//�����蔻���ONOFF
	static char					m_aFileName[MODELTYPE_MAX][256];		//�t�@�C���̖��O
public:
	CSceneX						*m_pObject;
};

#endif