#include <bangtal>
using namespace bangtal;
#include <stdlib.h>
#include <time.h>

SceneID scene1, scene2, scene3, round1, round2, round3;
ObjectID direction[8];
int direction_num[8];
int direction_location[8] = { 50, 210, 370, 530, 690, 850, 1010, 1170 };
ObjectID start, restart, continue1, continue2;
ObjectID dance1, dance2, dance3, dance4, dance5;
int num = 0;
int roundnum = 0;
TimerID timer;

//랜덤으로 숫자 지정하는 함수 만듦
int which_direction() {
	int direction;
	switch (rand() % 4) {
	case 0: direction = 0; break;
	case 1: direction = 1; break;
	case 2: direction = 2; break;
	case 3: direction = 3; break;
	}
	return direction;
}

void hidedance() {
	hideObject(dance1);
	hideObject(dance2);
	hideObject(dance3);
	hideObject(dance4);
	hideObject(dance5);
}

void mix() {
	//방향키 숫자 지정
	for (int i = 0; i < 8; i++) {
		direction_num[i] = which_direction();
		//지정한 숫자에 따라 이미지 지정
		if (direction_num[i] == 0) {
			direction[i] = createObject("Images\\up.png");
		}
		else if (direction_num[i] == 1) {
			direction[i] = createObject("Images\\down.png");
		}
		else if (direction_num[i] == 2) {
			direction[i] = createObject("Images\\left.png");
		}
		else if (direction_num[i] == 3) {
			direction[i] = createObject("Images\\right.png");
		}
		locateObject(direction[i], scene2, direction_location[i], 110);
		scaleObject(direction[i], 0.5f);
	}
}

void fail() {
	for (int i = 0; i < 8; i++) {
		enterScene(scene3);
		hideObject(start);
		showObject(restart);
		num = 0;
		stopTimer(timer);
		hideTimer();
		hidedance();
	}
}

void keyboardCallback(KeyCode code, KeyState state) {
	if (num == 8) {
		hidedance();
		if (roundnum == 0) {
			enterScene(round1);
			roundnum++;
			num = 0;
			stopTimer(timer);
			hideTimer();
		}
		else if (roundnum == 1) {
			enterScene(round2);
			roundnum++;
			num = 0;
			stopTimer(timer);
			hideTimer();
		}
		else if (roundnum == 2) {
			enterScene(round3);
			num = 0;
			stopTimer(timer);
			hideTimer();
		}
	}
	else {
		if (code == KeyCode::KEY_UP_ARROW && state == KeyState::KEY_PRESSED) {
			if (direction_num[num] == 0) {
				hideObject(direction[num++]);
				hidedance();
				showObject(dance1);
			}
			else {
				fail();
				showObject(dance1);
			}
		}
		else if (code == KeyCode::KEY_DOWN_ARROW && state == KeyState::KEY_PRESSED) {
			if (direction_num[num] == 1) {
				hideObject(direction[num++]);
				hidedance();
				showObject(dance2);
			}
			else {
				fail();
				showObject(dance2);
			}
		}
		else if (code == KeyCode::KEY_LEFT_ARROW && state == KeyState::KEY_PRESSED) {
			if (direction_num[num] == 2) {
				hideObject(direction[num++]);
				hidedance();
				showObject(dance3);
			}
			else {
				fail();
				showObject(dance3);
			}
		}
		else if (code == KeyCode::KEY_RIGHT_ARROW && state == KeyState::KEY_PRESSED) {
			if (direction_num[num] == 3) {
				hideObject(direction[num++]);
				hidedance();
				showObject(dance4);
			}
			else {
				fail();
				showObject(dance4);
			}
		}
	}
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == start || object == continue1 || object == continue2) { 
		hidedance();
		showObject(dance5);
		mix();
		for (int i = 0; i < 8; i++) {
			showObject(direction[i]);
		}
		setKeyboardCallback(keyboardCallback);
		enterScene(scene2);
		if (roundnum == 0) {
			timer = createTimer(8.0f);
			showTimer(timer);
			startTimer(timer);
		}
		
		else if (roundnum == 1) {
			setTimer(timer, 6.0f);
			showTimer(timer);
			startTimer(timer);
		}
		else if (roundnum == 2) {
			setTimer(timer, 4.0f);
			showTimer(timer);
			startTimer(timer);
		}
	}
	else if (object == restart) {
		hidedance();
		showObject(dance5);
		for (int i = 0; i < 8; i++) {
			showObject(direction[i]);
		}
		setKeyboardCallback(keyboardCallback);
		enterScene(scene2);
		if (roundnum == 0) {
			setTimer(timer, 8.0f);
			showTimer(timer);
			startTimer(timer);
		}
		else if (roundnum == 1) {
			setTimer(timer, 6.0f);
			showTimer(timer);
			startTimer(timer);
		}
		else if (roundnum == 2) {
			setTimer(timer, 4.0f);
			showTimer(timer);
			startTimer(timer);
		}
	}
}

void timerCallback(TimerID what) {
	if (what == timer) {
		fail();
	}
}

int main()
{
	srand(time(NULL));

	//setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	scene1 = createScene("배경1", "Images\\scene1.png");
	scene2 = createScene("배경2", "Images\\scene2.png");
	scene3 = createScene("배경3", "Images\\scene3.png");
	round1 = createScene("라운드1", "Images\\round.png");
	round2 = createScene("라운드2", "Images\\round.png");
	round3 = createScene("라운드3", "Images\\round3.png");

	continue1 = createObject("Images\\continue.png");
	locateObject(continue1, round1, 505, 85);
	showObject(continue1);

	continue2 = createObject("Images\\continue.png");
	locateObject(continue2, round2, 505, 85);
	showObject(continue2);

	start = createObject("Images\\start.png");
	locateObject(start, scene1, 500, 80);
	scaleObject(start, 0.5f);
	showObject(start);

	restart = createObject("Images\\restart.png");
	locateObject(restart, scene3, 545, 125);
	scaleObject(restart, 0.65f);

	dance1 = createObject("Images\\dance1.png");
	dance2 = createObject("Images\\dance2.png");
	dance3 = createObject("Images\\dance3.png");
	dance4 = createObject("Images\\dance4.png");
	dance5 = createObject("Images\\dance5.png");

	locateObject(dance1, scene2, 380, 200);
	locateObject(dance2, scene2, 380, 200);
	locateObject(dance3, scene2, 380, 200);
	locateObject(dance4, scene2, 380, 200);
	locateObject(dance5, scene2, 420, 220);
	scaleObject(dance5, 0.9f);

	startGame(scene1);
}