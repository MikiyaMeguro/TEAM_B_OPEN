//=============================================================================
//
// ���C������ [main.h]
// Author : �R���֎j
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"

//�O���錾

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

private:
	void CameraSetting(void);

};
#endif