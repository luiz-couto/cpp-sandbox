#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Core.h"
#include "ConstantBufferReflection.h"

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

class Shader {
    public:
    ID3DBlob* shaderBlob;
    ConstantBufferReflection* constantBufferReflection;
    ShaderKind kind;

    void apply(Core* core) {
        if (constantBufferReflection == nullptr) {
            return;
        }
        int rootSignatureIndex = (kind == VERTEX_SHADER) ? 0 : 1;
        core->getCommandList()->SetGraphicsRootConstantBufferView(rootSignatureIndex, constantBufferReflection->getGPUAddress());
        //MessageBoxA(NULL, ("GPU ADRESS 2: " + std::to_string(constantBufferReflection->getGPUAddress())).c_str(), "Info", MB_OK | MB_ICONINFORMATION);
        constantBufferReflection->next();
    }
};

class ShaderManager {
public:
    std::unordered_map<std::string, Shader> shaders;
    Core *core;

    ShaderManager(Core* _core) : core(_core) {}

    void loadConstantBufferReflection(ID3DBlob* shaderBlob, ConstantBufferReflection *reflectionBuffer) {
        ID3D12ShaderReflection *reflection;
        HRESULT hr = D3DReflect(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), IID_PPV_ARGS(&reflection));
        if (FAILED(hr)) {
            MessageBoxA(NULL, "Failed to reflect shader", "Shader Reflection Error", MB_OK | MB_ICONERROR);
            return;
        }
        D3D12_SHADER_DESC desc;
        reflection->GetDesc(&desc);

        for (int i = 0; i < desc.ConstantBuffers; i++) {
            ID3D12ShaderReflectionConstantBuffer* constantBuffer = reflection->GetConstantBufferByIndex(i);
            D3D12_SHADER_BUFFER_DESC cbDesc;
            constantBuffer->GetDesc(&cbDesc);
            reflectionBuffer->name = cbDesc.Name;
            unsigned int totalSize = 0;

            for (int j = 0; j < cbDesc.Variables; j++) {
                ID3D12ShaderReflectionVariable* var = constantBuffer->GetVariableByIndex(j);
                D3D12_SHADER_VARIABLE_DESC vDesc;
                var->GetDesc(&vDesc);
                ConstantBufferVariable bufferVariable;
                bufferVariable.offset = vDesc.StartOffset;
                bufferVariable.size = vDesc.Size;
                reflectionBuffer->constantBufferData.insert({vDesc.Name, bufferVariable});
                totalSize += bufferVariable.size;
            }
        }
    }

    template <typename T>
    Shader* getShader(std::string filename, ShaderKind kind, T *cpuConstantBufferStruct) {
        auto it = shaders.find(filename);
        if (it != shaders.end()) {
            return &shaders[filename];
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

        ConstantBufferReflection* constantBufferReflection = nullptr;
        if (cpuConstantBufferStruct != nullptr) {
            constantBufferReflection = new ConstantBufferReflection();
            constantBufferReflection->init(core, sizeof(*cpuConstantBufferStruct));
            loadConstantBufferReflection(shader, constantBufferReflection);
            //MessageBoxA(NULL, ("GPU ADRESS 1: " + std::to_string(constantBufferReflection->getGPUAddress())).c_str(), "Info", MB_OK | MB_ICONINFORMATION);
        }
        
        shaders.insert({filename, {shader, constantBufferReflection, kind}});
        return &shaders[filename];
    }

    Shader* getShader(std::string filename, ShaderKind kind) {
        auto it = shaders.find(filename);
        if (it != shaders.end()) {
            return &shaders[filename];
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
        
        shaders.insert({filename, {shader, nullptr, kind}});
        return &shaders[filename];
    }

    template <typename T>
    void updateConstantVS(std::string shaderFilename, std::string varName, T* data) {
        auto it = shaders.find(shaderFilename);
        if (it == shaders.end()) {
            MessageBoxA(NULL, ("Shader not found: " + shaderFilename).c_str(), "Error", MB_OK | MB_ICONERROR);
            return;
        }
        Shader& shader = it->second;
        shader.constantBufferReflection->update(varName, data);
    }

    template <typename T>
    Shader* getVertexShader(std::string filename, T *cpuConstantBufferStruct) {
        return getShader(filename, VERTEX_SHADER, cpuConstantBufferStruct);
    }

    template <typename T>
    Shader* getPixelShader(std::string filename, T *cpuConstantBufferStruct) {
        return getShader(filename, PIXEL_SHADER, cpuConstantBufferStruct);
    }

    ~ShaderManager() {
        for (auto& pair : shaders) {
            if (pair.second.shaderBlob) {
                pair.second.shaderBlob->Release();
            }
        }
    }

};