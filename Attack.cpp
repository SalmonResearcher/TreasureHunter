#include "Attack.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"


#include "Player.h"
#include "Enemy.h"

namespace {
    XMVECTOR playerForwardVec_;
    XMFLOAT3 playerPos_;



}

//コンストラクタ
Attack::Attack(GameObject* parent)
    :GameObject(parent, "Attack"), hModel_(-1), deleteTime_(0), move_{0,0,0}
{
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), ATTACK_SIZE);
    AddCollider(collision);
}

//デストラクタ
Attack::~Attack()
{

}

//初期化
void Attack::Initialize()
{

}

//更新
void Attack::Update()
{
    Attacking();
    if (deleteTime_ <= 0)
    {
        KillMe();
    }
    deleteTime_--;

}

//描画
void Attack::Draw()
{
}

//開放
void Attack::Release()
{
}

void Attack::OnCollision(GameObject* pTarget)
{
}

void Attack::AttackDirection(XMVECTOR _dir)
{
    playerForwardVec_ = _dir;
}

void Attack::AttackPosition(XMFLOAT3 _pos)
{
    //この数を変更すると攻撃の出現位置が遠くなる
    float offset = 0.25f;
    playerPos_ = _pos;
    // 弾丸の初期位置 = プレイヤー位置 + (前方ベクトル * 距離オフセット)
    XMVECTOR attackInit = XMLoadFloat3(&playerPos_) + (playerForwardVec_ * offset);
    XMStoreFloat3(&attackPos_, attackInit);
}

void Attack::Attacking() {
    XMFLOAT3 moveAtk;
    XMStoreFloat3(&moveAtk, playerForwardVec_);
    attackPos_.x += moveAtk.x * ATTACK_SIZE;
    attackPos_.z += moveAtk.z *ATTACK_SIZE;
    transform_.position_ = attackPos_;
}
