//=============================================================================
//
// �Q�[������ [game.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include "player.h"
#include "tube.h"
#include "meshField.h"
//�O���錾
class CPlayer;
class CTube;
class CPoint;

//=============================================================================
// �}�N����`
//=============================================================================
//********************************
// 1��ʎ��̓��̈ʒu
//********************************
#define WORD_TUBE001_POS_1P		(D3DXVECTOR3(50.0f, 590.0f, 0.0f))		// 2��ʎ�(1P)�̈ʒu

//********************************
// 2��ʎ��̓��̈ʒu
//********************************
#define WORD_TUBE002_POS_1P		(D3DXVECTOR3(50.0f, 240.0f, 0.0f))		// 2��ʎ�(1P)�̈ʒu
#define WORD_TUBE002_POS_2P		(D3DXVECTOR3(50.0f, 590.0f, 0.0f))		// 2��ʎ�(2P)�̈ʒu
#define WORD_TUBE002_SIZE		(D3DXVECTOR2(60.0f, 160.0f))			// 2��ʎ��̃T�C�Y

//********************************
// 3��ʎ��̓��̈ʒu
//********************************
#define WORD_TUBE003_POS_1P		(D3DXVECTOR3(50.0f, 240.0f, 0.0f))		// 3��ʎ�(1P)�̈ʒu
#define WORD_TUBE003_POS_2P		(D3DXVECTOR3(1220.0f, 240.0f, 0.0f))	// 3��ʎ�(2P)�̈ʒu
#define WORD_TUBE003_POS_3P		(D3DXVECTOR3(50.0f, 590.0f, 0.0f))		// 3��ʎ�(3P)�̈ʒu

//********************************
// 4��ʎ��̓��̈ʒu
//********************************
#define WORD_TUBE004_POS_1P		(D3DXVECTOR3(50.0f, 240.0f, 0.0f))		// 4��ʎ�(1P)�̈ʒu
#define WORD_TUBE004_POS_2P		(D3DXVECTOR3(1220.0f, 240.0f, 0.0f))	// 4��ʎ�(2P)�̈ʒu
#define WORD_TUBE004_POS_3P		(D3DXVECTOR3(50.0f, 590.0f, 0.0f))		// 4��ʎ�(3P)�̈ʒu
#define WORD_TUBE004_POS_4P		(D3DXVECTOR3(1220.0f, 590.0f, 0.0f))	// 4��ʎ�(4P)�̈ʒu

#define MAX_PLAYER (4)

//�N���X�i�V�[��2D�̔h���N���X�j
class CGame
{
public:
	CGame();
	~CGame();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadChara(void);
	static CGame *Create(void);

	void WordCreate(void);	// �����̐����̊Ǘ�

	// �擾�̊֐�
	static CPlayer *GetPlayer(int nNumPlayer = 0) { return (nNumPlayer < MAX_PLAYER && nNumPlayer >= 0) ? m_pPlayer[nNumPlayer] : m_pPlayer[0]; }		// �v���C���[�̎擾
	static CTube *GetTube(int nNum);		// �����̉���UI�̎擾
	static CMeshField *GetMeshField(void) { return m_pMeshField; }			// �����̉���UI�̎擾
	static CPoint *GetPoint(int nNum) { return m_pPoint[nNum]; }			// �|�C���g�̎擾
private:
	void CameraSetting(int nNum);		// �l���ɉ������J��������
	void PlayerSetting(int nNum);		// �l���ɉ������v���C���[����
	void TubeSetting(int nNum);			// �l���ɉ��������̐���
	void SetPointFrame(int nNum);		// �l���ɉ������|�C���g�̐���
	static CPlayer *m_pPlayer[MAX_PLAYER];
	static CTube *m_apTube[MAX_PLAYER];
	static CPoint *m_pPoint[MAX_PLAYER];
	static CMeshField *m_pMeshField;

};
#endif