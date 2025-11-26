#include "Window.h"
#include "Core.h"
#include "Math.h"

// Refactor to a mesh class later
struct PRIM_VERTEX {
    Vec3 position;
    Colour colour;
};

// What to draw
class Mesh {
    public:
    ID3D12Resource* vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW vbView;

    Mesh(){}

    void init(Core* core, void* vertices, int vertexSizeInBytes, int numVertices) {
        D3D12_HEAP_PROPERTIES heapprops = {};
        heapprops.Type = D3D12_HEAP_TYPE_DEFAULT;
        heapprops.CreationNodeMask = 1;
        heapprops.VisibleNodeMask = 1;

        D3D12_RESOURCE_DESC vbDesc = {};
        vbDesc.Width = numVertices * vertexSizeInBytes;
        vbDesc.Height = 1;
        vbDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        vbDesc.DepthOrArraySize = 1;
        vbDesc.MipLevels = 1;
        vbDesc.SampleDesc.Count = 1;
        vbDesc.SampleDesc.Quality = 0;
        vbDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        core->device->CreateCommittedResource(&heapprops, D3D12_HEAP_FLAG_NONE, &vbDesc,
        D3D12_RESOURCE_STATE_COMMON, NULL, IID_PPV_ARGS(&vertexBuffer));

        core->uploadResource(vertexBuffer, vertices, numVertices * vertexSizeInBytes, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
        
        vbView.BufferLocation = vertexBuffer->GetGPUVirtualAddress(); // point where the buffer is located in GPU memory
        vbView.StrideInBytes = vertexSizeInBytes; // size of each vertex. Everytime we step forward in the buffer, we move by this size
        vbView.SizeInBytes = numVertices * vertexSizeInBytes;

    }

    void draw(Core* core) {
        core->getCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        core->getCommandList()->IASetVertexBuffers(0, 1, &vbView);
        core->getCommandList()->DrawInstanced(3, 1, 0, 0);
    }

};

// What to draw
class ScreenSpaceTriangle {
    public:
    PRIM_VERTEX vertices[3];
    Mesh mesh;

    // We may want to share this between multiple meshes later. Like a storage of Layouts. A new class
    D3D12_INPUT_ELEMENT_DESC inputLayout[2];
    D3D12_INPUT_LAYOUT_DESC inputLayoutDesc;

    ScreenSpaceTriangle() {}

    void init(Core* core) {
        PRIM_VERTEX vertices[3];
        vertices[0].position = Vec3(0, 1.0f, 0);
        vertices[0].colour = Colour(0, 1.0f, 0);
        vertices[1].position = Vec3(-1.0f, -1.0f, 0);
        vertices[1].colour = Colour(1.0f, 0, 0);
        vertices[2].position = Vec3(1.0f, -1.0f, 0);
        vertices[2].colour = Colour(0, 0, 1.0f);

        mesh.init(core, &vertices[0], sizeof(PRIM_VERTEX), 3);

        // The names are used after in the shader to link the vertex data to the shader inputs
        inputLayout[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
        inputLayout[1] = { "COLOUR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
        inputLayoutDesc.NumElements = 2;
        inputLayoutDesc.pInputElementDescs = inputLayout;
    }
};


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    Window win;
    Core core;
    win.init(1024, 1024, 0, 0, "My Window");
    core.init(win.hwnd, win.windowWidth, win.windowHeight);

    while (true) {
        core.resetCommandList();
        core.beginFrame();
        win.processMessages();
        if (win.keys[VK_ESCAPE] == 1) {
            break;
        }
        core.finishFrame();
    }

    core.flushGraphicsQueue();
    return 0;
}
