#include "PlayScene.h"
#include "Global.h"

#include "Player.h"
#include "Stage.h"
#include "Enemy/Enemy.h"
#include "Jewel.h"
#include "JewelBox.h"
#include "JewelBullet.h"
#include "CharacterDisplay.h"

#include "EnemySpawn.h"

#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"

namespace {
	int timer = 0;
	int count = 0;

	int jewel_;
	int killCount_;
	int score_ = 0;

	XMFLOAT3 spawnPoint(0.0f, 0.0f, -50.0f);

	Player* pPlayer;
	Stage* pStage;
	Jewel* pJewel;
	Enemy* pEnemy;
	JewelBox* pBox;
	CharacterDisplay* pDisplay_;
	EnemySpawn* pEnemySpawn;
	JewelBullet* pBullet;

	float pitch = 1.0;
}

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), hBGM_(-1), hScoreSound_(-1)
{
}

//������
void PlayScene::Initialize()
{
	hBGM_ = Audio::Load("BGM/PlayScene.wav", true);
	assert(hBGM_ >= 0);
	Audio::Play(hBGM_, false, 1.0f, 0.15f);

	hScoreSound_ = Audio::Load("SE/CountUp.wav", false);
	assert(hScoreSound_ >= 0);

	pPlayer = Instantiate<Player>(this);
	pStage = Instantiate<Stage>(this);
	pJewel = Instantiate<Jewel>(this);
	pBox = Instantiate<JewelBox>(this);
	pEnemySpawn = Instantiate<EnemySpawn>(this);
	pBullet = Instantiate<JewelBullet>(this);

	pBullet->BulletPosition(XMFLOAT3(500, 0, 0));

	pDisplay_ = Instantiate<CharacterDisplay>(this);

	pDisplay_->CreateJewels(1);
	pDisplay_->CreateScores(1);
	pDisplay_->CreateTimers(1);

	pDisplay_->SetJewelPosition(0, 45, 650);
	pDisplay_->SetScorePosition(0, 950, 45);
	pDisplay_->SetTimerPosition(0, 850, 45);

	pDisplay_->ScoreCountStart(0);

	pDisplay_->SetTimerLimit(0, 60);
	pDisplay_->TimerStart(0);

	pEnemySpawn->SetInterval(30);
	pEnemySpawn->SetSpawnPoint(spawnPoint);
	pEnemySpawn->SetRandomX(-80.0f, 60.0f);
	pEnemySpawn->StartSpawn();
}

//�X�V
void PlayScene::Update()
{
	if (Input::IsKeyDown(DIK_P))
	{
		pEnemy = InstantiateFront<Enemy>(this);
	}

	count++;



	jewel_ = pBox->ReturnJewel();
	killCount_ = pPlayer->GetKillCount();


	//�^�C�}�[���O�Ȃ�
	if (Input::IsKeyDown(DIK_C) || pDisplay_->IsFinished(0)) {
		pEnemySpawn->StopSpawn();

		Global::AddJewel(jewel_);
		Global::AddKillCount(killCount_);

		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
	pDisplay_->CalcScoreValue(0);


	if (!pDisplay_->IsCountEnd(0))
	{
		SoundPlay(hScoreSound_, 5);
		pitch += 0.01f;
	}
	if (pDisplay_->IsCountEnd(0))
	{
		pitch = 1.0f;
	}


}

//�`��
void PlayScene::Draw()
{
	pDisplay_->Draw();

}

//�J��
void PlayScene::Release()
{
	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void PlayScene::SoundPlay(int  handle, int interval)
{
	if (soundtimer % interval == 0) {
		Audio::Play(handle, true, pitch, 0.2);
	}
	soundtimer++;
}