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

		SOUND_LABEL_MAX,
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


	};
};
#endif
