#pragma once

#include "Core.h"
#include "Math.h"
#include "PSOManager.h"
#include "ShaderManager.h"
#include "Mesh.h"

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