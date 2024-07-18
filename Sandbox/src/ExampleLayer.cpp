#include "ExampleLayer.h"

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define LOG_INPUT 0

ExampleLayer::ExampleLayer()
    : Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
{
    m_VertexArray = Ember::VertexArray::Create();

    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
    };

    Ember::Ref<Ember::VertexBuffer> vertexBuffer = Ember::VertexBuffer::Create(vertices, sizeof(vertices));
    Ember::BufferLayout layout = {
        { Ember::ShaderDataType::Float3, "a_Position" },
        { Ember::ShaderDataType::Float4, "a_Color" }
    };
    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[3] = { 0, 1, 2 };
    Ember::Ref<Ember::IndexBuffer> indexBuffer = Ember::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_SquareVA = Ember::VertexArray::Create();

    float squareVertices[5 * 4] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    Ember::Ref<Ember::VertexBuffer> squareVB = Ember::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
    squareVB->SetLayout({
        { Ember::ShaderDataType::Float3, "a_Position" },
        { Ember::ShaderDataType::Float2, "a_TextCoord" }
    });

    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Ember::Ref<Ember::IndexBuffer> squareIB = Ember::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_SquareVA->SetIndexBuffer(squareIB);

    std::string vertexSrc = R"(
        #version 330 core
        
        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

        out vec3 v_Position;
        out vec4 v_Color;

        void main()
        {
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core
        
        layout(location = 0) out vec4 color;

        in vec3 v_Position;
        in vec4 v_Color;

        void main()
        {
            color = vec4(v_Position * 0.5 + 0.5, 1.0);
            color = v_Color;
        }
    )";

    m_Shader = Ember::Shader::Create("VertexColorTriangle", vertexSrc, fragmentSrc);

    std::string flatShaderVertexSrc = R"(
        #version 330 core
        
        layout(location = 0) in vec3 a_Position;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

        out vec3 v_Position;

        void main()
        {
            v_Position = a_Position;
            gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
        }
    )";

    std::string flatShaderFragmentSrc = R"(
        #version 330 core
        
        layout(location = 0) out vec4 color;

        in vec3 v_Position;

        uniform vec3 u_Color;

        void main()
        {
            color = vec4(u_Color, 1.0);
        }
    )";

    m_FlatColorShader = Ember::Shader::Create("DiscoShader", flatShaderVertexSrc, flatShaderFragmentSrc);

    auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

    m_Texture = Ember::Texture2D::Create("assets/textures/Checkerboard.png");
    m_Texture2 = Ember::Texture2D::Create("assets/textures/opengl.png");

    textureShader->Bind();
    textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnAttach()
{
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Ember::Timestep ts)
{
    // EMBER_INFO("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    Ember::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Ember::RenderCommand::Clear();

    Ember::Renderer::BeginScene(m_CameraController.GetCamera());

    static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    m_FlatColorShader->Bind();
    m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

    for(int y = 0; y < 20; y++)
    {
        for(int x = 0; x < 20; x++)
        {
            glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
            Ember::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
        }
    }

    auto textureShader = m_ShaderLibrary.Get("Texture");

    m_Texture->Bind();
    Ember::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    
    m_Texture2->Bind();
    Ember::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    // Triangle
    // Ember::Renderer::Submit(m_Shader, m_VertexArray);

    Ember::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void ExampleLayer::OnEvent(Ember::Event& event)
{

    m_CameraController.OnEvent(event);

    #if LOG_INPUT
    {
        // log keystrokes
        if(event.GetEventType() == Ember::EventType::KeyPressed)
        {
            Ember::KeyPressedEvent& e = (Ember::KeyPressedEvent&)event;
            EMBER_TRACE("{0}", (char)e.GetKeyCode());
        }

        // log mouse clicks
        if(event.GetEventType() == Ember::EventType::MouseButtonPressed)
        {
            Ember::MouseButtonPressedEvent& e = (Ember::MouseButtonPressedEvent&)event;
            EMBER_TRACE("Mouse button {0} pressed", e.GetMouseButton());
        }

        // log mouse movement
        if(event.GetEventType() == Ember::EventType::MouseMoved)
        {
            Ember::MouseMovedEvent& e = (Ember::MouseMovedEvent&)event;
            EMBER_TRACE("Mouse moved to {0}, {1}", e.GetX(), e.GetY());
        }

        // log mouse scroll
        if(event.GetEventType() == Ember::EventType::MouseScrolled)
        {
            Ember::MouseScrolledEvent& e = (Ember::MouseScrolledEvent&)event;
            EMBER_TRACE("Mouse scrolled by {0}, {1}", e.GetXOffset(), e.GetYOffset());
        }
    }
    #endif

}