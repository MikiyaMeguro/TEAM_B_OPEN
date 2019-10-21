//=============================================================================
//
// �Z���N�g���j���[���� [SelectMenu.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _SELECTMENU_H_
#define _SELECTMENU_H_

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
#define MAX_SELECTMENU			(4)							//�ő�|���S������

//*********************************************************************
//�Q�[���N���X�̒�`
//*********************************************************************
class CSelectMenu : public CScene //�h���N���X
{
public:
	typedef enum
	{
		SELECT_MENU_NONE = 0,
		SELECT_MENU_ONE,			//1�ڂ̃��j���[
		SELECT_MENU_TWO,			//2�ڂ̃��j���[
		SELECT_MENU_THREE,			//3�ڂ̃��j���[
		SELECT_MENU_FOUR,			//4�ڂ̃��j���[
		SELECT_MENU_MAX			//��Ԃ̑���
	}SELECT_MENU;				//�񋓌^

	typedef enum
	{
		SELECTTYPE_NONE = 0,	//�I�΂�Ă��Ȃ����
		SELECTTYPE_SELECT,		//�I�΂�Ă���	���
		SELECTTYPE_MAX			//��Ԃ̑���
	}SELECT;

	typedef enum
	{
		MENU_TYPE_NONE = 0,		//����
		MENU_TYPE_TUTORIAL,		//�`���[�g���A��
		MENU_TYPE_RESULT,		//���g���C
		MENU_TYPE_PAUSE,		//�|�[�Y
		MENU_TYPE_MAX			//��Ԃ̑���
	}MENU_TYPE;

	typedef struct
	{
		SELECT		select;		//�Z���N�g
		D3DXVECTOR3 pos;		//�ʒu
		D3DXCOLOR	col;		//�J���[
	}SELECTMENU;

	CSelectMenu(int nPriority = 7);
	~CSelectMenu();
	static CSelectMenu *Create(D3DXVECTOR3 pos, float fLength, float fSpace, MENU_TYPE type);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static SELECT_MENU *GetModeSelectMode(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	static bool GetModeSelectBool(void);
	static void SetModeSelectBool(bool ModeSelectBool);
	void MenuDecide(SELECT_MENU MenuSelect);
	//�����o�ϐ�
private:
	D3DXVECTOR3					m_InitPos;
	float						m_fWidth, m_fHeight;	// ������
	float						m_fSpace;
	float						m_fInitYpos;	//���j���[�̏�������
	D3DXVECTOR3					m_TexMove;

	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_SELECTMENU];			// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;							// ���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTextureBG;						// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffBG;						// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D					*m_apPolygonBG;						// ���j���[�̃|���S��
	MENU_TYPE					m_MenuType;							// ���j���[�̃^�C�v
	SELECTMENU					m_aModeSelectMenu[MAX_SELECTMENU];	// �Z���N�g���j���[
	D3DXVECTOR3					m_Pos[MAX_SELECTMENU];				// �ʒu
	static SELECT_MENU			m_SelectMode;						// �I�����Ă郂�[�h
	int							m_nSelect;							// �I�����Ă���ԍ�
	CScene2D					*m_apPolygon[MAX_SELECTMENU];		// ���j���[�̃|���S��
	static	bool				m_bModeSelect;						// �Z���N�g���j���[�̏��
	int							m_nMaxMenu;							// ���j���[�ő吔
};

#endif