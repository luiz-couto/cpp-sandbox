#pragma once

#include "Core.h"
#include "Math.h"
#include "PSOManager.h"
#include "ShaderManager.h"
#include "Mesh.h"

class Sphere {
public:
    Mesh mesh;
    ShaderManager* shaderManager;
    PSOManager psos;
    VertexLayoutCache vertexLayoutCache;

    Sphere(ShaderManager* sm) : shaderManager(sm) {}

    void init(Core* core, VertexShaderCBStaticModel *vsCB) {
        // Build geometry
        std::vector<STATIC_VERTEX> vertices;
        float radius = 1.0f;
        int rings = 16;
        int segments = 16;
        float pi = 3.14159f;

        for (int lat = 0; lat <= rings; lat++) {
            float theta = lat * pi / rings;
            float sinTheta = sinf(theta);
            float cosTheta = cosf(theta);

            for (int lon = 0; lon <= segments; lon++) {
                float phi = lon * 2.0f * pi / segments;
                float sinPhi = sinf(phi);
                float cosPhi = cosf(phi);
                Vec3 position(radius * sinTheta * cosPhi, radius * cosTheta,
                radius * sinTheta * sinPhi);
                Vec3 normal = position.normalize();
                float tu = 1.0f - (float)lon / segments;
                float tv = 1.0f - (float)lat / rings;
                vertices.push_back(addVertex(position, normal, tu, tv));
            }
        }

        std::vector<unsigned int> indices;
        for (int lat = 0; lat < rings; lat++) {
            for (int lon = 0; lon < segments; lon++) {
                int current = lat * (segments + 1) + lon;
                int next = current + segments + 1;
                indices.push_back(current);
                indices.push_back(next);
                indices.push_back(current + 1);
                indices.push_back(current + 1);
                indices.push_back(next);
                indices.push_back(next + 1);
            }
        }

        mesh.initFromVec(core, vertices, indices);

        Shader* vertexShaderBlob = shaderManager->getVertexShader("VertexShader.hlsl", vsCB);
        Shader* pixelShaderBlob = shaderManager->getShader("PixelShader.hlsl", PIXEL_SHADER);
        psos.createPSO(core, "Sphere", vertexShaderBlob->shaderBlob, pixelShaderBlob->shaderBlob, vertexLayoutCache.getStaticLayout());
    }

    void draw(Core* core, VertexShaderCBStaticModel *vsCB) {
        core->beginRenderPass();

        // 1. Bind PSO FIRST
        psos.bind(core, "Sphere");

        // 2. Update constant buffer values
        shaderManager->updateConstantVS("VertexShader.hlsl", "W",  &vsCB->W);
        shaderManager->updateConstantVS("VertexShader.hlsl", "VP", &vsCB->VP);

        // 3. Apply vertex shader (binds CBV)
        shaderManager->getVertexShader("VertexShader.hlsl", vsCB)->apply(core);

        // 4. Draw
        mesh.draw(core);
    }

};