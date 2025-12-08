#include "Window.h"
#include "Core.h"
#include "Math.h"
#include "PSOManager.h"
#include "GamesEngineeringBase.h"
#include "ShaderManager.h"
#include "Mesh.h"
#include "Cube.h"
#include "Sphere.h"
#include "Plane.h"
#include "GEMObject.h"
#include "GEMAnimatedObject.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define Z_FAR 1000.0f
#define Z_NEAR 0.01f

// Create Pipeline Manager to access many strcuts

class Camera {
    public:
    Vec3 from;
    Vec3 to;
    Vec3 up;

    Camera() : from(11.0f, 5.0f, 11.0f), to(0, 1, 0), up(0, 1, 0) {}
    Camera(Vec3 from, Vec3 to, Vec3 up) : from(from), to(to), up(up) {}
    
    void OnPressW() {
        //MessageBoxA(NULL, "W Pressed", "Info", MB_OK | MB_ICONINFORMATION);
        this->from.z = this->from.z - 1.0f;
    }
    void OnPressS() {
        this->from.z = this->from.z + 1.0f;
    }

    void OnPressA() {
        this->from.x = this->from.x - 1.0f;
    }

    void OnPressD() {
        this->from.x = this->from.x + 1.0f;
    }

    void registerKeysCallbacks(Window *win) {
        win->registerKeyCallback('W', [&]() { this->OnPressW(); });
        win->registerKeyCallback('S', [&]() { this->OnPressS(); });
        win->registerKeyCallback('A', [&]() { this->OnPressA(); });
        win->registerKeyCallback('D', [&]() { this->OnPressD(); });
    }
};

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    Window win;
    win.init(WINDOW_HEIGHT, WINDOW_WIDTH, 0, 0, "My Window");

    Core core;
    core.init(win.hwnd, win.windowWidth, win.windowHeight);
    
    ShaderManager* shaderManager = new ShaderManager(&core);
    Camera camera;
    camera.registerKeysCallbacks(&win);
    
    Matrix viewMatrix;
    viewMatrix.setLookatMatrix(camera.from, camera.to, camera.up);

    Matrix projectionMatrix;
    float FOV = 60.0f;
    projectionMatrix.setProjectionMatrix(Z_FAR, Z_NEAR, FOV, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    Matrix WorldMatrix;
    WorldMatrix.setIdentity();

    Cube cube(shaderManager);
    Sphere sphere(shaderManager);
    GEMObject acacia(shaderManager, &core, "assets/models/acacia_003.gem");
    GEMAnimatedObject rex(shaderManager, "assets/models/TRex.gem");

    VertexShaderCBStaticModel vsCBStaticModel;
    VertexShaderCBAnimatedModel vsCBAnimatedModel;

    vsCBStaticModel.W = WorldMatrix;
    vsCBStaticModel.VP = (projectionMatrix.mul(viewMatrix));

    vsCBAnimatedModel.W = WorldMatrix;
    vsCBAnimatedModel.VP = (projectionMatrix.mul(viewMatrix));

    AnimationInstance animatedInstance;
    rex.init(&core, &vsCBAnimatedModel);

    animatedInstance.init(&rex.animatedModel->animation, 0);
    memcpy(vsCBAnimatedModel.bones, animatedInstance.matrices, sizeof(vsCBAnimatedModel.bones));
    
    //cube.init(&core, &vsCBStaticModel);
    //acacia.init(&core, &vsCBStaticModel);
    //sphere.init(&core, &vsCBStaticModel);

    GamesEngineeringBase::Timer tim = GamesEngineeringBase::Timer();
    float time = 0.0f;

    while (true) {
        core.beginFrame();
        win.processMessages();
        if (win.keys[VK_ESCAPE] == 1) {
            break;
        }

        float dt = tim.dt();
        time += dt;
        time = fmodf(time, 2 * 3.1415f); // Avoid precision issues

        viewMatrix.setLookatMatrix(camera.from, camera.to, camera.up);

        //vsCBStaticModel.VP = (projectionMatrix.mul(viewMatrix));
        vsCBAnimatedModel.VP = (projectionMatrix.mul(viewMatrix));
        // acacia.draw(&core, &vsCBStaticModel);

        // cube.draw(&core, &vsCBStaticModel);

        //vsCBStaticModel.W.setScaling(0.01f, 0.01f, 0.01f);
        vsCBAnimatedModel.W.setScaling(0.01f, 0.01f, 0.01f);
        // cube.draw(&core, &vsCBStaticModel);

        animatedInstance.update("roar", dt);
        //animatedInstance.animationFinished();
		if (animatedInstance.animationFinished() == true)
		{
			animatedInstance.resetAnimationTime();
		}
        memcpy(vsCBAnimatedModel.bones, animatedInstance.matrices, sizeof(vsCBAnimatedModel.bones));
        rex.draw(&core, &vsCBAnimatedModel); 

        // vsCBStaticModel.W.setTranslation(0, 0, 0);


        core.finishFrame();
    }

    core.flushGraphicsQueue();
    return 0;
}
