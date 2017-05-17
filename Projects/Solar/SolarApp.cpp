#include "SolarApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "ErrorManager.h"
#include "ResourceManager.h"


SolarApp::SolarApp() {

}

SolarApp::~SolarApp() {

}

bool SolarApp::startup() {
	m_cameraX = m_cameraY = 0;
	m_scale = 1;

	m_2dRenderer = std::unique_ptr<aie::Renderer2D>(new aie::Renderer2D);

	// Create a font using the resource manager for safe loading
	m_sunTex = ResourceManager::loadSharedResource<aie::Texture>("./solar/textures/sun.png");
	m_mercuryTex = ResourceManager::loadSharedResource<aie::Texture>("./solar/textures/mercury.png");
	m_venusTex = ResourceManager::loadSharedResource<aie::Texture>("./solar/textures/venera.png");
	m_earthTex = ResourceManager::loadSharedResource<aie::Texture>("./solar/textures/earth.png");
	m_marsTex = ResourceManager::loadSharedResource<aie::Texture>("./solar/textures/mars.png");
	m_jupiterTex = ResourceManager::loadSharedResource<aie::Texture>("./solar/textures/jupiter.png");
	m_saturnTex = ResourceManager::loadSharedResource<aie::Texture>("./solar/textures/saturn.png");
	m_uranusTex = ResourceManager::loadSharedResource<aie::Texture>("./solar/textures/uran.png");
	m_neptuneTex = ResourceManager::loadSharedResource<aie::Texture>("./solar/textures/neptun.png");
	m_starsTex = ResourceManager::loadSharedResource<aie::Texture>("./solar/textures/starground.png");
	m_moonTex = ResourceManager::loadSharedResource<aie::Texture>("./solar/textures/moon.png");

	// MUST BE LAST .. If we do this we have to handle memory manually
	m_font = new aie::Font("./solar/font/consolas.ttf", 32);

	//				Planet Distance	Distance to		Scale distance	Actual			Orbit times
	//				from Sun (AU)	planet			from Sun		diameter
	//								(kilometers)	(centimeters)	(kilometers)
	//	Sun(a star)		0										1391980
	//	Mercury			0.39		 58000000		3.9			4880				88
	//	Venus			0.72		108000000		7.9			12100				224.7
	//	Earth			1.00		150000000		10			12800				365.2
	//	Mars			1.52		228000000		15.2		6800				687.0
	//	Jupiter			5.20		778000000		52.0		142000				4332
	//	Saturn			9.54 1,		430000000		95.4		120000				10760
	//	Uranus			19.2 2,		870000000		192			51800				30700
	//	Neptune			30.1 4,		500000000		301			49500				60200
	//	Pluto			39.4 5,		900000000		394			2300				90600

	// and build the planets
	float orbitSlowdown = 5;
	Vector3 center = { (float)getWindowWidth() / 2, (float)getWindowHeight() / 2, 1 };
	planets.push_back(Planet(0.f,					0.f,		500.f,		695500, m_sunTex.get(),		center)); // sun
	planets.push_back(Planet((float)58000000,		88.f,		58.6f,		2440,	m_mercuryTex.get(),	center)); // mercury
	planets.push_back(Planet((float)108000000,		224.7f,		243.f,		6052,	m_venusTex.get(),	center)); // venus
	planets.push_back(Planet((float)150000000,		365.2f,		1.f,		6371,	m_earthTex.get(),	center)); // real earth
	planets.push_back(Planet((float)228000000,		687.0f,		1.03f,		3389,	m_marsTex.get(),	center)); // mars
	planets.push_back(Planet((float)778000000,		4332.f,		0.4139f,	69911,	m_jupiterTex.get(),	center)); // jupiter
	planets.push_back(Planet((float)430000000,		10760.f,	9999.f,		1137,	m_saturnTex.get(),	center)); // saturn
	planets.push_back(Planet((float)870000000,		60200.f,	19.2f,		1137,	m_uranusTex.get(),	center)); // Uranus
	planets.push_back(Planet((float)500000000,		60200.f,	30.1f,		1137,	m_neptuneTex.get(), center)); // neptune

	// add any moons
	// planets[3].addMoon(7000000, 27.3, 27.3, 1738, m_moonTex);

	return true;
}

void SolarApp::shutdown() {
	// now only delete fonts and sounds as smart pointers are in effect
	delete m_font;
}

void SolarApp::update(float deltaTime) {
	static double lastMouseMove = 0;
	// input example
	aie::Input* input = aie::Input::getInstance();

	// new planets displayed
	for (unsigned int i = 0; i < planets.size(); i++) {
		planets[i].update(deltaTime);
	}

	// mouse wheel
	double movement = input->getMouseScroll();
	double difference = movement;
	m_scale = m_scale - (float) (lastMouseMove - movement)/50.f;
	if (m_scale < .2f) m_scale = 0.2f;
	lastMouseMove = movement;

	if (input->isKeyDown(aie::INPUT_KEY_UP))
		m_cameraY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		m_cameraY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		m_cameraX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		m_cameraX += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_C)) {
		m_cameraX = m_cameraY = 0;
		m_scale = 1.0f;
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}


void SolarApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw a cross hairs
	m_2dRenderer->setRenderColour(1.f, 1.f, 0.f, 0.2f);
	m_2dRenderer->drawLine(0, (float)getWindowHeight() / 2, (float)getWindowWidth(), (float)getWindowHeight() / 2, 2, 1);
	m_2dRenderer->drawLine((float)getWindowWidth() / 2, 0, (float)getWindowWidth() / 2, (float)getWindowHeight(), 2, 1);

	// new planets displayed
	for (unsigned int i = 0; i < planets.size(); i++) {
		planets[i].render(m_2dRenderer.get(), m_scale);
	}

	// output some text, uses the last used colour
	m_2dRenderer->setRenderColour(1.f, 1.f, 1.f, 0.2f);
#if 0
	char tempStr[256];
	sprintf_s(tempStr, "Press ESC to quit  %f scale = %f", (float)lastMouseMovePrint, m_scale);
	m_2dRenderer->drawText(m_font, tempStr, 0, 0);
#else
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
#endif

	// done drawing sprites
	m_2dRenderer->end();
}

