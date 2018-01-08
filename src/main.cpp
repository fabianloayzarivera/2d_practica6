#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION


#include <glfw3.h>
#include <stb_image.h>
//#include <font.h>
#include <Vec2.h>
#include <list>
//#include <random>
#include <sprite.h>
using namespace std;

ltex_t *createTexture(const char *filename, int *width, int *height);
void beeUpdatePosAngle(Sprite &beeSprite, float &angle, float &pointsX, float &pointsY, double &xposBee, double &yposBee, Vec2 mousePos, Vec2 &beePos, float deltaTime);

int main() {

	// Inicializamos GLFW
	if (!glfwInit()) {
		cout << "Error: No se ha podido inicializar GLFW" << endl;
		return -1;
	}
	atexit(glfwTerminate);
	// Creamos la ventana
	glfwWindowHint(GLFW_RESIZABLE, false);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Programacion 2D", nullptr, nullptr);
	if (!window) {
		cout << "Error: No se ha podido crear la ventana" << endl;
		return -1;
	}
	// Activamos contexto de OpenGL
	glfwMakeContextCurrent(window);
	// Inicializamos LiteGFX
	lgfx_setup2d(800, 600);

	int widthBee		= 640;
	int heightBee		= 92;
	int widthClouds = 256;
	int heightClouds = 256;
	Sprite beeSprite	= Sprite(createTexture("./data/bee_anim.png", &widthBee, &heightBee), 8, 1);
	
	beeSprite.setPosition(Vec2(0, 0));
	beeSprite.setBlend(BLEND_ALPHA);
	beeSprite.setFps(8);
	beeSprite.setPivot(Vec2(0.5f, 0.5f));

	Sprite cloudsSprite = Sprite(createTexture("./data/clouds.png", &widthBee, &heightBee), 1, 1);
	cloudsSprite.setPosition(Vec2(0, 0));
	cloudsSprite.setBlend(BLEND_ALPHA);
	cloudsSprite.setFps(1);
	cloudsSprite.setPivot(Vec2(0.5f, 0.5f));
	int beeFrame;
	float frame = 0;
	double lastTime = glfwGetTime();
	double xposMouse = 0;
	double yposMouse = 0;
	double xposBee = 0;
	double yposBee = 0;
	float pointsX = 0;
	float pointsY = 0;
	float angle=0;
	
	Vec2 beePos;
	
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// Actualizamos delta
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// Actualizamos tamaño de ventana
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		lgfx_setviewport(0, 0, screenWidth, screenHeight);
		lgfx_clearcolorbuffer(0.7f, 0.6f, 0.7f);

		glfwGetCursorPos(window, &xposMouse, &yposMouse);
		Vec2 mousePos = Vec2(xposMouse, yposMouse);		
		
		beeUpdatePosAngle(beeSprite, angle, pointsX, pointsY, xposBee, yposBee, mousePos, beePos, deltaTime);

		cloudsSprite.update(deltaTime);
		cloudsSprite.draw();

		beeSprite.update(deltaTime);
		beeSprite.draw();
		
		
		
		
		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();


	}

	return 0;
}

ltex_t* createTexture(const char *filename, int *width, int *height) {

	unsigned char* buffer = stbi_load(filename, width, height, nullptr, 4);

	if (buffer != NULL) {
	}
	else {
		cout << "buffer empty";
	}

	ltex_t* tex = ltex_alloc(*width, *height, 0);

	ltex_setpixels(tex, buffer);

	stbi_image_free(buffer);

	return tex;
	//ltex_free(ltex_t* tex);

}

void beeUpdatePosAngle(Sprite &beeSprite, float &angle, float &pointsX, float &pointsY, double &xposBee, double &yposBee, Vec2 mousePos, Vec2 &beePos, float deltaTime) {
	Vec2 dist;
	Vec2 direction;
	dist = mousePos - beePos;
	direction = dist.norm();

	if (dist.lenght() > 2) {
		pointsX = 128.0f * deltaTime * direction.x;
		pointsY = 128.0f * deltaTime * direction.y;
		if (xposBee < mousePos.x && angle > -15) {
			angle -= (32 * deltaTime);
		}
		else if (angle < 15) {
			angle += (32 * deltaTime);
		}
	}
	else {
		pointsX = 0;
		pointsY = 0;
		if (angle < 0) {
			angle += (32 * deltaTime);
		}
		else if (angle > 0) {
			angle -= (32 * deltaTime);
		}
	}
	xposBee += pointsX;
	yposBee += pointsY;

	beePos = Vec2(xposBee, yposBee);
	beeSprite.setPosition(beePos);
	beeSprite.setAngle(angle);
}