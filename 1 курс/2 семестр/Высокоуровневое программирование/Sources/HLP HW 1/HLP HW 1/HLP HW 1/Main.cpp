#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
//#include <SFML/Graphics.hpp>
#include <ctime>


using namespace sf;

const unsigned short FACES = 20;
const unsigned int CENTER_RADIUS = 5;
const float WINDOW_WIDTH = 1000;
const float WINDOW_HEIGTH = 500;
const float ROTATE_SPEED = 1000;
const float MOVE_SPEED = 0.1;

int main()
{
	setlocale(LC_ALL, "Russian");

	std::cout << "Введите радиус: ";
	float radius = 100; 
	//std::cin >> radius;
	
	std::cout << "Введите координаты центра: ";
	float centerX = 250; 
	float centerY = 250; 
	//std::cin >> centerX >> centerY;

	std::cout << "Как вы хотите задать дугу?\n";
	std::cout << "0. Через координаты\n";
	std::cout << "1. Через углы\n";
	std::cout << ">>> ";
	int mode = 1;
	//std::cin >> mode;
	while (mode != 0 && mode != 1)
	{
		std::cout << "Ошибка ввода, попробуйте еще раз\n";
		std::cout << ">>> ";
		std::cin >> mode;
	}

	float startAngle{};
	float endAngle{};

	if (mode == 0)
	{
		std::cout << "Введите координаты начальной точки: ";
		float startPointX; 
		float startPointY; 
		std::cin >> startPointX >> startPointY;

		std::cout << "Введите координаты конечной точки: ";
		float endPointX; 
		float endPointY; 
		std::cin >> endPointX >> endPointY;

		startAngle = atan((centerY - startPointY) / (startPointX - centerX));
		endAngle = atan((centerY - endPointY) / (endPointX - centerX));

		if (startPointX < centerX)
		{
			startAngle += M_PI;
		}
		if (endPointX < centerX)
		{
			endAngle += M_PI;
		}
	}
	else if (mode == 1)
	{
		std::cout << "Введите угол начальной точки (град): ";
		//std::cin >> startAngle;
		startAngle = 0;
		startAngle *= M_PI / 180;

		std::cout << "Введите угол конечной точки (град): ";
		//std::cin >> endAngle;
		endAngle = 90;
		endAngle *= M_PI / 180;
	}

	float angularLength = abs(endAngle - startAngle);

	std::cout << "Чтобы перейти к сектору, нажмите enter\n";

	CircleShape center(CENTER_RADIUS);
	center.setPosition(centerX - CENTER_RADIUS, centerY - CENTER_RADIUS);
	center.setFillColor(Color(0, 0, 0));

	VertexArray arc(LineStrip, FACES + 1);
	VertexArray sector(TriangleFan, FACES + 2);

	float angle = startAngle;
	for (unsigned short i{}; i < FACES + 1; ++i)
	{
		arc[i].color = Color(0, 0, 0);
		sector[i].color = Color(0, 0, 0);
		arc[i].position = Vector2f(centerX + radius * cos(angle), centerY - radius * sin(angle));
		angle += angularLength / FACES;
	}
	sector[FACES + 1].color = Color(0, 0, 0);

	CircleShape leftEye(15);
	leftEye.setPosition(425, 200);
	leftEye.setFillColor(Color(255, 255, 255));

	CircleShape rightEye(15);
	rightEye.setPosition(465, 200);
	rightEye.setFillColor(Color(255, 255, 255));

	CircleShape leftPupil(12.5);
	leftPupil.setPosition(425, 200);
	leftPupil.setFillColor(Color(0, 0, 0));

	CircleShape rightPupil(12.5);
	rightPupil.setPosition(465, 200);
	rightPupil.setFillColor(Color(0, 0, 0));

	CircleShape leftBlick(5);
	leftBlick.setPosition(440, 210);
	leftBlick.setFillColor(Color(255, 255, 255));

	CircleShape rightBlick(5);
	rightBlick.setPosition(480, 210);
	rightBlick.setFillColor(Color(255, 255, 255));

	CircleShape leftBrow(3);
	leftBrow.setPosition(425, 200);
	leftBrow.setFillColor(Color(0, 0, 0));
	leftBrow.scale(2, 0.75);
	leftBrow.rotate(-45);

	CircleShape rightBrow(3);
	rightBrow.setPosition(485, 190);
	rightBrow.setFillColor(Color(0, 0, 0));
	rightBrow.scale(2, 0.75);
	rightBrow.rotate(45);

	CircleShape nose(7, 3);
	nose.setPosition(452, 227);
	nose.setFillColor(Color(57, 28, 17));

	Vertex mouth[]
	{
		Vertex(Vector2f(455, 250)),
		Vertex(Vector2f(465, 250))
	};
	mouth[0].color = Color(0, 0, 0);
	mouth[1].color = Color(0, 0, 0);

	CircleShape head(60);
	head.setPosition(400, 160);
	head.setFillColor(Color(237, 174, 10));
	head.setOutlineColor(Color(82, 55, 22));
	head.setOutlineThickness(-20);

	CircleShape leftEar(60);
	leftEar.setPosition(320, 160);
	leftEar.setFillColor(Color(57, 28, 17));
	leftEar.setOutlineColor(Color(82, 55, 22));
	leftEar.setOutlineThickness(-20);

	CircleShape rightEar(60);
	rightEar.setPosition(480, 160);
	rightEar.setFillColor(Color(57, 28, 17));
	rightEar.setOutlineColor(Color(82, 55, 22));
	rightEar.setOutlineThickness(-20);

	CircleShape body(50);
	body.setPosition(410, 250);
	body.setFillColor(Color(237, 174, 10));
	body.setOutlineColor(Color(82, 55, 22));
	body.setOutlineThickness(-20);
	body.scale(1, 1.5);

	CircleShape leftArm(25);
	leftArm.setPosition(362.5, 325);
	leftArm.setFillColor(Color(82, 55, 22));
	leftArm.scale(1.5, 0.75);
	leftArm.rotate(-45);

	CircleShape rightArm(25);
	rightArm.setPosition(502.5, 270);
	rightArm.setFillColor(Color(82, 55, 22));
	rightArm.scale(1.5, 0.75);
	rightArm.rotate(45);

	CircleShape leftFoot(25);
	leftFoot.setPosition(372.5, 370);
	leftFoot.setFillColor(Color(82, 55, 22));
	leftFoot.scale(1.5, 0.75);

	CircleShape rightFoot(25);
	rightFoot.setPosition(472.5, 370);
	rightFoot.setFillColor(Color(82, 55, 22));
	rightFoot.scale(1.5, 0.75);

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), "Arc and sector");

	float rotateAngle = 0;
	float offsetX = 0;
	float directionMultiplier = 1;
	bool enterWasPressed = false;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Enter) && enterWasPressed == false)
			{
				enterWasPressed = true;
				center.setFillColor(Color(255, 0, 0));
			}
			if (event.type == Event::Closed)
				window.close();
		}

		if (enterWasPressed == true)
		{
			sector[0].position = Vector2f(offsetX + centerX, centerY);
			center.setPosition(offsetX - CENTER_RADIUS + centerX, centerY - CENTER_RADIUS);
			angle = startAngle - rotateAngle;
			for (unsigned short i = 1; i < FACES + 2; ++i)
			{
				sector[i].position = Vector2f(offsetX + centerX + radius * cos(angle), centerY - radius * sin(angle));
				angle += angularLength / FACES;
			}
		}

		window.clear(Color(255, 255, 255));
		if (enterWasPressed == false)
		{
			//window.draw(arc);
		}
		else
		{
			window.draw(sector);

			rotateAngle -= M_PI / ROTATE_SPEED;
			offsetX += directionMultiplier * MOVE_SPEED;
			if (offsetX >= WINDOW_WIDTH - centerX - radius)
			{
				directionMultiplier = -1;
			}
			else if (offsetX <= radius - centerX)
			{
				directionMultiplier = 1;
			}
		}
		window.draw(leftEar);
		window.draw(rightEar);
		window.draw(body);
		window.draw(head);
		window.draw(nose);
		window.draw(mouth, 2, Lines);
		window.draw(leftEye);
		window.draw(rightEye);
		window.draw(leftPupil);
		window.draw(rightPupil);
		window.draw(leftBlick);
		window.draw(rightBlick);
		window.draw(leftBrow);
		window.draw(rightBrow);
		window.draw(leftArm);
		window.draw(rightArm);
		window.draw(leftFoot);
		window.draw(rightFoot);
		//window.draw(center);
		window.display();
	}

	return 0;
}


//int main()
//{
//	float angle{};
//	float x, y = 0;
//	const float PI = 3.1415927;
//	sf::ContextSettings settings;
//	settings.antialiasingLevel = 8;
//
//	sf::RenderWindow window(sf::VideoMode(1280, 720), "Home", sf::Style::Default, settings);
//	//sf::Vector2f windowCenter = sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
//
//	//sf::CircleShape clock(250);
//	//clock.setPointCount(100);
//	//clock.setFillColor(sf::Color::White);
//	//clock.setOutlineThickness(5);
//	//clock.setOutlineColor(sf::Color::Black);
//	//clock.setPosition(150, 50);
//
//	//sf::CircleShape centerCircle(10);
//	//centerCircle.setPointCount(100);
//	//centerCircle.setFillColor(sf::Color::Red);
//	//centerCircle.setPosition(390, 290);
//
//	//sf::CircleShape dot[60];
//	//dot->setFillColor(sf::Color::Black);
//	//dot->setRadius(3);
//	//for (int i = 0; i < 60; i++)
//	//{
//	//	x = (250 - 10) * cos(angle);
//	//	y = (250 - 10) * sin(angle);
//
//	//	if (i % 5 == 0)
//	//		dot[i] = sf::CircleShape(3);
//	//	else
//	//		dot[i] = sf::CircleShape(1);
//	//	dot[i].setFillColor(sf::Color::Black);
//	//	dot[i].setOrigin(dot[i].getGlobalBounds().width / 2, dot[i].getGlobalBounds().height / 2);
//	//	dot[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);
//
//	//	angle = angle + ((2 * PI) / 60);
//	//}
//
//	//sf::RectangleShape hourHand(sf::Vector2f(5, 180));
//	//sf::RectangleShape minuteHand(sf::Vector2f(3, 240));
//	//sf::RectangleShape secondHand(sf::Vector2f(2, 250));
//
//	//hourHand.setFillColor(sf::Color::Black);
//	//minuteHand.setFillColor(sf::Color::Black);
//	//secondHand.setFillColor(sf::Color::Red);
//
//	//hourHand.setPosition(windowCenter);
//	//minuteHand.setPosition(windowCenter);
//	//secondHand.setPosition(windowCenter);
//
//	sf::RectangleShape wall(sf::Vector2f(400, 300));
//	wall.setFillColor(sf::Color(255, 128, 0));
//	wall.setPosition(250, 250);
//
//	sf::ConvexShape roof;
//	roof.setPointCount(3);
//	roof.setPoint(0,sf::Vector2f(175, 250));
//	roof.setPoint(1, sf::Vector2f(725, 250));
//	roof.setPoint(2, sf::Vector2f(450, 100));
//	roof.setFillColor(sf::Color(128, 64, 0));
//
//	sf::RectangleShape earth(sf::Vector2f(1280, 250));
//	earth.setFillColor(sf::Color::Green);
//	earth.setPosition(0,480 );
//
//	sf::RectangleShape windowFrame(sf::Vector2f(150, 150));
//	windowFrame.setFillColor(sf::Color(128, 64, 0));
//	windowFrame.setPosition(375, 300);
//
//	sf::RectangleShape glass(sf::Vector2f(130, 130));
//	glass.setFillColor(sf::Color(0, 255, 255));
//	glass.setPosition(385, 310);
//
//	sf::RectangleShape stickWindowaVertical(sf::Vector2f(5, 130));
//	stickWindowaVertical.setFillColor(sf::Color(128, 64, 0));
//	stickWindowaVertical.setPosition(450, 310);
//
//	sf::RectangleShape stickWindowaGorizontal(sf::Vector2f(5, 130));
//	stickWindowaGorizontal.setFillColor(sf::Color(128, 64, 0));
//	stickWindowaGorizontal.setPosition(515, 372);
//	stickWindowaGorizontal.rotate(90);
//
//	sf::RectangleShape Chimney(sf::Vector2f(50, 90));
//	Chimney.setFillColor(sf::Color(192,192,192));
//	Chimney.setPosition(530, 130);
//
//	sf::CircleShape smokeSmall(10);
//	smokeSmall.setFillColor(sf::Color(128,128,128));
//	smokeSmall.setPosition(543, 115);
//
//	sf::CircleShape smokeMedium(15);
//	smokeMedium.setFillColor(sf::Color(128, 128, 128));
//	smokeMedium.setPosition(550, 95);
//
//	sf::CircleShape smokeBig(20);
//	smokeBig.setFillColor(sf::Color(128, 128, 128));
//	smokeBig.setPosition(556, 70);
//
//	sf::CircleShape moon(115);
//	moon.setFillColor(sf::Color::White);
//	moon.setPosition(900, 60);
//	moon.setPointCount(100);
//
//	sf::CircleShape blackCicrcle(115);
//	blackCicrcle.setFillColor(sf::Color::Black);
//	blackCicrcle.setPosition(850, 60);
//	blackCicrcle.setPointCount(100);
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//
//				window.close();
//		}
//		/*std::time_t currentTime = std::time(NULL);
//
//		struct tm* ptm = localtime(&currentTime);
//
//		sf::Transform transformation[3];
//		transformation[0].rotate(180 + (float)ptm->tm_hour * 30 + (float)ptm->tm_min / 2 + (float)ptm->tm_sec / 120, sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
//		transformation[1].rotate(180 + (float)ptm->tm_min * 6 + ((float)ptm->tm_sec / 10), sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
//		transformation[2].rotate(180 + (float)ptm->tm_sec * 6, sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
//
//		window.clear(sf::Color::White);
//
//		window.draw(clock);
//
//		for (int i{}; i < 60; ++i)
//		{
//			window.draw(dot[i]);
//
//		}
//
//		window.draw(hourHand, transformation[0]);
//		window.draw(minuteHand, transformation[1]);
//		window.draw(secondHand, transformation[2]);*/
//
//		//window.draw(centerCircle);
//		window.clear(sf::Color::Black);
//		window.draw(earth);
//		window.draw(wall);
//		window.draw(roof);
//		window.draw(windowFrame);
//		window.draw(glass);
//		window.draw(stickWindowaVertical);
//		window.draw(stickWindowaGorizontal);
//		window.draw(Chimney);
//		window.draw(smokeSmall);
//		window.draw(smokeMedium);
//		window.draw(smokeBig);
//		window.draw(moon);
//		window.draw(blackCicrcle);
//		window.display();
//	}
//	return 0;
//}