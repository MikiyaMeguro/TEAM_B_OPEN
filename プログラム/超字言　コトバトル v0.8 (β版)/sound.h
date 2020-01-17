//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*********************************************************************
//�T�E���h�N���X�̒�`
//*********************************************************************
//��{�N���X
class CSound
{
public:
	// �T�E���h�t�@�C��
	typedef enum //���x���Ɛ��ƕ��т𑵂���
	{
		SOUND_LABEL_BGM_TITLE = 0,		// �^�C�g��
		SOUND_LABEL_BGM_SELECT,			// �Z���N�g
		SOUND_LABEL_BGM_TUTORIAL,		// �`���[�g���A��
		SOUND_LABEL_BGM_CHARACTERSELECT,// �L�����N�^�[�Z���N�g
		SOUND_LABEL_BGM_STAGESELECT,	// �X�e�[�W�Z���N�g
		SOUND_LABEL_BGM_GAME000,		// �Q�[��[�@�B�X�e�[�W]
		SOUND_LABEL_BGM_GAME001,		// �Q�[��[�V��X�e�[�W]
		SOUND_LABEL_BGM_GAME002,		// �Q�[��[�n�`�X�e�[�W]
		SOUND_LABEL_BGM_RANKING,		// �����L���O

		SOUND_LABEL_SE_BULLET000,		// �e�Ƃ̏Փˉ�[�m�b�N�o�b�N��]
		SOUND_LABEL_SE_BULLET001,		// �e�Ƃ̏Փˉ�[�X�s�[�h]
		SOUND_LABEL_SE_BULLET002,		// �e�Ƃ̏Փˉ�[���˕Ԃ�]
		SOUND_LABEL_SE_BULLET003,		// �e�Ƃ̏Փˉ�[�ђ�]

		SOUND_LABEL_SE_GETTEXT000,		// �����擾��[1�����ڎ擾]
		SOUND_LABEL_SE_GETTEXT001,		// �����擾��[2�����ڎ擾]
		SOUND_LABEL_SE_GETTEXT002,		// �����擾��[3�����ڎ擾]

		SOUND_LABEL_SE_STEP,			// �X�e�b�v
		SOUND_LABEL_SE_PAUSEOPEN,		// �|�[�Y���������ۂ̉�
		SOUND_LABEL_SE_PAUSECLOSE,		// �|�[�Y�I�����ۂ̉�

		SOUND_LABEL_SE_SWITCHON,		// �X�C�b�`��������ON
		SOUND_LABEL_SE_SWITCHOFF,		// �X�C�b�`��������OFF

		SOUND_LABEL_SE_POINTUP,			// �|�C���g�A�b�v
		SOUND_LABEL_SE_POINTDOWN,		// �|�C���g�_�E��

		SOUND_LABEL_SE_SELECT00,		// ���艹
		SOUND_LABEL_SE_SELECT01,		// �L�����Z�����h���h��
		SOUND_LABEL_SE_SELECT02,		// �I����
		SOUND_LABEL_SE_SELECT03,		// �L�����N�^�[�I����
		SOUND_LABEL_SE_SELECT04,		// �Q�[���X�^�[�g

		SOUND_LABEL_VOICE_TITLECALL00,		//�^�C�g���R�[��
		SOUND_LABEL_VOICE_TITLECALL01,		//�^�C�g���R�[��2
		SOUND_LABEL_VOICE_SELECT_DOG,		//�L�����I�����@��
		SOUND_LABEL_VOICE_SELECT_BEAR,		//�L�����I�����@�F
		SOUND_LABEL_VOICE_SELECT_CAT,		//�L�����I�����@�L
		SOUND_LABEL_VOICE_SELECT_RABBIT,	//�L�����I�����@�e
		SOUND_LABEL_VOICE_DOG_ATTACK00,		//���@�U���{�C�X
		SOUND_LABEL_VOICE_DOG_ATTACK01,		//���@�U���{�C�X
		SOUND_LABEL_VOICE_DOG_DAMAGE00,		//���@��e�{�C�X
		SOUND_LABEL_VOICE_BEAR_ATTACK00,	//�F�@�U���{�C�X
		SOUND_LABEL_VOICE_BEAR_ATTACK01,	//�F�@�U���{�C�X
		SOUND_LABEL_VOICE_BEAR_DAMAGE00,	//�F�@��e�{�C�X
		SOUND_LABEL_VOICE_CAT_ATTACK00,		//�L�@�U���{�C�X
		SOUND_LABEL_VOICE_CAT_ATTACK01,		//�L�@�U���{�C�X
		SOUND_LABEL_VOICE_CAT_DAMAGE00,		//�L�@��e�{�C�X
		SOUND_LABEL_VOICE_RABBIT_ATTACK00,	//�e�@�U���{�C�X
		SOUND_LABEL_VOICE_RABBIT_ATTACK01,	//�e�@�U���{�C�X
		SOUND_LABEL_VOICE_RABBIT_DAMAGE00,	//�e�@��e�{�C�X
		SOUND_LABEL_VOICE_DOG_VICTORY,		//���@�D���R�����g
		SOUND_LABEL_VOICE_BEAR_VICTORY,		//�F�@�D���R�����g
		SOUND_LABEL_VOICE_CAT_VICTORY,		//�L�@�D���R�����g
		SOUND_LABEL_VOICE_RABBIT_VICTORY,	//�e�@�D���R�����g

		SOUND_LABEL_SE_GAMESTART00,	//�R�g�o�g��
		SOUND_LABEL_SE_GAMESTART01,	//�X�^�[�g
		SOUND_LABEL_SE_GAMEEND,		//�����܂�


		SOUND_LABEL_SE_TITLE,		// �^�C�g��

		SOUND_LABEL_SE_EXPLOSION, //����
		SOUND_LABEL_MAX
	} SOUND_LABEL;
	// �p�����[�^�\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	float GetVolume(SOUND_LABEL label);						// ���ʂ̎擾
	void SetVolume(SOUND_LABEL label, float fVolume);		// ���ʂ̐ݒ�

protected:
	IXAudio2				*m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice	*m_pMasteringVoice = NULL;						// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX] = {};			// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX] = {};			// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX] = {};				// �I�[�f�B�I�f�[�^�T�C�Y
    // �e���f�ނ̃p�����[�^ ���x���Ɛ��ƕ��т𑵂���
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/TITLE.wav", -1 },			// �^�C�g��
		{ "data/BGM/SELECT.wav", -1 },			// �Z���N�g
		{ "data/BGM/TUTORIAL.wav", -1 },		// �`���[�g���A��
		{ "data/BGM/CHARACTERSELECT.wav", -1 },	// �L�����N�^�[�Z���N�g
		{ "data/BGM/STAGESELECT.wav", -1 },		// �X�e�[�W�Z���N�g
		{ "data/BGM/GAME000.wav", -1 },			// �Q�[��[�@�B�X�e�[�W]
		{ "data/BGM/GAME000.wav", -1 },			// �Q�[��[�V��X�e�[�W]
		{ "data/BGM/GAME000.wav", -1 },			// �Q�[��[�n�`�X�e�[�W]
		{ "data/BGM/RANKING.wav", -1 },			// �����L���O

		{ "data/SE/bullet000.wav", 0 },			// �e�Ƃ̏Փˉ�[�m�b�N�o�b�N��]
		{ "data/SE/bullet001.wav", 0 },			// �e�Ƃ̏Փˉ�[�X�s�[�h]
		{ "data/SE/bullet002.wav", 0 },			// �e�Ƃ̏Փˉ�[���˕Ԃ�]
		{ "data/SE/bullet003.wav", 0 },			// �e�Ƃ̏Փˉ�[�ђ�]

		{ "data/SE/gettext000.wav", 0 },		// �����擾��[1�����ڎ擾]
		{ "data/SE/gettext001.wav", 0 },		// �����擾��[2�����ڎ擾]
		{ "data/SE/gettext002.wav", 0 },		// �����擾��[3�����ڎ擾]

		{ "data/SE/step.wav", 0 },				// �X�e�b�v
		{ "data/SE/pause_open.wav", 0 },		// �|�[�Y���������ۂ̉�
		{ "data/SE/pause_close.wav", 0 },		// �|�[�Y�I�����ۂ̉�

		{ "data/SE/switchon.wav", 0 },		// �X�C�b�`��������ON
		{ "data/SE/switchoff.wav", 0 },		// �X�C�b�`��������OFF

		{ "data/SE/pointup.wav", 0 },		// �|�C���g�A�b�v
		{ "data/SE/pointupdown.wav", 0 },	// �|�C���g�_�E��

		{ "data/SE/Select1.wav", 0 },	// ���艹
		{ "data/SE/Select2.wav", 0 },	// �L�����Z����
		{ "data/SE/Select3.wav", 0 },	// �I����
		{ "data/SE/Select4.wav", 0 },	// �L�����N�^�[�I����
		{ "data/SE/Select5.wav", 0 },	// �Q�[���X�^�[�g

		{ "data/VOICE/titlecall000.wav", 0 },		//�^�C�g���R�[��
		{ "data/VOICE/titlecall001.wav", 0 },		//�^�C�g���R�[��2
		{ "data/VOICE/dog_select.wav", 0 },			//�L�����I�����@��
		{ "data/VOICE/bea_select.wav", 0 },			//�L�����I�����@�F
		{ "data/VOICE/cat_select.wav", 0 },			//�L�����I�����@�L
		{ "data/VOICE/rabit_select.wav", 0 },		//�L�����I�����@�e
		{ "data/VOICE/dog_atk000.wav", 0 },			//���@�U���{�C�X
		{ "data/VOICE/dog_atk001.wav", 0 },			//���@�U���{�C�X
		{ "data/VOICE/dog_damege.wav", 0 },			//���@��e�{�C�X
		{ "data/VOICE/bea_atk000.wav", 0 },			//�F�@�U���{�C�X
		{ "data/VOICE/bea_atk001.wav", 0 },			//�F�@�U���{�C�X
		{ "data/VOICE/bea_damege.wav", 0 },			//�F�@��e�{�C�X
		{ "data/VOICE/cat_atk000.wav", 0 },			//�L�@�U���{�C�X
		{ "data/VOICE/cat_atk001.wav", 0 },			//�L�@�U���{�C�X
		{ "data/VOICE/cat_damege.wav", 0 },			//�L�@��e�{�C�X
		{ "data/VOICE/rabit_atk000.wav", 0 },		//�e�@�U���{�C�X
		{ "data/VOICE/rabit_atk001.wav", 0 },		//�e�@�U���{�C�X
		{ "data/VOICE/rabit_damege.wav", 0 },		//�e�@��e�{�C�X
		{ "data/VOICE/dog_victory.wav", 0 },		//���@�D��
		{ "data/VOICE/bea_victory.wav", 0 },		//�F�@�D��
		{ "data/VOICE/cat_victory.wav", 0 },		//�L�@�D��
		{ "data/VOICE/rabit_victory.wav", 0 },		//�e�@�D��

		{ "data/VOICE/gamestart000.wav", 0 },		//�R�g�o�g��
		{ "data/VOICE/gamestart001.wav", 0 },		//�X�^�[�g
		{ "data/VOICE/gameend000.wav", 0 },			//�����܂�


		{ "data/SE/Title.wav", 0 },	// �^�C�g��
		{ "data/SE/Explosion001.wav", 0 },	// ����

	};
};
#endif
