#include <world.h>

World::World() {
	sprite = nullptr;
	clearRed = 0.8f;
	clearGreen = 0.7f;
	clearBlue = 0.8f;
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
	back3FrameX = 0;
	back3FrameY = 0;
}

void World::updateCameraPosition(const Vec2& pos, float deltaTime) {
		
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
	back3FrameX += 16 * deltaTime;
	back3FrameY += 8 * deltaTime;
}

void World::draw(const Vec2& screenSize) {
	lgfx_setblend(backgroundBlend);

	//background 3	
	float u0Back3 = ((cameraPosition.x * scrollRatio3)+ back3FrameX) / back3->width;
	float v0Back3 = ((cameraPosition.y * scrollRatio3)+ back3FrameY)/ back3->height;
	float u1Back3 = (screenSize.x / back3->width) + u0Back3;
	float v1Back3 = (screenSize.y / back3->height) + v0Back3;


	ltex_drawrotsized(back3, cameraPosition.x, cameraPosition.y, 0, 0, 0, screenSize.x + u0Back3, screenSize.y + v0Back3, u0Back3, v0Back3 , u1Back3, v1Back3);
	//background 2
	
	float u0Back2 = (cameraPosition.x / back2->width) * scrollRatio2;
	float v0Back2 = (cameraPosition.y / back2->height) * scrollRatio2;
	float u1Back2 = (screenSize.x / back2->width) + u0Back2;
	float v1Back2 = (screenSize.y / back2->height) + v0Back2;
	

	ltex_drawrotsized(back2, cameraPosition.x, cameraPosition.y, 0, 0, 0, screenSize.x + u0Back2, screenSize.y + v0Back2, u0Back2, v0Back2, u1Back2, v1Back2);

	//background 1
	float u0Back1 = (cameraPosition.x / back1->width) * scrollRatio1;
	float v0Back1 = (cameraPosition.y / back1->height) * scrollRatio1;
	float u1Back1 = (screenSize.x / back1->width) + u0Back1;
	float v1Back1 = (screenSize.y / back1->height) + v0Back1;

	ltex_drawrotsized(back1, cameraPosition.x, cameraPosition.y, 0, 0, 0, screenSize.x + u0Back1, screenSize.y + v0Back1, u0Back1, v0Back1, u1Back1, v1Back1);

	////background 0
	float u0Back0 = (cameraPosition.x / back0->width) * scrollRatio0;
	float v0Back0 = 0;
	float u1Back0 = (screenSize.x / back0->width) + u0Back0;
	float v1Back0 = 1;

	ltex_drawrotsized(back0, cameraPosition.x, 0, 0, 0, 0, screenSize.x, back0->height, u0Back0, v0Back0, u1Back0, 1);


	////Sprite
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

void World::setBackground(size_t layer, ltex_t* tex) {
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

World::~World() {
	ltex_free(back0);
	ltex_free(back1);
	ltex_free(back3);

}