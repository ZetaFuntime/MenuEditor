#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include <vector>
#include "Matrix3.h"
#include "Vector3.h"
#include "planet.h"
using std::vector;

#include <memory>

class SolarApp : public aie::Application {
public:

	SolarApp();
	virtual ~SolarApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	float m_scale;

	// new stuff
	vector<Planet> planets;

	std::unique_ptr<aie::Renderer2D> m_2dRenderer;

	aie::Font*			m_font;

	std::shared_ptr<aie::Texture> m_starsTex;
	std::shared_ptr<aie::Texture> m_sunTex;
	std::shared_ptr<aie::Texture> m_mercuryTex;
	std::shared_ptr<aie::Texture> m_venusTex;
	std::shared_ptr<aie::Texture> m_earthTex;
	std::shared_ptr<aie::Texture> m_marsTex;
	std::shared_ptr<aie::Texture> m_jupiterTex;
	std::shared_ptr<aie::Texture> m_saturnTex;
	std::shared_ptr<aie::Texture> m_uranusTex;
	std::shared_ptr<aie::Texture> m_neptuneTex;
	std::shared_ptr<aie::Texture> m_moonTex;

	//aie::Audio*			m_audio;

	float m_cameraX, m_cameraY;
	float m_timer;
};