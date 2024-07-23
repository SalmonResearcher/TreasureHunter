#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"



//�e�X�g�V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
	int hBGM_;

	int hScoreSound_;
	int soundtimer;
	Text* pText;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�T�E���h���ZF���ƂɍĐ�����
	void SoundPlay(int handle, int interval);

};