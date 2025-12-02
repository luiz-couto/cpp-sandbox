#include "Window.h"
#include "Core.h"
#include "Math.h"
#include "PSOManager.h"
#include "GamesEngineeringBase.h"
#include "ShaderManager.h"
#include "Mesh.h"
#include "Cube.h"
#include "Sphere.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

// Constant buffers associates with the shader - use code reflection (to get the size of the buffer from the shader itself?)
// Pipeline Manager to access many strcuts

class Plane {
public:
    Mesh mesh;
    ShaderManager* shaderManager;
    PSOManager psos;
    VertexLayoutCache vertexLayoutCache;

    Plane(ShaderManager* sm) : shaderManager(sm) {}

    void init(Core* core, VertexShaderCBStaticModel *vsCB) {
        // Build geometry
        std::vector<STATIC_VERTEX> vertices;
        vertices.push_back(addVertex(Vec3(-15, 0, -15), Vec3(0, 1, 0), 0, 0));
        vertices.push_back(addVertex(Vec3( 15, 0, -15), Vec3(0, 1, 0), 1, 0));
        vertices.push_back(addVertex(Vec3(-15, 0,  15), Vec3(0, 1, 0), 0, 1));
        vertices.push_back(addVertex(Vec3( 15, 0,  15), Vec3(0, 1, 0), 1, 1));

        std::vector<unsigned int> indices = { 2, 1, 0,  1, 2, 3 };
        mesh.initFromVec(core, vertices, indices);

        Shader* vertexShaderBlob = shaderManager->getVertexShader("VertexShader.hlsl", vsCB);
        Shader* pixelShaderBlob = shaderManager->getShader("PixelShader.hlsl", PIXEL_SHADER);
        psos.createPSO(core, "Plane", vertexShaderBlob->shaderBlob, pixelShaderBlob->shaderBlob, vertexLayoutCache.getStaticLayout());
    }

    void draw(Core* core, VertexShaderCBStaticModel *vsCB) {
        core->beginRenderPass();

        // 1. Bind PSO FIRST
        psos.bind(core, "Plane");

        // 2. Update constant buffer values
        shaderManager->updateConstantVS("VertexShader.hlsl", "W",  &vsCB->W);
        shaderManager->updateConstantVS("VertexShader.hlsl", "VP", &vsCB->VP);

        // 3. Apply vertex shader (binds CBV)
        shaderManager->getVertexShader("VertexShader.hlsl", vsCB)->apply(core);

        // 4. Draw
        mesh.draw(core);
    }

};

class Camera {
    public:
    Vec3 from;
    Vec3 to;
    Vec3 up;

    Camera() : from(25.0f, 55.0f, 80.0f), to(0, 1, 0), up(0, 1, 0) {}
    Camera(Vec3 from, Vec3 to, Vec3 up) : from(from), to(to), up(up) {}
};

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    Window win;
    win.init(WINDOW_HEIGHT, WINDOW_WIDTH, 0, 0, "My Window");

    Core core;
    core.init(win.hwnd, win.windowWidth, win.windowHeight);
    
    ShaderManager* shaderManager = new ShaderManager(&core);
    Camera camera;
    
    Matrix viewMatrix;
    viewMatrix.setLookatMatrix(camera.from, camera.to, camera.up);

    Matrix projectionMatrix;
    float zFar = 1000.0f;
    float zNear = 0.01f;
    float FOV = 60.0f;
    projectionMatrix.setProjectionMatrix(zFar, zNear, FOV, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    Matrix WorldMatrix;
    WorldMatrix.setIdentity();

    Cube cube(shaderManager);
    Sphere sphere(shaderManager);
    VertexShaderCBStaticModel vsCBStaticModel;

    vsCBStaticModel.W = WorldMatrix;
    vsCBStaticModel.VP = (projectionMatrix.mul(viewMatrix));

    cube.init(&core, &vsCBStaticModel);
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

        Vec3 from = Vec3(11 * cos(time), 5, 11 * sinf(time));
        camera.from = from;
        viewMatrix.setLookatMatrix(camera.from, camera.to, camera.up);

        vsCBStaticModel.VP = (projectionMatrix.mul(viewMatrix));
        cube.draw(&core, &vsCBStaticModel);

        vsCBStaticModel.W.setTranslation(5, 0, 0);
        cube.draw(&core, &vsCBStaticModel);

        vsCBStaticModel.W.setTranslation(0, 0, 0);
        core.finishFrame();
    }

    core.flushGraphicsQueue();
    return 0;
}
