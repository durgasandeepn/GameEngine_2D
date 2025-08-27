/****************************************************************
// File Name: Engine
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Team - everyone in the team modified this file often
// Description: Core engine system. Singleton that handles the main game loop's update
// and draw calls. Holds references to core game systems.
****************************************************************/

#include "precompiled.h"
#include "Engine.h"

bool Engine::Initialize(const EngineConfig& config)
{
    /*
    * Initializes systems here in the Engine.
    * I.e., if a system exists solely in the Engine, this is where they get
    * created by calling "make_shared" for example.
    */
    assert(&config);

    if (!InitializeWindow(config)) {
        std::cerr << "Failed to initialize window, terminating game." << std::endl;
        return false;
    }

    if (!InitializeRenderer()) {
        std::cerr << "Failed to initialize renderer, terminating game." << std::endl;
        return false;
    }

    if (!InitializeDebugWindowSystem()) {
        std::cerr << "Failed to initialize audio system, terminating game." << std::endl;
        return false;
    }
    else {
        std::cerr << "DONE " << std::endl;
    }


    // Assign local variables from config
    fixedTimeStep = config.fixedTimeStep;
    debugMode = config.debugMode;

    /* 
    * Initialization for systems that are singletons.
    * I.e., retrieves each singleton instance and stores it locally here
    * to be referenced by the Engine.
    */
    input = &Input::Instance();
    assert(input);
    input->Initialize(window.get());

    time = &Time::Instance();
    assert(time);

    physicsManager = &PhysicsManager::Instance();
    assert(physicsManager);

    renderManager = &RenderManager::Instance();
    assert(renderManager);

    audioManager = &AudioManager::Instance();
    assert(audioManager);
    audioManager->Initialize();

    // Initialize ResourceManager with engine systems needed by engine components
    ResourceManager::Instance().Initialize(
        renderer.get(),
        audioManager,
        window.get()
    );

    MemoryManager::Instance().Initialize();

    return true;
}

void Engine::Update()
{
    time->StartFrame();
    input->Update();

    if (!SceneManager::Instance().IsTransitioning()) {

        float scale = 1.0f;
        if (SceneManager::Instance().IsPause())
        {
            scale = 0.0f;
        }

        while (time->ShouldUpdatePhysics(fixedTimeStep)) {
            physicsManager->Update(time->GetDeltaTime(scale));
            time->ConsumePhysicsTime(fixedTimeStep);
        }

        SceneManager::Instance().Update(time->GetDeltaTime(1.0));

        
        if (input->IsKeyPressed(KeyCode::Tilda)) {
            ImguiWrapper::Instance().SetDebugWindow();
        }
        

        audioManager->Update();

		if (input->IsKeyPressed(KeyCode::F11))
		{
			SetFullscreen(!window->IsFullscreen());
		}
    }

}

void Engine::Render()
{
    renderer->Clear(0.0f, 0.0f, 0.0f, 1.0f);

    debugWindow->NewFrameSetup();//Debugwindow 

    renderManager->Render(debugMode);
    debugWindow->SetElements( );
    debugWindow->RenderCall();//Debugwindow 

    renderer->SwapBuffers();

    time->EndFrame();
}

bool Engine::IsRunning() const
{
    return window && !window->ShouldClose();
}

void Engine::Shutdown()
{
    assert(debugWindow);
    debugWindow->Clear();

    assert(physicsManager);
    physicsManager->ClearBodies();

    assert(renderManager);
    renderManager->ClearRenderables();

    SceneManager::Instance().Shutdown();
    ResourceManager::Instance().Shutdown();
    MemoryManager::Instance().Shutdown();

    assert(renderer);
    renderer.reset();

    assert(window);
    window.reset();

    assert(audioManager);
    audioManager->Shutdown();
}

void Engine::Quit()
{
    assert(window);
    glfwSetWindowShouldClose(window->GetNativeWindow(), true);
}

void Engine::SetFullscreen(bool isFullscreen)
{
    assert(window);
    window->SetIsFullscreen(isFullscreen);
}

void Engine::SetResolution(Resolution res)
{
    assert(window);
    window->SetResolution(res);
}

bool Engine::InitializeWindow(const EngineConfig& config)
{
    try {
        window = std::make_unique<GameWindow>(
            config.windowWidth,
            config.windowHeight,
            config.windowTitle
        );
        assert(window);
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Window creation failed: " << e.what() << std::endl;
        return false;
    }
}

bool Engine::InitializeRenderer()
{
    try {
        renderer = std::make_unique<Renderer>(*window);
        assert(renderer);
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Renderer creation failed: " << e.what() << std::endl;
        return false;
    }
}

bool Engine::InitializeDebugWindowSystem( )//DebugWindow
{   
    debugWindow = &ImguiWrapper::Instance();
    assert(debugWindow);
    bool result = debugWindow->Initialize(window->GetNativeWindow());

    return result;

}

