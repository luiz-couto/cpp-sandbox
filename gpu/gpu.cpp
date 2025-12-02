#include "Window.h"
#include "Core.h"
#include "Math.h"
#include "PSOManager.h"
#include "GamesEngineeringBase.h"
#include "ShaderManager.h"
#include "Mesh.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 1024

// Constant buffers associates with the shader - use code reflection (to get the size of the buffer from the shader itself?)
// Pipeline Manager to access many strcuts

struct PRIM_VERTEX {
    Vec3 position;
    Colour colour;
};

struct VertexShaderCBStaticModel {
    Matrix W;
    Matrix VP;
};

STATIC_VERTEX addVertex(Vec3 p, Vec3 n, float tu, float tv) {
    STATIC_VERTEX v;
    v.pos = p;
    v.normal = n;
    v.tangent = Vec3(0, 0, 0); // For now
    v.tu = tu;
    v.tv = tv;
    return v;
}

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
        MessageBoxA(NULL, pixelShaderBlob->shaderBlob ? "PS has blob" : "PS is NULL", "Check", 0);
        MessageBoxA(NULL, ("PS blob size = " + std::to_string(pixelShaderBlob->shaderBlob->GetBufferSize())).c_str(), 0, MB_OK);
        psos.createPSO(core, "Plane", vertexShaderBlob->shaderBlob, pixelShaderBlob->shaderBlob, vertexLayoutCache.getStaticLayout());
    }

    void draw(Core* core, VertexShaderCBStaticModel *vsCB) {   
        core->beginRenderPass();

        // Update VS/PS constant buffers
        //shaderManager->updateConstantVS("VertexShader.hlsl", "W", &vsCB->W);
        //shaderManager->updateConstantVS("VertexShader.hlsl", "VP", &vsCB->VP);

        shaderManager->getVertexShader("VertexShader.hlsl", vsCB)->apply(core);
        //Shader* pixelShader = shaderManager->getShader("PixelShader.hlsl", PIXEL_SHADER);
        //core->getCommandList()->SetGraphicsRootConstantBufferView(0, vertexShader->constantBufferReflection->getGPUAddress());


        // Apply PSO (bind VS+PS)
        psos.bind(core, "Plane");

        // Draw geometry
        mesh.draw(core);
    }

    // void draw(Core* core, VertexShaderCBStaticModel *vsCB) {
    //     core->beginRenderPass();

    //     // 1. Bind PSO FIRST
    //     psos.bind(core, "Plane");

    //     // 2. Update constant buffer values
    //     shaderManager->updateConstantVS("VertexShader.hlsl", "W",  &vsCB->W);
    //     shaderManager->updateConstantVS("VertexShader.hlsl", "VP", &vsCB->VP);

    //     // 3. Apply vertex shader (binds CBV)
    //     shaderManager->getVertexShader("VertexShader.hlsl", vsCB)->apply(core);

    //     // 4. Draw
    //     mesh.draw(core);
    // }

};

class Camera {
    public:
    Vec3 from;
    Vec3 to;
    Vec3 up;

    Camera() : from(0, 5.0f, 11.0f), to(0, 1, 0), up(0, 1, 0) {}
    Camera(Vec3 from, Vec3 to, Vec3 up) : from(from), to(to), up(up) {}
};

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    Window win;
    win.init(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, "My Window");

    Core core;
    core.init(win.hwnd, win.windowWidth, win.windowHeight);
    
    ShaderManager* shaderManager = new ShaderManager(&core);
    Camera camera;
    
    Matrix viewMatrix;
    viewMatrix.setLookatMatrix(camera.from, camera.to, camera.up);

    // print LookAt matrix
    // MessageBoxA(NULL, 
    //     ("View Matrix:\n" +
    //     std::to_string(viewMatrix.m[0]) + " " + std::to_string(viewMatrix.m[1]) + " " + std::to_string(viewMatrix.m[2]) + " " + std::to_string(viewMatrix.m[3]) + "\n" +
    //     std::to_string(viewMatrix.m[4]) + " " + std::to_string(viewMatrix.m[5]) + " " + std::to_string(viewMatrix.m[6]) + " " + std::to_string(viewMatrix.m[7]) + "\n" +
    //     std::to_string(viewMatrix.m[8]) + " " + std::to_string(viewMatrix.m[9]) + " " + std::to_string(viewMatrix.m[10]) + " " + std::to_string(viewMatrix.m[11]) + "\n" +
    //     std::to_string(viewMatrix.m[12]) + " " + std::to_string(viewMatrix.m[13]) + " " + std::to_string(viewMatrix.m[14]) + " " + std::to_string(viewMatrix.m[15]) + "\n"
    //     ).c_str(),
    //     "Info", MB_OK | MB_ICONINFORMATION);

    Matrix projectionMatrix;
    float zFar = 1000.0f;
    float zNear = 0.01f;
    float FOV = 45.0f;
    projectionMatrix.setProjectionMatrix(zFar, zNear, FOV, WINDOW_WIDTH, WINDOW_HEIGHT);

    // print Projection matrix
    // MessageBoxA(NULL, 
    //     ("Projection Matrix:\n" +
    //     std::to_string(projectionMatrix.m[0]) + " " + std::to_string(projectionMatrix.m[1]) + " " + std::to_string(projectionMatrix.m[2]) + " " + std::to_string(projectionMatrix.m[3]) + "\n" +
    //     std::to_string(projectionMatrix.m[4]) + " " + std::to_string(projectionMatrix.m[5]) + " " + std::to_string(projectionMatrix.m[6]) + " " + std::to_string(projectionMatrix.m[7]) + "\n" +
    //     std::to_string(projectionMatrix.m[8]) + " " + std::to_string(projectionMatrix.m[9]) + " " + std::to_string(projectionMatrix.m[10]) + " " + std::to_string(projectionMatrix.m[11]) + "\n" +
    //     std::to_string(projectionMatrix.m[12]) + " " + std::to_string(projectionMatrix.m[13]) + " " + std::to_string(projectionMatrix.m[14]) + " " + std::to_string(projectionMatrix.m[15]) + "\n"
    //     ).c_str(),
    //     "Info", MB_OK | MB_ICONINFORMATION);
    
    Matrix WorldMatrix;
    WorldMatrix.setIdentity();

    Plane plane(shaderManager);
    VertexShaderCBStaticModel vsCBStaticModel;

    vsCBStaticModel.W = WorldMatrix;

    // print World matrix
    // MessageBoxA(NULL, 
    //     ("World Matrix:\n" +
    //     std::to_string(vsCBStaticModel.W.m[0]) + " " + std::to_string(vsCBStaticModel.W.m[1]) + " " + std::to_string(vsCBStaticModel.W.m[2]) + " " + std::to_string(vsCBStaticModel.W.m[3]) + "\n" +
    //     std::to_string(vsCBStaticModel.W.m[4]) + " " + std::to_string(vsCBStaticModel.W.m[5]) + " " + std::to_string(vsCBStaticModel.W.m[6]) + " " + std::to_string(vsCBStaticModel.W.m[7]) + "\n" +
    //     std::to_string(vsCBStaticModel.W.m[8]) + " " + std::to_string(vsCBStaticModel.W.m[9]) + " " + std::to_string(vsCBStaticModel.W.m[10]) + " " + std::to_string(vsCBStaticModel.W.m[11]) + "\n" +
    //     std::to_string(vsCBStaticModel.W.m[12]) + " " + std::to_string(vsCBStaticModel.W.m[13]) + " " + std::to_string(vsCBStaticModel.W.m[14]) + " " + std::to_string(vsCBStaticModel.W.m[15]) + "\n"
    //     ).c_str(),
    //     "Info", MB_OK | MB_ICONINFORMATION);

    vsCBStaticModel.VP = (viewMatrix.mul(projectionMatrix));

    // print VP matrix
    // MessageBoxA(NULL,
    //     ("VP Matrix:\n" +
    //     std::to_string(vsCBStaticModel.VP.m[0]) + " " + std::to_string(vsCBStaticModel.VP.m[1]) + " " + std::to_string(vsCBStaticModel.VP.m[2]) + " " + std::to_string(vsCBStaticModel.VP.m[3]) + "\n" +
    //     std::to_string(vsCBStaticModel.VP.m[4]) + " " + std::to_string(vsCBStaticModel.VP.m[5]) + " " + std::to_string(vsCBStaticModel.VP.m[6]) + " " + std::to_string(vsCBStaticModel.VP.m[7]) + "\n" +
    //     std::to_string(vsCBStaticModel.VP.m[8]) + " " + std::to_string(vsCBStaticModel.VP.m[9]) + " " + std::to_string(vsCBStaticModel.VP.m[10]) + " " + std::to_string(vsCBStaticModel.VP.m[11]) + "\n" +
    //     std::to_string(vsCBStaticModel.VP.m[12]) + " " + std::to_string(vsCBStaticModel.VP.m[13]) + " " + std::to_string(vsCBStaticModel.VP.m[14]) + " " + std::to_string(vsCBStaticModel.VP.m[15]) + "\n"
    //     ).c_str(),
    //     "Info", MB_OK | MB_ICONINFORMATION);


    plane.init(&core, &vsCBStaticModel);

    while (true) {
        core.beginFrame();
        win.processMessages();
        if (win.keys[VK_ESCAPE] == 1) {
            break;
        }

        plane.draw(&core, &vsCBStaticModel);
        core.finishFrame();
    }

    core.flushGraphicsQueue();
    return 0;
}
