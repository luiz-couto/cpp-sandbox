#pragma once

#include "Core.h"
#include "Math.h"
#include "PSOManager.h"
#include "ShaderManager.h"
#include "Mesh.h"

class Cube {
public:
    Mesh mesh;
    ShaderManager* shaderManager;
    PSOManager psos;
    VertexLayoutCache vertexLayoutCache;

    Cube(ShaderManager* sm) : shaderManager(sm) {}

    void init(Core* core, VertexShaderCBStaticModel *vsCB) {
        // Build geometry
        std::vector<STATIC_VERTEX> vertices;
        Vec3 p0 = Vec3(-1.0f, -1.0f, -1.0f);
        Vec3 p1 = Vec3(1.0f, -1.0f, -1.0f);
        Vec3 p2 = Vec3(1.0f, 1.0f, -1.0f);
        Vec3 p3 = Vec3(-1.0f, 1.0f, -1.0f);
        Vec3 p4 = Vec3(-1.0f, -1.0f, 1.0f);
        Vec3 p5 = Vec3(1.0f, -1.0f, 1.0f);
        Vec3 p6 = Vec3(1.0f, 1.0f, 1.0f);
        Vec3 p7 = Vec3(-1.0f, 1.0f, 1.0f);

        // Add faces
        vertices.push_back(addVertex(p0, Vec3(0.0f, 0.0f, -1.0f), 0.0f, 1.0f));
        vertices.push_back(addVertex(p1, Vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f));
        vertices.push_back(addVertex(p2, Vec3(0.0f, 0.0f, -1.0f), 1.0f, 0.0f));
        vertices.push_back(addVertex(p3, Vec3(0.0f, 0.0f, -1.0f), 0.0f, 0.0f));
        vertices.push_back(addVertex(p5, Vec3(0.0f, 0.0f, 1.0f), 0.0f, 1.0f));
        vertices.push_back(addVertex(p4, Vec3(0.0f, 0.0f, 1.0f), 1.0f, 1.0f));
        vertices.push_back(addVertex(p7, Vec3(0.0f, 0.0f, 1.0f), 1.0f, 0.0f));
        vertices.push_back(addVertex(p6, Vec3(0.0f, 0.0f, 1.0f), 0.0f, 0.0f));
        vertices.push_back(addVertex(p4, Vec3(-1.0f, 0.0f, 0.0f), 0.0f, 1.0f));
        vertices.push_back(addVertex(p0, Vec3(-1.0f, 0.0f, 0.0f), 1.0f, 1.0f));
        vertices.push_back(addVertex(p3, Vec3(-1.0f, 0.0f, 0.0f), 1.0f, 0.0f));
        vertices.push_back(addVertex(p7, Vec3(-1.0f, 0.0f, 0.0f), 0.0f, 0.0f));

        vertices.push_back(addVertex(p1, Vec3(1.0f, 0.0f, 0.0f), 0.0f, 1.0f));
        vertices.push_back(addVertex(p5, Vec3(1.0f, 0.0f, 0.0f), 1.0f, 1.0f));
        vertices.push_back(addVertex(p6, Vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.0f));
        vertices.push_back(addVertex(p2, Vec3(1.0f, 0.0f, 0.0f), 0.0f, 0.0f));
        vertices.push_back(addVertex(p3, Vec3(0.0f, 1.0f, 0.0f), 0.0f, 1.0f));
        vertices.push_back(addVertex(p2, Vec3(0.0f, 1.0f, 0.0f), 1.0f, 1.0f));
        vertices.push_back(addVertex(p6, Vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.0f));
        vertices.push_back(addVertex(p7, Vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f));
        vertices.push_back(addVertex(p4, Vec3(0.0f, -1.0f, 0.0f), 0.0f, 1.0f));
        vertices.push_back(addVertex(p5, Vec3(0.0f, -1.0f, 0.0f), 1.0f, 1.0f));
        vertices.push_back(addVertex(p1, Vec3(0.0f, -1.0f, 0.0f), 1.0f, 0.0f));
        vertices.push_back(addVertex(p0, Vec3(0.0f, -1.0f, 0.0f), 0.0f, 0.0f));

        std::vector<unsigned int> indices;
        indices.push_back(0); indices.push_back(1); indices.push_back(2);
        indices.push_back(0); indices.push_back(2); indices.push_back(3);
        indices.push_back(4); indices.push_back(5); indices.push_back(6);
        indices.push_back(4); indices.push_back(6); indices.push_back(7);
        indices.push_back(8); indices.push_back(9); indices.push_back(10);
        indices.push_back(8); indices.push_back(10); indices.push_back(11);
        indices.push_back(12); indices.push_back(13); indices.push_back(14);
        indices.push_back(12); indices.push_back(14); indices.push_back(15);
        indices.push_back(16); indices.push_back(17); indices.push_back(18);
        indices.push_back(16); indices.push_back(18); indices.push_back(19);
        indices.push_back(20); indices.push_back(21); indices.push_back(22);
        indices.push_back(20); indices.push_back(22); indices.push_back(23);

        mesh.initFromVec(core, vertices, indices);

        Shader* vertexShaderBlob = shaderManager->getVertexShader("VertexShader.hlsl", vsCB);
        Shader* pixelShaderBlob = shaderManager->getShader("PixelShader.hlsl", PIXEL_SHADER);
        psos.createPSO(core, "Cube", vertexShaderBlob->shaderBlob, pixelShaderBlob->shaderBlob, vertexLayoutCache.getStaticLayout());
    }

    void draw(Core* core, VertexShaderCBStaticModel *vsCB) {
        core->beginRenderPass();

        // 1. Bind PSO FIRST
        psos.bind(core, "Cube");

        // 2. Update constant buffer values
        shaderManager->updateConstantVS("VertexShader.hlsl", "W",  &vsCB->W);
        shaderManager->updateConstantVS("VertexShader.hlsl", "VP", &vsCB->VP);

        // 3. Apply vertex shader (binds CBV)
        shaderManager->getVertexShader("VertexShader.hlsl", vsCB)->apply(core);

        // 4. Draw
        mesh.draw(core);
    }

};