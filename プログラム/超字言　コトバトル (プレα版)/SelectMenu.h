//=============================================================================
//
// �Z���N�g���j���[���� [SelectMenu.h]
// Author : Mikiya Meguro/Akane Gokan
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
#define MAX_SELETMODE_BG		(10)						//BG�̍ő�|���S��
#define BAND_SIZE				(0.5f)						//�т̃T�C�Y
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

	static SELECT_MENU *GetModeSelectMode(void) {	return &m_SelectMode;	}
	static HRESULT Load(void) { return S_OK; }
	static void UnLoad(void);
	static bool GetModeSelectBool(void) { return m_bModeSelect; }
	static void SetModeSelectBool(bool ModeSelectBool) { m_bModeSelect = ModeSelectBool; }

	void MenuDecide(SELECT_MENU MenuSelect);

	//�����o�ϐ�
private:
	/* �w�i�̎�� */
	typedef enum
	{
		SELECTMODEBGTYPE_BG = 0,
		SELECTMODEBGTYPE_BAND_L,
		SELECTMODEBGTYPE_BAND_R,
		SELECTMODEBGTYPE_FRAME,
		SELECTMODEBGTYPE_EXPLANATION

	}SELECTMODEBGTYPE;

	/* �|���S���̎�� */
	typedef enum
	{
		POLYGONTYPE_NONE = 0,
		POLYGONTYPE_MENU,
		POLYGONTYPE_BG
	}POLYGONTYPE;

	/* �A�j���[�V�����̊������� */
	typedef enum
	{
		ANIMTYPE_NONE=0,
		ANIMTYPE_X,
		ANIMTYPE_Y,
		ANIMTYPE_MAX

	}ANIMTYPE;
	void ScrollMenu(SELECTMODEBGTYPE type, float fScroolSpeed);
	void SelectModeExplanation(int MenuSelect);
	void SelectAnimation(int MenuSelect);
	void SelectMove(POLYGONTYPE type,int MenuNum);
	void SetSelectAnimation(POLYGONTYPE type, ANIMTYPE AnimType,int MenuNum, int MaxAnimPatternX, int MaxAnimPatternY,int AnimSpeed);
	void InitTutorialPolygon(void);

	D3DXVECTOR3					m_InitPos;
	float						m_fWidth, m_fHeight;	// ������
	float						m_fSpace;
	float						m_fInitYpos;	//���j���[�̏�������
	D3DXVECTOR3					m_TexMove;

	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_SELECTMENU];			// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;							// ���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTextureBG;						// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffBG;						// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D					*m_apPolygonBG[MAX_SELETMODE_BG];	// ���j���[�̃|���S��
	MENU_TYPE					m_MenuType;							// ���j���[�̃^�C�v
	SELECTMENU					m_aModeSelectMenu[MAX_SELECTMENU];	// �Z���N�g���j���[
	D3DXVECTOR3					m_Pos[MAX_SELECTMENU];				// �ʒu
	static SELECT_MENU			m_SelectMode;						// �I�����Ă郂�[�h
	int							m_nSelect;							// �I�����Ă���ԍ�
	CScene2D					*m_apPolygon[MAX_SELECTMENU];		// ���j���[�̃|���S��
	static	bool				m_bModeSelect;						// �Z���N�g���j���[�̏��
	int							m_nMaxMenu;							// ���j���[�ő吔

	/* ���o�ʕϐ� */
	int m_nCntScrool;		//�X�N���[���J�E���^�[
	int m_nCntAnim;			//�A�j���J�E���^�[
	int m_nPatturnAnim;		//�A�j���p�^�[��
	int m_nCntAnim2;			//�A�j���J�E���^�[
	int m_nPatturnAnim2;		//�A�j���p�^�[��
	float m_fChangeMode;	//�I�𒆃��[�h�A�C�R���̈ړ�����J�E���^�[
	float m_fMoveMode;		//�I�𒆃��[�h�A�C�R���̈ړ��ʂ��v��
};

#endif