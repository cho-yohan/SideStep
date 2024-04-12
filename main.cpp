#include <Novice.h>
#include <stdlib.h>

const char kWindowTitle[] = "5147_Side_Step";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	int titleGhd =
		Novice::LoadTexture("./resources/title/titleScreen.png");

	int titleName[2] = {
	Novice::LoadTexture("./resources/title/titleName.png"),
	Novice::LoadTexture("./resources/title/titleName1.png") };

	int leftRun[3] = {
	Novice::LoadTexture("./resources/running/leftRunning0.png"),
	Novice::LoadTexture("./resources/running/leftRunning1.png"),
	Novice::LoadTexture("./resources/running/leftRunning2.png") };

	int rightRun[3] = {
	Novice::LoadTexture("./resources/running/rightRunning0.png"),
	Novice::LoadTexture("./resources/running/rightRunning1.png"),
	Novice::LoadTexture("./resources/running/rightRunning2.png") };

	int fuelGhd[3] = {
	Novice::LoadTexture("./resources/fuel/fuel0.png"),
	Novice::LoadTexture("./resources/fuel/fuelBack0.png"),
	Novice::LoadTexture("./resources/fuel/fuelBack1.png") };

	int gaugePointGhd =
		Novice::LoadTexture("./resources/point/point0.png");

	int obstacleGhd =
		Novice::LoadTexture("./resources/obstacle/obstacle0.png");

	int doorGhd =
		Novice::LoadTexture("./resources/door/GoalDoorSprite.png");

	int overGhd =
		Novice::LoadTexture("./resources/over/GameOverSprite.png");

	int clearGhd =
		Novice::LoadTexture("./resources/clear/ClearSprite.png");

	//===================================================================================================================
	//BGM
	//===================================================================================================================
	int soundHandle1 = Novice::LoadAudio("./sound/Journey.mp3");
	//int soundHandle2 = Novice::LoadAudio("./sound/164855__zonkmachine.mp3");

	int voiceHandle1 = 0;
	//int voiceHandle2 = 0;

	//===================================================================================================================

	struct Vector2 {
		float x, y;
		float size;
	};

	struct Title {
		float x, y;
	};

	struct Background {
		Vector2 pos;
		float width, height;
	};

	struct Player {
		Vector2 pos;
		float x, y;
		float speed;
		bool isSpeed;
	};

	struct Fuel {
		Vector2 pos;
		float x, y;
		int sizeX, sizeY;
		float speed;
	};

	struct Hit {
		Vector2 pos;
		Vector2 size;
		float x, y;
	};

	struct GaugeP {
		Vector2 pos;
		float x, y;
		float speed;
		bool isAlive;
	};

	struct Obstacle {
		Vector2 pos;
		float x, y;
		float speed;
		bool isAlive;
	};

	struct Door {
		Vector2 pos;
		float x, y;
	};

	struct GameTime {
		Vector2 pos;
		float x, y;
		float sizeX, sizeY;
	};

	//===================================================================================================================

	Title title[2];
	title[0].x = 0, title[0].y = 0;
	title[1].x = 400, title[1].y = 450;

	Background background[3];
	background[0].pos.x = 0, background[0].pos.y = 0;
	background[0].width = 1280, background[0].height = 720;

	background[1].pos.x = 1080, background[1].pos.y = 0;

	background[2].pos.x = 1105, background[2].pos.y = 245;
	background[2].width = 150, background[2].height = 280;


	Background fuelBack;
	fuelBack.pos.x = 1080, fuelBack.pos.y = 0;

	Background overScreen;
	overScreen.pos.x = 0, overScreen.pos.y = 0;

	Background clearScreen;
	clearScreen.pos.x = 0, clearScreen.pos.y = 0;

	Player player;
	player.pos.x = 50, player.pos.y = 620;
	player.speed = 8;
	player.isSpeed = true;

	Fuel fuel;
	fuel.pos.x = 1105, fuel.pos.y = 230;

	Fuel gauge1;
	gauge1.pos.x = 1110, gauge1.pos.y = 249;
	gauge1.sizeX = 140, gauge1.sizeY = 300;
	gauge1.speed = 0.3f;

	Fuel transBox;
	transBox.pos.x = 1110, transBox.pos.y = 530;
	transBox.sizeX = 140, transBox.sizeY = 300;


	Hit headHit;
	headHit.pos.x = player.pos.x;
	headHit.pos.y = player.pos.y;
	headHit.size.x = 25, headHit.size.y = 24;

	Hit bodyHit;
	bodyHit.pos.x = player.pos.x;
	bodyHit.pos.y = player.pos.y;
	bodyHit.size.x = 33, bodyHit.size.y = 65;

	GaugeP gaugeP[2];
	for (int p = 0; p < 2; p++) {
		gaugeP[p].pos.x = float(rand() % 1016 + 256); gaugeP[p].pos.y = 0;
		gaugeP[p].speed = 6;
		gaugeP[p].isAlive = false;
	}

	Hit pointHit[2];
	for (int p = 0; p < 2; p++) {
		pointHit[p].pos.x = gaugeP[p].pos.x;
		pointHit[p].pos.y = gaugeP[p].pos.y;
		pointHit[p].size.x = 32, pointHit[p].size.y = 32;
	}


	Obstacle obstacle[5];
	for (int i = 0; i < 5; i++) {
		obstacle[i].pos.x = float(rand() % 1016); obstacle[i].pos.y = 0;
		obstacle[i].speed = float(rand() % 8 + 9);
		obstacle[i].isAlive = false;
	}

	Hit obHit[5];
	for (int i = 0; i < 5; i++) {
		obHit[i].pos.x = obstacle[i].pos.x;
		obHit[i].pos.y = obstacle[i].pos.y;
		obHit[i].size.x = 60, obHit[i].size.y = 52;
	}


	Door door;
	door.pos.x = float(rand() % 1016);
	door.pos.y = 624;

	Hit doorHit;
	doorHit.pos.x = door.pos.x;
	doorHit.pos.y = door.pos.y;
	doorHit.size.x = 84, doorHit.size.y = 96;

	GameTime gametime;
	gametime.pos.x = 550, gametime.pos.y = 0;
	gametime.sizeX = 30, gametime.sizeY = 20;

	//===================================================================================================================

	int gameTimer = 60;
	int miniTmer = 20;

	int i = 0;
	int p = 0;

	int enter = 0;
	int space = 0;

	int rT = 0;
	int rTimer = 9;

	int lT = 0;
	int lTimer = 9;

	int t = 0;
	int textTimer = 30;

	int goalTimer = 1300;
	int transTimer = 100;

	int pTimer[2] = { 0,0 };
	int oTimer[5] = { 0,0,0,0,0 };

	bool rTrans = false;
	bool lTrans = true;
	bool isHit = true;

	bool isGoal = true;

	bool isAlive = true;

	bool isHitGauge = false;

	bool isHitOb = false;

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

		if (Novice::IsPlayingAudio(voiceHandle1) == 0) {
			voiceHandle1 = Novice::PlayAudio(soundHandle1, true, 0.5f);
		}

		enum Scane {
			TITLE,
			GAME,
			GAMECLEAR,
			GAMEOVER
		};

		switch (enter) {
		case TITLE:

			Novice::DrawSprite((int)title[0].x, (int)title[0].y, titleGhd, 1, 1, 0.0f, 0xFFFFFFFF);

			if (enter == 0) {
				Novice::DrawSprite((int)title[1].x, (int)title[1].y, titleName[t], 1, 1, 0.0f, 0xFFFFFFFF);
				textTimer = textTimer - 1;
				if (textTimer <= 0) {
					t = t + 1;
					textTimer = 30;
					if (t >= 2) {
						t = 0;
					}
				}
			}

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				enter = GAME;
			}

			i = 0;
			p = 0;

			player.pos.x = 50, player.pos.y = 620;

			gauge1.pos.x = 1110, gauge1.pos.y = 249;

			rT = 0;
			rTimer = 9;

			lT = 0;
			lTimer = 9;

			gameTimer = 60;
			miniTmer = 20;

			goalTimer = 1300;
			transTimer = 150;

			rTrans = false;
			lTrans = true;
			isHit = true;

			isGoal = true;

			isAlive = true;

			break;

		case GAME:
			Novice::DrawBox((int)background[0].pos.x, (int)background[0].pos.y, (int)background[0].width, (int)background[0].height, 0.0f, WHITE, kFillModeSolid);
			Novice::DrawSprite((int)background[1].pos.x, (int)background[1].pos.y, fuelGhd[2], 1, 1, 0.0f, WHITE);
			Novice::DrawBox((int)background[2].pos.x, (int)background[2].pos.y, (int)background[2].width, (int)background[2].height, 0.0f, WHITE, kFillModeSolid);

			//===================================================================================================================
			//プレイヤーの動き
			//===================================================================================================================
			if (space == 0) {
				player.pos.x += player.speed;
				if (player.pos.x >= 1016) {
					space = 1;
				}
			}

			if (space == 0 && keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				space = 1;
			}
			else if (space == 1 && keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				space = 0;
			}

			if (space == 1) {
				player.pos.x -= player.speed;
				if (player.pos.x <= -33) {
					space = 0;
				}
			}

			if (space == 0) {
				rTrans = false;
				if (rTrans == false) {
					Novice::DrawSprite((int)player.pos.x, (int)player.pos.y, rightRun[rT], 1, 1, 0.0f, WHITE);
				}

				rTimer = rTimer - 1;
				if (rTimer <= 0) {
					rT = rT + 1;
					rTimer = 9;
					if (rT >= 2) {
						rT = 0;
					}
				}
			}

			if (space == 1) {
				lTrans = false;
				if (lTrans == false) {
					Novice::DrawSprite((int)player.pos.x, (int)player.pos.y, leftRun[lT], 1, 1, 0.0f, WHITE);
				}

				rTrans = true;

				lTimer = lTimer - 1;
				if (lTimer <= 0) {
					lT = lT + 1;
					lTimer = 9;
					if (lT >= 2) {
						lT = 0;
					}
				}
			}


			//===================================================================================================================
			//燃料の減り
			//===================================================================================================================
			if (space == 0) {
				gauge1.pos.y += gauge1.speed;
			}
			else if (space == 1) {
				gauge1.pos.y += gauge1.speed;
			}


			Novice::DrawBox((int)gauge1.pos.x, (int)gauge1.pos.y, (int)gauge1.sizeX, (int)gauge1.sizeY, 0.0f, GREEN, kFillModeSolid);
			Novice::DrawSprite((int)transBox.pos.x, (int)transBox.pos.y, fuelGhd[2], 1, 1, 0.0f, WHITE);

			Novice::DrawSprite((int)fuelBack.pos.x, (int)fuelBack.pos.y, fuelGhd[1], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite((int)fuel.pos.x, (int)fuel.pos.y, fuelGhd[0], 1, 1, 0.0f, WHITE);

			if (gauge1.pos.y >= 521) {
				enter = GAMEOVER;
			}


			headHit.pos.x = player.pos.x;
			headHit.pos.y = player.pos.y;

			bodyHit.pos.x = player.pos.x;
			bodyHit.pos.y = player.pos.y;
			if (isHit == false) {
				Novice::DrawBox((int)headHit.pos.x + 36, (int)headHit.pos.y, (int)headHit.size.x, (int)headHit.size.y, 0.0f, RED, kFillModeWireFrame);
				Novice::DrawBox((int)bodyHit.pos.x + 31, (int)bodyHit.pos.y + 31, (int)bodyHit.size.x, (int)bodyHit.size.y, 0.0f, RED, kFillModeWireFrame);
			}


			//===================================================================================================================
			//扉の処理
			//===================================================================================================================
			goalTimer--;
			if (goalTimer <= 0) {
				doorHit.pos.x = door.pos.x;
				doorHit.pos.y = door.pos.y;
				isGoal = false;
				if (isGoal == false) {
					Novice::DrawSprite((int)door.pos.x, (int)door.pos.y, doorGhd, 1, 1, 0.0f, WHITE);

					if (isHit == false) {
						Novice::DrawBox((int)doorHit.pos.x + 6, (int)doorHit.pos.y, (int)doorHit.size.x, (int)doorHit.size.y, 0.0f, RED, kFillModeWireFrame);
					}

					if (keys[DIK_SPACE] && preKeys[DIK_SPACE] && bodyHit.pos.x + 31 < doorHit.pos.x + 6 + doorHit.size.x && doorHit.pos.x + 6 < bodyHit.pos.x + 31 + bodyHit.size.x) {
						enter = GAMECLEAR;
					}
				}
			}
			if (goalTimer <= 0) {
				transTimer--;
				if (transTimer <= 0) {
					isGoal = true;
					goalTimer = 1300;
					if (goalTimer == 1300) {
						door.pos.x = float(rand() % 1016);
						transTimer = 150;
					}
				}
			}

			//===================================================================================================================
			//ランダム障害物
			//===================================================================================================================
			for (i = 0; i < 5; i++) {
				oTimer[i]++;
				Novice::ScreenPrintf(100, 100, "Timer:%d", oTimer[i]++);

				if (i == 0)
				{
					isAlive = false;
					if (i == 0) {
						isAlive = true;
						obstacle[i].pos.y += obstacle[i].speed;

						obHit[i].pos.x = obstacle[i].pos.x;
						obHit[i].pos.y = obstacle[i].pos.y;

						Novice::DrawSprite((int)obstacle[i].pos.x, (int)obstacle[i].pos.y, obstacleGhd, 1, 1, 0.0f, WHITE);

						if (isHit == false) {
							Novice::DrawBox((int)obHit[i].pos.x + 2, (int)obHit[i].pos.y + 2, (int)obHit[i].size.x, (int)obHit[i].size.y, 0.0f, RED, kFillModeWireFrame);
						}

						if (obstacle[i].pos.y >= 720) {
							obstacle[i].pos.x = (float)(rand() % 1016);
							obstacle[i].pos.y = 0;
						}
					}
				}

				if (i == 1) {
					isAlive = false;

					if (oTimer[i] >= 200) {
						obstacle[i].pos.y += obstacle[i].speed;
						isAlive = true;

						obHit[i].pos.x = obstacle[i].pos.x;
						obHit[i].pos.y = obstacle[i].pos.y;

						Novice::DrawSprite((int)obstacle[i].pos.x, (int)obstacle[i].pos.y, obstacleGhd, 1, 1, 0.0f, WHITE);

						if (isHit == false) {
							Novice::DrawBox((int)obHit[i].pos.x + 2, (int)obHit[i].pos.y + 2, (int)obHit[i].size.x, (int)obHit[i].size.y, 0.0f, RED, kFillModeWireFrame);
						}
					}
				}
				if (i == 2) {
					isAlive = false;

					if (oTimer[i] > 250) {
						obstacle[i].pos.y += obstacle[i].speed;
						isAlive = true;

						obHit[i].pos.x = obstacle[i].pos.x;
						obHit[i].pos.y = obstacle[i].pos.y;

						Novice::DrawSprite((int)obstacle[i].pos.x, (int)obstacle[i].pos.y, obstacleGhd, 1, 1, 0.0f, WHITE);

						if (isHit == false) {
							Novice::DrawBox((int)obHit[i].pos.x + 2, (int)obHit[i].pos.y + 2, (int)obHit[i].size.x, (int)obHit[i].size.y, 0.0f, RED, kFillModeWireFrame);
						}
					}
				}
				if (i == 3) {
					isAlive = false;

					if (oTimer[i] > 150) {
						obstacle[i].pos.y += obstacle[i].speed;
						isAlive = true;

						obHit[i].pos.x = obstacle[i].pos.x;
						obHit[i].pos.y = obstacle[i].pos.y;

						Novice::DrawSprite((int)obstacle[i].pos.x, (int)obstacle[i].pos.y, obstacleGhd, 1, 1, 0.0f, WHITE);

						if (isHit == false) {
							Novice::DrawBox((int)obHit[i].pos.x + 2, (int)obHit[i].pos.y + 2, (int)obHit[i].size.x, (int)obHit[i].size.y, 0.0f, RED, kFillModeWireFrame);
						}
					}
				}
				if (i == 4) {
					isAlive = false;

					if (oTimer[i] > 100) {
						obstacle[i].pos.y += obstacle[i].speed;
						isAlive = true;

						obHit[i].pos.x = obstacle[i].pos.x;
						obHit[i].pos.y = obstacle[i].pos.y;

						Novice::DrawSprite((int)obstacle[i].pos.x, (int)obstacle[i].pos.y, obstacleGhd, 1, 1, 0.0f, WHITE);

						if (isHit == false) {
							Novice::DrawBox((int)obHit[i].pos.x + 2, (int)obHit[i].pos.y + 2, (int)obHit[i].size.x, (int)obHit[i].size.y, 0.0f, RED, kFillModeWireFrame);
						}
					}
				}
				if (i == 5) {
					isAlive = false;

					if (oTimer[i] > 270) {
						obstacle[i].pos.y += obstacle[i].speed;
						isAlive = true;

						obHit[i].pos.x = obstacle[i].pos.x;
						obHit[i].pos.y = obstacle[i].pos.y;

						Novice::DrawSprite((int)obstacle[i].pos.x, (int)obstacle[i].pos.y, obstacleGhd, 1, 1, 0.0f, WHITE);

						if (isHit == false) {
							Novice::DrawBox((int)obHit[i].pos.x + 2, (int)obHit[i].pos.y + 2, (int)obHit[i].size.x, (int)obHit[i].size.y, 0.0f, RED, kFillModeWireFrame);
						}
					}
				}

				if (obstacle[i].pos.y >= 720) {

					obstacle[i].pos.x = (float)(rand() % 1016);
					obstacle[i].pos.y = 0;
				}


				if (headHit.pos.x + 36 < obHit[i].pos.x + 2 + obHit[i].size.x && obHit[i].pos.x + 2 < headHit.pos.x + 36 + headHit.size.x &&
					headHit.pos.y < obHit[i].pos.y + 2 + obHit[i].size.y) {

					/*if (Novice::IsPlayingAudio(voiceHandle2) == 1) {
						voiceHandle2 = Novice::PlayAudio(soundHandle2, true, 0.5f);
					}
					else { Novice::StopAudio(voiceHandle2); }*/

					isHitOb = true;
					if (isHitOb == true) {
						gauge1.pos.y += 3;
						if (gauge1.pos.y <= 522) {
							gauge1.pos.y -= gauge1.speed;
						}
					}
				}
			}


			//===================================================================================================================
			//ランダムエナジー
			//===================================================================================================================
			for (p = 0; p < 2; p++) {
				pTimer[p]++;
				Novice::ScreenPrintf(100, 100, "Timer:%d", pTimer[p]++);

				if (p == 0)
				{
					isAlive = false;
					if (p == 0) {
						isAlive = true;
						gaugeP[p].pos.y += gaugeP[p].speed;

						pointHit[p].pos.y = gaugeP[p].pos.y;
						pointHit[p].pos.x = gaugeP[p].pos.x;

						Novice::DrawSprite((int)gaugeP[p].pos.x, (int)gaugeP[p].pos.y, gaugePointGhd, 1, 1, 0.0f, WHITE);

						if (isHit == false) {
							Novice::DrawBox((int)pointHit[p].pos.x, (int)pointHit[p].pos.y, (int)pointHit[p].size.x, (int)pointHit[p].size.y, 0.0f, RED, kFillModeWireFrame);
						}

						if (gaugeP[p].pos.y >= 720) {
							gaugeP[p].pos.x = (float)(rand() % 1016);
							gaugeP[p].pos.y = 0;
						}
					}
				}

				if (p == 1) {
					isAlive = false;

					if (pTimer[p] >= 200) {
						gaugeP[p].pos.y += gaugeP[p].speed;
						isAlive = true;

						pointHit[p].pos.x = gaugeP[p].pos.x;
						pointHit[p].pos.y = gaugeP[p].pos.y;

						Novice::DrawSprite((int)gaugeP[p].pos.x, (int)gaugeP[p].pos.y, gaugePointGhd, 1, 1, 0.0f, WHITE);

						if (isHit == false) {
							Novice::DrawBox((int)pointHit[p].pos.x, (int)pointHit[p].pos.y, (int)pointHit[p].size.x, (int)pointHit[p].size.y, 0.0f, RED, kFillModeWireFrame);
						}
					}
				}

				if (gaugeP[p].pos.y >= 720) {

					gaugeP[p].pos.x = (float)(rand() % 1016);
					gaugeP[p].pos.y = 0;
				}


				if (gauge1.pos.y >= 249 && headHit.pos.x + 36 < pointHit[p].pos.x + pointHit[p].size.x && pointHit[p].pos.x < headHit.pos.x + 36 + headHit.size.x &&
					headHit.pos.y < pointHit[p].pos.y + pointHit[p].size.y && pointHit[p].pos.y < headHit.pos.y + headHit.size.y) {
					isHitGauge = true;
					if (isHitGauge == true) {
						gauge1.pos.y -= 10;
						if (gauge1.pos.y >= 249) {
							gauge1.pos.y += gauge1.speed;
						}
					}
				}
			}


			//===================================================================================================================
			//制限時間
			//===================================================================================================================
			miniTmer--;
			if (miniTmer <= 0) {
				gameTimer -= 1;
				miniTmer = 60;
			}
			if (gameTimer <= 0) {
				enter = GAMEOVER;
			}

			Novice::DrawBox((int)gametime.pos.x, (int)gametime.pos.y, (int)gametime.sizeX, (int)gametime.sizeY, 0.0f, 0x489898, kFillModeSolid);
			Novice::ScreenPrintf(556, 0, "%d", gameTimer);


			break;

		case GAMECLEAR:

			Novice::DrawSprite((int)clearScreen.pos.x, (int)clearScreen.pos.y, clearGhd, 1, 1, 0.0f, WHITE);

			Novice::StopAudio(voiceHandle1);

			break;

		case GAMEOVER:

			Novice::DrawSprite((int)overScreen.pos.x, (int)overScreen.pos.y, overGhd, 1, 1, 0.0f, WHITE);

			Novice::StopAudio(voiceHandle1);

			break;

		default:
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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
