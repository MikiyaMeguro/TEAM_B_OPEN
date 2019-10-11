//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _PLAYERSELECT_H_
#define _PLAYERSELECT_H_

#include "main.h"
#include "input.h"
#include "scene.h"

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER_SELECTMENU			(4)							//�����L���O�̐�

//*********************************************************************
//�Q�[���N���X�̒�`
//*********************************************************************
class CPlayerSelect : public CScene //�h���N���X
{
public:
	typedef enum
	{
		SELECTPLAYER_NONE = 0,
		SELECTPLAYER_1P,			//���s���
		SELECTPLAYER_2P,			//���g���C���
		SELECTPLAYER_3P,			//�I��
		SELECTPLAYER_4P,			//�I��
		SELECTPLAYER_MAX			//��Ԃ̑���
	}SELECTPLAYER;				//�񋓌^

	typedef enum
	{
		SELECTTYPE_NONE = 0,	//�I�΂�Ă��Ȃ����
		SELECTTYPE_SELECT,		//�I�΂�Ă���	���
		SELECTTYPE_MAX			//��Ԃ̑���
	}SELECT;

	typedef struct
	{
		SELECT		select;		//�Z���N�g
		D3DXVECTOR3 pos;		//�ʒu
		D3DXCOLOR	col;		//�J���[
	}SELECTMENU;

	CPlayerSelect(int nPriority = 7);
	~CPlayerSelect();
	static CPlayerSelect *Create(D3DXVECTOR3 pos, float fLength);
	HRESULT Init(void) { return S_OK; };
	virtual HRESULT Init(D3DXVECTOR3 pos);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static SELECTPLAYER *GetModeSelectMode(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	static bool GetModeSelectBool(void);
	static void SetModeSelectBool(bool ModeSelectBool);
	//�����o�ϐ�
private:
	D3DXVECTOR3					m_InitPos;
	float						m_fWidth, m_fHeight;	// ������
	D3DXVECTOR3					m_TexMove;


	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_PLAYER_SELECTMENU];			// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;							// ���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTextureBG;						// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffBG;						// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D					*m_apPolygonBG;						// ���j���[�̃|���S��

	SELECTMENU					m_aModeSelectMenu[MAX_PLAYER_SELECTMENU];		// �|�[�Y���j���[
	D3DXVECTOR3					m_Pos[MAX_PLAYER_SELECTMENU];				// �ʒu
	static SELECTPLAYER			m_SelectMode;						// �I�����Ă郂�[�h
	int							m_nSelect;							// �I�����Ă���ԍ�
	CScene2D					*m_apPolygon[MAX_PLAYER_SELECTMENU];		// ���j���[�̃|���S��
	static	bool				m_bModeSelect;							// �|�[�Y�̏��
};

#endif