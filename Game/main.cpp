#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "Globals.h"
#include "Mob.h"
#include "Player.h"
#include "Scene.h"

#include <time.h>
#include <random>

void handlePlayerMovement(Player& player, float deltaTime, float rotateSpeed, float speed) {
	player.addEventListener(sf::Keyboard::Right, ROTATE, 1.f * deltaTime * rotateSpeed);
	player.addEventListener(sf::Keyboard::Left, ROTATE, -1.f * deltaTime * rotateSpeed);
	mat2 delta; delta[0][0] = 1.f; delta[1][0] = 0.f;
	delta = delta.rotate(player.getRotation() - 90, Z_AXIS);
	player.addEventListener(sf::Keyboard::Up, TRANSLATE, sf::Vector2f(delta[0][0] * deltaTime * speed, delta[1][0] * deltaTime * speed));

}

int main() {
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Infection", sf::Style::Close);

	TextObject title("img/Title.png", 265, 5);
	TextObject death("img/YouDied.png", 0, 160);
	TextObject ntos("(bacteria and virus not to scale)", W_WIDTH / 2.5f, W_HEIGHT / 1.1f, 10, sf::Color(30, 30, 30));
	TextObject howToPlayLine1("You are a virus that is trying to infect", W_WIDTH / 7.22f, W_HEIGHT / 7.f, 40, sf::Color(30, 30, 30));
	TextObject howToPlayLine2("a persons cells! You must select a level", W_WIDTH / 7.f, W_HEIGHT / 4.85f, 40, sf::Color(30, 30, 30));
	TextObject howToPlayLine3("as a way to get into the person. Avoid ", W_WIDTH / 7.f, W_HEIGHT / 3.7f, 40, sf::Color(30, 30, 30));
	TextObject howToPlayLine4("the immune systems defences to stay", W_WIDTH / 7.f, W_HEIGHT / 3.f, 40, sf::Color(30, 30, 30));
	TextObject howToPlayLine5("alive. Use the arrow keys to move.", W_WIDTH / 7.f, W_HEIGHT / 2.55f, 40, sf::Color(30, 30, 30));
	TextObject B_Cell_Text("B Cell", W_WIDTH / 6.1f, W_HEIGHT / 1.19f, 25, sf::Color(30, 30, 30));
	TextObject T_Cell_Text("T Cell", W_WIDTH / 2.65f, W_HEIGHT / 1.19f, 25, sf::Color(30, 30, 30));
	TextObject Antibody_Text("Antibody", W_WIDTH / 1.675f, W_HEIGHT / 1.19f, 25, sf::Color(30, 30, 30));
	TextObject HealthBarText("Protection: 100%", W_WIDTH / 1.2f, W_HEIGHT / 10.f, 20, sf::Color(0, 0, 0));
	HealthBarText.setFont("fonts/AGENCYR.ttf");
	TextObject youWinText("You just infected a person!", 70, W_HEIGHT / 2.3f, 67, sf::Color(0, 0, 0));
	TextObject PhagocyteText("Phagocyte", W_WIDTH / 1.2f, W_HEIGHT / 1.19f, 25, sf::Color(30, 30, 30));
	
	TextButton playButton("Play!", W_WIDTH / 2.25f, W_HEIGHT / 3.5f, 50, sf::Color(30, 30, 30), sf::Color(255, 0, 0));
	TextButton HTPB("How To Play", W_WIDTH / 2.903f, W_HEIGHT / 2.f, 50, sf::Color(30, 30, 30), sf::Color(255, 0, 0));
	TextButton LevelButton("Level Select", W_WIDTH / 2.881f, W_HEIGHT / 1.35f, 50, sf::Color(30, 30, 30), sf::Color(255, 0, 0));
	TextButton noseLevel("Level 1: Nose", W_WIDTH / 3.05f, W_HEIGHT / 4.f, 50, sf::Color(30, 30, 30), sf::Color(255, 0, 0));
	TextButton skinLevel("Level 2: Skin", W_WIDTH / 2.94f, W_HEIGHT / 1.5f, 50, sf::Color(30, 30, 30), sf::Color(255, 0, 0));
	TextButton nextLevelButton("Next Level", W_WIDTH / 2.5f, W_HEIGHT / 1.7f, 50, sf::Color(0, 0, 0), sf::Color(255, 0, 0));

	NavigationButton backArrow1("img/BackArrow.png", "img/BackArrowRed.png", 0, 5, sf::Vector2f(0.5f, 0.4f));

	Entity B_Cell_Icon("img/B_Cell.png", W_WIDTH / 7.f, W_HEIGHT / 1.7f);
	B_Cell_Icon.scale(sf::Vector2f(0.5, 0.5));
	Entity T_Cell_Icon("img/T_Cell.png", W_WIDTH / 3.f, W_HEIGHT / 1.75f);
	T_Cell_Icon.scale(sf::Vector2f(0.5, 0.5));
	Entity Antibody_Icon("img/Antibody.png", W_WIDTH / 1.85f, W_HEIGHT / 1.83f);
	Antibody_Icon.scale(sf::Vector2f(1.1f, 1.1f));
	Entity phagocyteIcon("img/Phagocyte.png", W_WIDTH / 1.3f, W_HEIGHT / 1.83);
	phagocyteIcon.scale(sf::Vector2f(0.25f, 0.25f));

	Entity Nose("img/Nose.png", 0, 0);
	Nose.setTextureRect(0, 0, 600, 600);
	Nose.scale(sf::Vector2f(1.2, 1.2));
	Entity Nose1("img/Nose1.png", 0, 0);
	Nose1.scale(sf::Vector2f(1.2, 1.2));
	Entity healthBar("img/HealthBar.png", W_WIDTH - 220, 20);
	healthBar.setBorder(sf::Color::Black, 3);
	healthBar.useBorder(true);
	Entity mainBackground("img/InnerNose.png", 0, 0);
	Entity mainCell("img/Cell.png", 0, 0);

	std::vector<Mob*> skinLevelMobs;
	Mob skin1("img/Skin.png", 0, W_HEIGHT - 100);
	skin1.scale(sf::Vector2f(4.f/9.f, 4.f/9.f));
	Mob skin2("img/Skin.png", W_WIDTH - 380, W_HEIGHT - 100);
	skin2.scale(sf::Vector2f(4.f / 9.f, 4.f / 9.f));
	skinLevelMobs.push_back(&skin1);
	skinLevelMobs.push_back(&skin2);

	Mob vessle1("img/Inflammation.png", 0, 0);
	Mob vessle2("img/Inflammation.png", 0, W_HEIGHT - 150);

	Player player("img/Virus.png", W_WIDTH / 1.1f, W_HEIGHT / 4.f, CENTER);
	player.rotate(180.f);
	player.scale(sf::Vector2f(0.5, 0.5));
	float rotateSpeed = 80.f;
	float speed = 120.f;

	std::vector<Mob*> mobs;

	//top
	Mob noseHair1("img/NoseHair.png", W_WIDTH - 200, W_HEIGHT - 100);
	Mob noseHair2("img/NoseHair.png", W_WIDTH - 400, W_HEIGHT - 200);
	noseHair2.scale(sf::Vector2f(1.f, 2.f));
	Mob noseHair3("img/NoseHair.png", W_WIDTH - 600, W_HEIGHT - 150);
	noseHair3.scale(sf::Vector2f(1.f, 1.5f));
	Mob noseHair4("img/NoseHair.png", W_WIDTH - 700, W_HEIGHT - 170);
	noseHair4.scale(sf::Vector2f(1.f, 1.7f));
	Mob noseHair5("img/NoseHair.png", W_WIDTH - 830, W_HEIGHT - 100);

	//bottom
	Mob noseHair6("img/NoseHair.png", W_WIDTH - 240, 300);
	noseHair6.scale(sf::Vector2f(1.f, -3.f));
	Mob noseHair7("img/NoseHair.png", W_WIDTH - 370, 200);
	noseHair7.scale(sf::Vector2f(1.f, -2.f));
	Mob noseHair8("img/NoseHair.png", W_WIDTH - 516, 250);
	noseHair8.scale(sf::Vector2f(1.f, -2.5f));
	Mob noseHair9("img/NoseHair.png", W_WIDTH - 685, 230);
	noseHair9.scale(sf::Vector2f(1.f, -2.3f));
	Mob noseHair10("img/NoseHair.png", W_WIDTH - 812, 300);
	noseHair10.scale(sf::Vector2f(1.f, -3.f));

	//Mucus
	Mob mucus1("img/Mucus.png", rand() % 700, rand() % 550, CENTER);
	mucus1.scale(sf::Vector2f(0.5f, 0.5f));
	Mob mucus2("img/Mucus.png", rand() % 700, rand() % 550, CENTER);
	mucus2.scale(sf::Vector2f(0.5f, 0.5f));
	Mob mucus3("img/Mucus.png", rand() % 700, rand() % 550, CENTER);
	mucus3.scale(sf::Vector2f(0.5f, 0.5f));
	Mob mucus4("img/Mucus.png", rand() % 700, rand() % 550, CENTER);
	mucus4.scale(sf::Vector2f(0.5f, 0.5f));
	Mob mucus5("img/Mucus.png", rand() % 700, rand() % 550, CENTER);
	mucus5.scale(sf::Vector2f(0.5f, 0.5f));
	Mob mucus6("img/Mucus.png", rand() % 700, rand() % 550, CENTER);
	mucus6.scale(sf::Vector2f(0.5f, 0.5f));
	Mob mucus7("img/Mucus.png", rand() % 700, rand() % 550, CENTER);
	mucus7.scale(sf::Vector2f(0.5f, 0.5f));
	Mob mucus8("img/Mucus.png", rand() % 700, rand() % 550, CENTER);
	mucus8.scale(sf::Vector2f(0.5f, 0.5f));
	Mob mucus9("img/Mucus.png", rand() % 700, rand() % 550, CENTER);
	mucus9.scale(sf::Vector2f(0.5f, 0.5f));
	Mob mucus10("img/Mucus.png", rand() % 700, rand() % 550, CENTER);
	mucus10.scale(sf::Vector2f(0.5f, 0.5f));

	//T Cells
	Mob Tcell1("img/T_Cell.png", rand() % 750, rand() % 550, CENTER);
	Tcell1.scale(sf::Vector2f(0.25, 0.25));
	Mob Tcell2("img/T_Cell.png", rand() % 750, rand() % 550, CENTER);
	Tcell2.scale(sf::Vector2f(0.25, 0.25));
	Mob Tcell3("img/T_Cell.png", rand() % 750, rand() % 550, CENTER);
	Tcell3.scale(sf::Vector2f(0.25, 0.25));
	Mob Tcell4("img/T_Cell.png", rand() % 750, rand() % 550, CENTER);
	Tcell4.scale(sf::Vector2f(0.25, 0.25));
	Mob Tcell5("img/T_Cell.png", rand() % 750, rand() % 550, CENTER);
	Tcell5.scale(sf::Vector2f(0.25, 0.25));

	//B cells
	Mob Bcell1("img/B_Cell.png", rand() % 750, rand() % 550, CENTER);
	Bcell1.scale(sf::Vector2f(0.25, 0.25));
	Mob Bcell2("img/B_Cell.png", rand() % 750, rand() % 550, CENTER);
	Bcell2.scale(sf::Vector2f(0.25, 0.25));
	Mob Bcell3("img/B_Cell.png", rand() % 750, rand() % 550, CENTER);
	Bcell3.scale(sf::Vector2f(0.25, 0.25));
	Mob Bcell4("img/B_Cell.png", rand() % 750, rand() % 550, CENTER);
	Bcell4.scale(sf::Vector2f(0.25, 0.25));
	Mob Bcell5("img/B_Cell.png", rand() % 750, rand() % 550, CENTER);
	Bcell5.scale(sf::Vector2f(0.25, 0.25));

	Mob antibody("img/Antibody.png", 300, W_HEIGHT / 3.f);

	mobs.push_back(&noseHair1);
	mobs.push_back(&noseHair2);
	mobs.push_back(&noseHair3);
	mobs.push_back(&noseHair4);
	mobs.push_back(&noseHair5);
	mobs.push_back(&noseHair6);
	mobs.push_back(&noseHair7);
	mobs.push_back(&noseHair8);
	mobs.push_back(&noseHair9);
	mobs.push_back(&noseHair10);

	mobs.push_back(&mucus1);
	mobs.push_back(&mucus2);
	mobs.push_back(&mucus3);
	mobs.push_back(&mucus4);
	mobs.push_back(&mucus5);
	mobs.push_back(&mucus6);
	mobs.push_back(&mucus7);
	mobs.push_back(&mucus8);
	mobs.push_back(&mucus9);
	mobs.push_back(&mucus10);

	mobs.push_back(&Bcell1);
	mobs.push_back(&Bcell2);
	mobs.push_back(&Bcell3);
	mobs.push_back(&Bcell4);
	mobs.push_back(&Bcell5);
	mobs.push_back(&Tcell1);
	mobs.push_back(&Tcell2);
	mobs.push_back(&Tcell3);
	mobs.push_back(&Tcell4);
	mobs.push_back(&Tcell5);

	std::vector<float> rotations;
	for (int i = 0; i < 10; i++) {
		rotations.push_back(1.f / (rand() % 36) * 500.f);
	}
	std::vector<sf::Vector2f> translations;
	sf::Vector2f vec1((rand() % 30) * (rand() % 3) * (rand() % 2 * -1), (rand() % 30) * (rand() % 3) * (rand() % 2 * -1));
	sf::Vector2f vec2((rand() % 30) * (rand() % 3) * (rand() % 2 * -1), (rand() % 30) * (rand() % 3) * (rand() % 2 * -1));
	sf::Vector2f vec3((rand() % 30) * (rand() % 3) * (rand() % 2 * -1), (rand() % 30) * (rand() % 3) * (rand() % 2 * -1));
	sf::Vector2f vec4((rand() % 30) * (rand() % 3) * (rand() % 2 * -1), (rand() % 30) * (rand() % 3) * (rand() % 2 * -1));
	sf::Vector2f vec5((rand() % 30) * (rand() % 3) * (rand() % 2 * -1), (rand() % 30) * (rand() % 3) * (rand() % 2 * -1));
	sf::Vector2f vec6((rand() % 30) * (rand() % 3) * (rand() % 2 * -1), (rand() % 30) * (rand() % 3) * (rand() % 2 * -1));
	sf::Vector2f vec7((rand() % 30) * (rand() % 3) * (rand() % 2 * -1), (rand() % 30) * (rand() % 3) * (rand() % 2 * -1));
	sf::Vector2f vec8((rand() % 30) * (rand() % 3) * (rand() % 2 * -1), (rand() % 30) * (rand() % 3) * (rand() % 2 * -1));
	sf::Vector2f vec9((rand() % 30) * (rand() % 3) * (rand() % 2 * -1), (rand() % 30) * (rand() % 3) * (rand() % 2 * -1));
	sf::Vector2f vec10((rand() % 30) * (rand() % 3) * (rand() % 2 * -1), (rand() % 30) * (rand() % 3) * (rand() % 2 * -1));
	translations.push_back(vec1);
	translations.push_back(vec2);
	translations.push_back(vec3);
	translations.push_back(vec4);
	translations.push_back(vec5);
	translations.push_back(vec6);
	translations.push_back(vec7);
	translations.push_back(vec8);
	translations.push_back(vec9);
	translations.push_back(vec10);

	Mob phagocyte("img/Phagocyte.png", 150, W_HEIGHT / 2.5f);
	phagocyte.scale(sf::Vector2f(0.2, 0.2));

	Scene homeScreen;
	homeScreen.addTextObject(&playButton);
	homeScreen.addTextObject(&HTPB);
	homeScreen.addTextObject(&LevelButton);
	homeScreen.addTextObject(&title);
	homeScreen.addTextObject(&ntos);

	Scene howToPlayScreen;
	howToPlayScreen.addNavigationButton(&backArrow1);
	howToPlayScreen.addTextObject(&howToPlayLine1);
	howToPlayScreen.addTextObject(&howToPlayLine2);
	howToPlayScreen.addTextObject(&howToPlayLine3);
	howToPlayScreen.addTextObject(&howToPlayLine4);
	howToPlayScreen.addTextObject(&howToPlayLine5);
	howToPlayScreen.addTextObject(&T_Cell_Text);
	howToPlayScreen.addTextObject(&B_Cell_Text);
	howToPlayScreen.addTextObject(&Antibody_Text);
	howToPlayScreen.addEntity(&B_Cell_Icon);
	howToPlayScreen.addEntity(&T_Cell_Icon);
	howToPlayScreen.addEntity(&Antibody_Icon);
	howToPlayScreen.addEntity(&phagocyteIcon);
	howToPlayScreen.addTextObject(&PhagocyteText);

	Scene levelSelectScreen;
	levelSelectScreen.addNavigationButton(&backArrow1);
	levelSelectScreen.addTextObject(&noseLevel);
	levelSelectScreen.addTextObject(&skinLevel);

	Scene NoseLevel;
	NoseLevel.addEntity(&Nose1);
	NoseLevel.addEntity(&player);
	NoseLevel.addEntity(&Nose);
	NoseLevel.addEntity(&healthBar);
	NoseLevel.addTextObject(&HealthBarText);

	Scene NoseLevelInner1;
	NoseLevelInner1.addEntity(&mainBackground);
	NoseLevelInner1.addEntity(&player);
	NoseLevelInner1.addEntity(&healthBar);
	NoseLevelInner1.addTextObject(&HealthBarText);
	for (int i = 0; i < mobs.size() - 10; i++) {
		if (i < 10) {
			mobs[i]->setEffects(0.01f, 0.f);
		}
		if (i > 9 && i < 20) {
			mobs[i]->setEffects(0.005f, 0.0005f);
		}
		NoseLevelInner1.addEntity(mobs[i]);
	}

	Scene finalScene;
	finalScene.addEntity(&mainBackground);
	finalScene.addEntity(&mainCell);
	for (int i = 20; i < mobs.size(); i++) {
		finalScene.addEntity(mobs[i]);
		mobs[i]->setEffects(0.01f, 0.f);
	}
	finalScene.addEntity(&antibody);
	antibody.setEffects(0.05f, 0.f);
	finalScene.addEntity(&player);
	finalScene.addEntity(&healthBar);
	finalScene.addTextObject(&HealthBarText);

	Scene GameOverScene;
	GameOverScene.addTextObject(&death);

	Scene LevelCompleteScene;
	LevelCompleteScene.addTextObject(&youWinText);
	LevelCompleteScene.addTextObject(&nextLevelButton);

	Scene skinScene1;
	for (int i = 0; i < skinLevelMobs.size(); i++) {
		skinScene1.addEntity(skinLevelMobs[i]);
	}
	skinScene1.addEntity(&player);
	skinScene1.addEntity(&healthBar);
	skinScene1.addTextObject(&HealthBarText);

	Scene skinScene2;
	skinScene2.addEntity(&mainBackground);
	skinScene2.addEntity(&vessle1);
	skinScene2.addEntity(&vessle2);
	skinScene2.addEntity(&phagocyte);
	phagocyte.setEffects(0.05f, 0.f);
	skinScene2.addEntity(&player);
	skinScene2.addEntity(&healthBar);
	skinScene2.addTextObject(&HealthBarText);

	TextButton quitButton("Quit", W_WIDTH / 2.2f, W_HEIGHT / 1.5f, 50, sf::Color(0, 0, 0), sf::Color(255, 0, 0));

	Scene endGame;
	endGame.addTextObject(&youWinText);
	endGame.addTextObject(&quitButton);

	bool onHomeScreen = true;
	bool onHowToPlayScreen = false;
	bool onLevelSelect = false;
	bool isDead = false;
	bool levelComplete = false;
	short int currentLevel = -1;
	short int currentLevelScene = 0;

	sf::Clock clock;
	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		sf::Event evt;
		while (window.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				window.close();
			}
			bool playClicked = playButton.isClicked(evt, window);
			bool HTPBclicked = HTPB.isClicked(evt, window);
			bool levelButtonClicked = LevelButton.isClicked(evt, window);
			bool backButton1Clicked = backArrow1.isClicked(evt, window);
			bool noseLevelClicked = noseLevel.isClicked(evt, window);
			bool skinLevelClicked = skinLevel.isClicked(evt, window);
			bool nextLevelClicked = nextLevelButton.isClicked(evt, window);
			bool quitPressed = quitButton.isClicked(evt, window);

			if (!onHomeScreen && currentLevel < 0) {
				if (backButton1Clicked) {
					onHowToPlayScreen = false;
					onLevelSelect = false;
					onHomeScreen = true;
				}
			}

			if (onHomeScreen) {
				if (HTPBclicked) {
					onHomeScreen = false;
					onHowToPlayScreen = true;
				}
				if (levelButtonClicked) {
					onHomeScreen = false;
					onLevelSelect = true;
				}
				if (playClicked) {
					onHomeScreen = false;
					currentLevel = 0;
				}
			}
			if (onLevelSelect) {
				if (noseLevelClicked) {
					onHomeScreen = false;
					onLevelSelect = false;
					currentLevel = 0;
				}
				if (skinLevelClicked) {
					onHomeScreen = false;
					onLevelSelect = false;
					player.setRotation(90.f);
					player.setPosition(sf::Vector2f(40, W_HEIGHT / 2.f));
					player.setHealth(100.f);
					currentLevelScene = 0;
					levelComplete = false;
					currentLevel = 1;
				}
			}
			if (levelComplete) {
				if (nextLevelClicked) {
					player.setRotation(90.f);
					player.setPosition(sf::Vector2f(40, W_HEIGHT / 2.f));
					player.setHealth(100.f);
					currentLevelScene = 0;
					levelComplete = false;
					currentLevel = 1;
				}
			}
			if (currentLevel == 1 && levelComplete == true) {
				if (quitPressed) {
					window.close();
				}
			}
		}

		window.clear(sf::Color(240, 240, 240));

		if (onHomeScreen) {
			homeScreen.renderAll(window);
		}
		if (onHowToPlayScreen) {
			howToPlayScreen.renderAll(window);
		}
		if (onLevelSelect) {
			levelSelectScreen.renderAll(window);
		}
		if (currentLevel == 0) {
			if (!isDead && !levelComplete) {
				player.damage(0.001);
			}
			HealthBarText.setText("Protection: " + std::to_string((int)player.getCurrentHealth()) + "%");
			healthBar.setTextureRect(0, 0, (int)player.getCurrentHealth() * 2, 20);
			if (player.getCurrentHealth() == 0) {
				isDead = true;
			}
			if (currentLevelScene == 0) {
				handlePlayerMovement(player, deltaTime, rotateSpeed, speed);
				NoseLevel.renderAll(window);
				if (player.getPosition().x < 438 && player.getPosition().y < 406) {
					currentLevelScene = 1;
					player.setRotation(-90.f);
					player.setPosition(sf::Vector2f(W_WIDTH / 1.05f, W_HEIGHT / 2.f));
					player.setHealth(100.f);
					levelComplete = false;
				}
			}
			if (currentLevelScene == 1) {
				if (!isDead) {
					handlePlayerMovement(player, deltaTime, rotateSpeed, speed);
					for (int i = 0; i < mobs.size() - 10; i++) {
						if (mobs[i]->getGlobalBounds().intersects(player.getGlobalBounds())) {
							mobs[i]->applyEffects(player);
						}
						if (i > 9 && i < 20) {
							mobs[i]->rotate(rotations[i - 10] * deltaTime);
							mobs[i]->translate(translations[i - 10] * deltaTime);
							if (mobs[i]->getPosition().x > W_WIDTH - 25 || mobs[i]->getPosition().x < 0) {
								translations[i - 10].x *= -1;
							}
							if (mobs[i]->getPosition().y > W_HEIGHT - 25 || mobs[i]->getPosition().y < 0) {
								translations[i - 10].y *= -1;
							}
						}
					}
					if (player.getPosition().x < -65) {
						player.setRotation(-90.f);
						player.setPosition(sf::Vector2f(W_WIDTH / 1.05f, W_HEIGHT / 2.f));
						player.resetSpeed();
						currentLevelScene = 2;
					}
				}
				NoseLevelInner1.renderAll(window);
				if (isDead) {
					GameOverScene.renderAll(window);
				}
			}
			if (currentLevelScene == 2) {
				if (!isDead && !levelComplete) {
					handlePlayerMovement(player, deltaTime, rotateSpeed, speed);
					for (int i = 20; i < mobs.size(); i++) {
						if (mobs[i]->getGlobalBounds().intersects(player.getGlobalBounds())) {
							mobs[i]->applyEffects(player);
						}
						mobs[i]->rotate(rotations[i - 20] * deltaTime);
						mobs[i]->translate(translations[i - 20] * deltaTime);
						if (mobs[i]->getPosition().x > W_WIDTH - 25 || mobs[i]->getPosition().x < 0) {
							translations[i - 20].x *= -1;
						}
						if (mobs[i]->getPosition().y > W_HEIGHT - 25 || mobs[i]->getPosition().y < 0) {
							translations[i - 20].y *= -1;
						}
					}
					if (antibody.getGlobalBounds().intersects(player.getGlobalBounds())) {
						antibody.applyEffects(player);
					}
					antibody.follow(player, deltaTime, 80.f, false);
					if (player.getPosition().x < 60.f && (player.getPosition().y > 0.f && player.getPosition().y < W_HEIGHT - 40.f)) {
						levelComplete = true;
					}
				}
				finalScene.renderAll(window);
				if (isDead) {
					GameOverScene.renderAll(window);
				}
				if (levelComplete) {
					LevelCompleteScene.renderAll(window);
				}
			}
		}
		if (currentLevel == 1) {
			if (!isDead && !levelComplete) {
				player.damage(0.001);
			}
			HealthBarText.setText("Protection: " + std::to_string((int)player.getCurrentHealth()) + "%");
			healthBar.setTextureRect(0, 0, (int)player.getCurrentHealth() * 2, 20);
			if (player.getCurrentHealth() == 0) {
				isDead = true;
			}
			if (currentLevelScene == 0) {
				handlePlayerMovement(player, deltaTime, rotateSpeed, speed);
				if (player.getPosition().x < skin1.getGlobalBounds().width + skin1.getPosition().x) {
					if (player.getPosition().y > skin1.getPosition().y - (player.getGlobalBounds().height / 2.04f)) {
						player.setPosition(sf::Vector2f(player.getPosition().x, skin1.getPosition().y - (player.getGlobalBounds().height / 2.04f)));
					}
				}
				if (player.getPosition().x > skin2.getPosition().x) {
					if (player.getPosition().y > skin1.getPosition().y - (player.getGlobalBounds().height / 2.04f)) {
						player.setPosition(sf::Vector2f(player.getPosition().x, skin1.getPosition().y - (player.getGlobalBounds().height / 2.04f)));
					}
				}
				if (player.getPosition().y > W_HEIGHT + 30.f) {
					player.setRotation(-90.f);
					player.setPosition(sf::Vector2f(W_WIDTH / 1.05f, W_HEIGHT / 2.f));
					currentLevelScene = 1;
				}
				skinScene1.renderAll(window);
				if (isDead) {
					GameOverScene.renderAll(window);
				}
			}
			if (currentLevelScene == 1) {
				if (!isDead) {
					handlePlayerMovement(player, deltaTime, rotateSpeed, speed);
					float pos1 = vessle1.getPosition().y + vessle1.getGlobalBounds().height + player.getGlobalBounds().height / 2;
					float pos2 = vessle2.getPosition().y - player.getGlobalBounds().height / 2;
					if (player.getPosition().y < pos1) {
						player.setPosition(sf::Vector2f(player.getPosition().x, pos1));
					}
					if (player.getPosition().y > pos2) {
						player.setPosition(sf::Vector2f(player.getPosition().x, pos2));
					}
					phagocyte.follow(player, deltaTime, 80.f, true);
					if (phagocyte.getGlobalBounds().intersects(player.getGlobalBounds())) {
						phagocyte.applyEffects(player);
					}
					if (player.getPosition().x < -65) {
						player.setRotation(-90.f);
						player.setPosition(sf::Vector2f(W_WIDTH / 1.05f, W_HEIGHT / 2.f));
						currentLevelScene = 2;
					}
				}
				skinScene2.renderAll(window);
				if (isDead) {
					GameOverScene.renderAll(window);
				}
			}
			if (currentLevelScene == 2) {
				if (!isDead && !levelComplete) {
					handlePlayerMovement(player, deltaTime, rotateSpeed, speed);
					for (int i = 20; i < mobs.size(); i++) {
						if (mobs[i]->getGlobalBounds().intersects(player.getGlobalBounds())) {
							mobs[i]->applyEffects(player);
						}
						mobs[i]->rotate(rotations[i - 20] * deltaTime);
						mobs[i]->translate(translations[i - 20] * deltaTime);
						if (mobs[i]->getPosition().x > W_WIDTH - 25 || mobs[i]->getPosition().x < 0) {
							translations[i - 20].x *= -1;
						}
						if (mobs[i]->getPosition().y > W_HEIGHT - 25 || mobs[i]->getPosition().y < 0) {
							translations[i - 20].y *= -1;
						}
					}
					if (antibody.getGlobalBounds().intersects(player.getGlobalBounds())) {
						antibody.applyEffects(player);
					}
					antibody.follow(player, deltaTime, 80.f, false);
					if (player.getPosition().x < 60.f && (player.getPosition().y > 0.f && player.getPosition().y < W_HEIGHT - 40.f)) {
						levelComplete = true;
					}
				}
				finalScene.renderAll(window);
				if (isDead) {
					GameOverScene.renderAll(window);
				}
				if (levelComplete) {
					endGame.renderAll(window);
				}
			}
		}
		window.display();
	}
}