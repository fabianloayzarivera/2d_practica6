#include <world.h>

World::World() {
	sprite = nullptr;
	clearRed = 0.7f;
	clearGreen = 0.6f;
	clearBlue = 0.7f;
	back0 = nullptr;
	back1 = nullptr;
	back2 = nullptr;
	back3 = nullptr;
	backgroundBlend = BLEND_ALPHA;
	scrollRatio0 = 0;
	scrollRatio1 = 0;
	scrollRatio2 = 0;
	scrollRatio3 = 0;
	scrollSpeed0 = Vec2(0, 0);
	scrollSpeed1 = Vec2(0, 0);
	scrollSpeed2 = Vec2(0, 0);
	scrollSpeed3 = Vec2(0, 0);
	cameraPosition = Vec2(0,0);
	screenSize = Vec2(800.0f, 600.0f);
}

void World::updateCameraPosition(const Vec2& pos, float deltaTime) {
	/*if ((pos.x >=  cameraPosition.x + (screenSize.x / 2.0f)) && (cameraPosition.x + screenSize.x < back0->width)){
		cameraPosition.x += 128.0f * deltaTime;
	}
	else if ((pos.x < cameraPosition.x + (screenSize.x / 2.0f)) && (cameraPosition.x > 0)) {
		cameraPosition.x -= 128.0f * deltaTime;
	}

	if ((pos.y >= cameraPosition.y + (screenSize.y / 2.0f)) && (cameraPosition.y + screenSize.y < back0->height)){
		cameraPosition.y += 128.0f * deltaTime;
	}
	else if ((pos.y < cameraPosition.y + (screenSize.y / 2.0f)) && (cameraPosition.y > 0)) {
		cameraPosition.y -= 128.0f * deltaTime;
	}*/
	
	cameraPosition.x = pos.x - (screenSize.x / 2.0f);
	cameraPosition.y = pos.y - (screenSize.y / 2.0f);
	if (cameraPosition.x < 0)
		cameraPosition.x = 0;
	if (cameraPosition.y < 0)
		cameraPosition.y = 0;

	if (cameraPosition.x > back0->width - screenSize.x)
		cameraPosition.x = back0->width - screenSize.x;
	if (cameraPosition.y > back0->height - screenSize.y)
		cameraPosition.y = back0->height - screenSize.y;

}

void World::update(float deltaTime) {
	sprite->update(deltaTime);

}

void World::draw(const Vec2& screenSize) {
	lgfx_setblend(backgroundBlend);
	//background 3	
	float u1Back3 = (static_cast<float>(back0->width) / static_cast<float>(back3->width));
	float v1Back3 = (static_cast<float>(screenSize.y) / static_cast<float>(back3->height));
	ltex_drawrotsized(back3, 0, 0, 0, 0, 0, back3->width*u1Back3, back3->height*v1Back3, 0, 0, u1Back3, v1Back3);
	//background 2
	float u1Back2 = (static_cast<float>(back0->width) / static_cast<float>(back2->width));
	//float v1Back2 = (static_cast<float>(screenSize.y) / static_cast<float>(back2->height));
	ltex_drawrotsized(back2, 0, 0, 0, 0, 0, back2->width * u1Back2, back2->height, 0, 0, u1Back2, 1);
	//background 1
	float u1Back1 = (static_cast<float>(back0->width) / static_cast<float>(back1->width));
	ltex_drawrotsized(back1, 0, 0, 0, 0, 0, back1->width * u1Back1, back1->height, 0, 0, u1Back1, 1);
	//background 0
	ltex_drawrotsized(back0, 0, 0, 0, 0, 0, back0->width, back0->height, 0, 0, 1, 1);
	//Sprite
	sprite->draw();
}

const ltex_t* World::getBackground(size_t layer) const {
	switch (layer)
	{
	case 0:
		return back0;
		break;
	case 1:
		return back1;
		break;
	case 2:
		return back2;
		break;
	case 3:
		return back3;
		break;
	default:
		break;
	}
}

void World::setBackground(size_t layer, const ltex_t* tex) {
	switch (layer)
	{
	case 0:
		back0 = tex;
		break;
	case 1:
		back1 = tex;
		break;
	case 2:
		back2 = tex;
		break;
	case 3:
		back3 = tex;
		break;
	default:
		break;
	}
}

float World::getScrollRatio (size_t layer) const{
	switch (layer)
	{
	case 0:
		return scrollRatio0;
		break;
	case 1:
		return scrollRatio1;
		break;
	case 2:
		return scrollRatio2;
		break;
	case 3:
		return scrollRatio3;
		break;
	default:
		break;
	}
}

void World::setScrollRatio(size_t layer, float ratio) {
	switch (layer)
	{
	case 0:
		scrollRatio0 = ratio;
		break;
	case 1:
		scrollRatio1 = ratio;
		break;
	case 2:
		scrollRatio2 = ratio;
		break;
	case 3:
		scrollRatio3 = ratio;
		break;
	default:
		break;
	}
}

const Vec2& World::getScrollSpeed(size_t layer) const {
	switch (layer)
	{
	case 0:
		return scrollSpeed0;
		break;
	case 1:
		return scrollSpeed1;
		break;
	case 2:
		return scrollSpeed2;
		break;
	case 3:
		return scrollSpeed3;
		break;
	default:
		break;
	}
}

void World::setScrollSpeed(size_t layer, const Vec2& speed) {
	switch (layer)
	{
	case 0:
		scrollSpeed0 = speed;
		break;
	case 1:
		scrollSpeed1 = speed;
		break;
	case 2:
		scrollSpeed2 = speed;
		break;
	case 3:
		scrollSpeed3 = speed;
		break;
	default:
		break;
	}
}
