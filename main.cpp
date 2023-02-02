#include <Novice.h>
#include"Enemy.h"
#include <stdio.h>

const char kWindowTitle[] = "LC1B_11_サイトウ_ユウキ_タイトル";

int Enemy::enemyCount;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Enemy* enemy1 = new Enemy(50, 300, 5, 15, true);
	Enemy* enemy2 = new Enemy(500, 500, 5, 15, true);
	Enemy* enemy3 = new Enemy(900, 150, 5, 15, true);

	int posX = 400;
	int posY = 600;
	int size = 25;
	int speed = 5;
	int bulletX = 0;
	int bulletY = 0;
	int bulletSize = 10;
	int bulletSpeed = 9;
	bool isShot = false;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

        enemy1->Update();
        enemy2->Update();
        enemy3->Update();

        if (keys[DIK_W])
        {
            posY -= speed;
        }

        if (keys[DIK_A])
        {
            posX -= speed;
        }

        if (keys[DIK_D])
        {
            posX += speed;
        }

        if (keys[DIK_S])
        {
            posY += speed;
        }

        if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0 && isShot == false)
        {
            isShot = true;
            bulletX = posX;
            bulletY = posY;
        }

        if (isShot == true)
        {
            bulletY -= bulletSpeed;
        }
        if (bulletY < -5)
        {
            isShot = false;
        }

        if (bulletX <= enemy1->posX_ + enemy1->radius_ &&
            enemy1->posX_ <= bulletX + bulletSize &&
            bulletY <= enemy1->posY_ + enemy1->radius_ &&
            enemy1->posY_ <= bulletY + bulletSize) {
            delete enemy1;
            delete enemy2;
            delete enemy3;
        }

        if (bulletX <= enemy2->posX_ + enemy2->radius_ &&
            enemy2->posX_ <= bulletX + bulletSize &&
            bulletY <= enemy2->posY_ + enemy2->radius_ &&
            enemy2->posY_ <= bulletY + bulletSize) {
            delete enemy1;
            delete enemy2;
            delete enemy3;
        }
        if (bulletX <= enemy3->posX_ + enemy3->radius_ &&
            enemy3->posX_ <= bulletX + bulletSize &&
            bulletY <= enemy3->posY_ + enemy3->radius_ &&
            enemy3->posY_ <= bulletY + bulletSize) {
            delete enemy1;
            delete enemy2;
            delete enemy3;
        }

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

        Novice::DrawEllipse(posX, posY, size, size, 0.0, GREEN, kFillModeSolid);

        if (isShot == true)
        {
            Novice::DrawEllipse(bulletX, bulletY, bulletSize, bulletSize, 0.0, WHITE, kFillModeSolid);
        }

        if (enemy1->isAlive_ == true)
        {
            enemy1->Draw();
        }

        if (enemy2->isAlive_ == true)
        {
            enemy2->Draw();
        }

        if (enemy3->isAlive_ == true)
        {
            enemy3->Draw();
        }

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
