//=============================================================================
//
// �^�C�g������ [title.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"

//�O���錾

//�N���X�i�V�[��2D�̔h���N���X�j
class CTitle
{
public:
	CTitle();
	~CTitle();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTitle *Create(void);

};
#endif