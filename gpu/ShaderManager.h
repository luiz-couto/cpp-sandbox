#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include "Core.h"

enum ShaderKind {
    VERTEX_SHADER,
    PIXEL_SHADER
};

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

class ShaderManager {
public:
    std::unordered_map<std::string, ID3DBlob*> shaders;

    ID3DBlob* getShader(std::string filename, ShaderKind kind) {
        auto it = shaders.find(filename);
        if (it != shaders.end()) {
            return shaders[filename];
        }

        ID3DBlob* shader;
        ID3DBlob* status;
        std::string entryPoint = (kind == VERTEX_SHADER) ? "VS" : "PS";
        std::string target = (kind == VERTEX_SHADER) ? "vs_5_0" : "ps_5_0";

        std::string shaderStr = readFile(filename);
        HRESULT hr = D3DCompile(shaderStr.c_str(),strlen(shaderStr.c_str()), NULL, NULL, NULL, entryPoint.c_str(), target.c_str(), 0, 0, &shader, &status);
        if (FAILED(hr)) {
            MessageBoxA(NULL, (char*)status->GetBufferPointer(), (filename + " Shader Compilation Error").c_str(), MB_OK | MB_ICONERROR);
            return nullptr;
        }

        shaders.insert({filename, shader});
        return shader;
    }

    ID3DBlob* getVertexShader(std::string filename) {
        return getShader(filename, VERTEX_SHADER);
    }

    ID3DBlob* getPixelShader(std::string filename) {
        return getShader(filename, PIXEL_SHADER);
    }

    ~ShaderManager() {
        for (auto& pair : shaders) {
            if (pair.second) {
                pair.second->Release();
            }
        }
    }

};