#include "Enemy.h"
#include "Novice.h"

Enemy::Enemy(int posX, int posY, int speed, int radius, bool isAlive)
{
	enemyCount++;
	posX_ = posX;
	posY_ = posY;
	speed_ = speed;
	radius_ = radius;
	isAlive_ = isAlive;
}

Enemy::~Enemy() 
{
	enemyCount--;
}
void Enemy::Update()
{
	posX_ += speed_;
	if (posX_ - radius_ < 0)
	{
		speed_ *= -1;
	}
	if (posX_ + radius_ > 1280)
	{
		speed_ += -1;
	}
}

void Enemy::Draw() 
{
	Novice::DrawEllipse(posX_, posY_, radius_, radius_, 0.0, RED, kFillModeSolid);
}