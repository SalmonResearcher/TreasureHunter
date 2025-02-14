#include "Stage.h"
#include "SkySphere.h"
#include "Engine/Model.h"

namespace
{
    SkySphere* pSky_;
}
//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    hModel_ = Model::Load("newStage3.fbx");
    assert(hModel_ >= 0);

    pSky_ = Instantiate<SkySphere>(this);
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//開放
void Stage::Release()
{
}