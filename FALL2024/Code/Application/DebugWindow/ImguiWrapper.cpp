/****************************************************************
// File Name: Imgui Wrapper
// © 2025 DigiPen (USA) Corporation
// Authors: Durga Sandeep (Debug window core), Jacob Wilburn (Implementation of Cheat Codes)
// Description: Handles the debug window using Imgui
****************************************************************/

#include "precompiled.h"
#include "ImguiWrapper.h"
#include <iostream>
#include "Engine.h"
#include "Scenes/GameplayDemo.h"
#include "Scenes/CreditsScene.h"
#include "Managers/GlobalSoundManager.h"
#include "Scenes/EndGameScene.h"


ImguiWrapper::~ImguiWrapper()
{

}



void ImguiWrapper::SetDebugWindow() {
    
    windowNeeded = !windowNeeded;
    
}

bool ImguiWrapper::Initialize(GLFWwindow* window)
{
    #ifdef _DEBUG 
	    windowNeeded = true;
    #else
	    windowNeeded = false;
    #endif
//    ImguiWrapper::Instance().SetDebugWindow();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::GetIO().IniFilename = nullptr;

    (void)io;
    ImGui::StyleColorsDark();
    
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        std::cerr << "Failed to initialize ImGui GLFW backend!" << std::endl;
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 330")) {
        std::cerr << "Failed to initialize ImGui OpenGL3 backend!" << std::endl;
        return false;
    }

    return true;
}

//
//Must be called for setting the Imgui NewFrame
void ImguiWrapper::NewFrameSetup() {

    if (!FontLoaded) {
        FontLoaded = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/KenneyFuture.ttf", 30.0f);
        IM_ASSERT(FontLoaded != nullptr);
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

   
}


//Setting the Imgui window elements
void ImguiWrapper::SetElements( ){

    if (windowNeeded == true) {
        ImVec2 Pos(50, 20); // X=100, Y=200
        ImGui::SetWindowSize(ImVec2((float)ImGuiWidth, (float)ImGuiHeight));
        ImGui::Begin("DEBUG WINDOW");
        ImGui::Separator();
        float fps = Engine::Instance().GetTime()->GetFPS();
        ImGui::Separator();
        ImGui::NewLine();
        ImGui::Text("FPS : %.2f", fps);
        ImGui::NewLine();
        ImGui::Separator();
        ImGui::Separator();

        ImGui::Text("MEMORY MANAGER DATA");
        ImGui::Separator();
        ImGui::Separator();
        ImGui::NewLine();
        ImGui::Indent(20.0f);
        ImGui::Text("Allocated Objects :  %d", MemoryManager::Instance().GetDebugMemoryData().allocatedObjects);
        ImGui::Unindent(20.0f);
        ImGui::NewLine();
        ImGui::Indent(20.0f);
        ImGui::Text("MemoryPool Size :  %d", MemoryManager::Instance().GetDebugMemoryData().memoryPoolSize);
        ImGui::Unindent(20.0f);
        ImGui::NewLine();
        ImGui::Indent(20.0f);
        ImGui::Text("FreeList Size :  %d", MemoryManager::Instance().GetDebugMemoryData().freeListSize);
        ImGui::Unindent(20.0f);
        ImGui::Separator();
        ImGui::Separator();
        ImGui::Text("Total Created Objects :  %d", MemoryManager::Instance().GetDebugMemoryData().totalCreatedObject);
        ImGui::Unindent(20.0f);
        ImGui::Separator();
        ImGui::Separator();

        ImGui::Text("EVENT MANAGER DATA");
        ImGui::Separator();
        ImGui::Separator();
        ImGui::NewLine();
        ImGui::Indent(20.0f);
        ImGui::Text("Active Listener Count :  %d", EventManager::Instance().GetActiveListenerCount());

        ImGui::NewLine();
        ImGui::Separator();
        ImGui::Text("Test Methods Below");
        ImGui::Separator();
        //ImGui::SetCursorPos(Pos);

		if (ImGui::Button("SHOW CREDITS")) {
			SceneManager::Instance().PushScene<CreditsScene>("CreditsScene");

		}


        if (ImGui::Button("MUTE MUSIC")) {
            if (!bgmPaused) {
                GlobalSoundManager::Instance().PauseBGM();
				bgmPaused = true;
            }
            else {
				GlobalSoundManager::Instance().PlayBGM();
				bgmPaused = false;
            }
        }

        if (ImGui::Button("MOVE TO NEXT ROOM")) {
			auto enemyList = GameManager::Instance().GetEnemies();
			for (auto enemy : enemyList)
			{
                GameObject::Destroy(enemy);
			}
			GameManager::Instance().DoorOpen();
			GameManager::Instance().GoToNextDungeon();
        }

        if (ImGui::Button("MOVE TO BOSS AREA")) {
            auto enemyList = GameManager::Instance().GetEnemies();
            for (auto enemy : enemyList)
            {
                GameObject::Destroy(enemy);
            }
            GameManager::Instance().SetBossTrigger(0);
            GameManager::Instance().DoorOpen();
            GameManager::Instance().GoToNextDungeon();
        }

        if (ImGui::Button("MOVE TO END SCENE")) {
            GameManager::Instance().ResetAfterGameOver(true);
			TransitionManager::Instance().QueueSceneChange<EndGameScene>("EndGameScene");
        }

        if (ImGui::Button("INSTANT LOSE")) {
            GameManager::Instance().IsGameOver();
        }

        if (ImGui::Button("GOD MODE")) {
            if (godMode) {
                TurnOffGodMode();
                godMode = false;
            }
            else {
                SetGodMode();
                godMode = true;
            }
        }

        if (ImGui::Button("INSTANT KILL")) {
            ToggleInstantKill();
        }

        if (ImGui::Button("QUIT")) {
            QuitMethod();
        }
        ImGui::Separator();

        if (ImGui::Checkbox("Enable Debug Collisions", &enableDebugCall))
        {
            Engine::Instance().SetDebugMode(enableDebugCall);
        }
        ImGui::Separator();



        ImGui::End();
    }
}





void ImguiWrapper::RenderCall() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiWrapper::Clear() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}



void ImguiWrapper::PhysicsDebug( ) {
    std::cout << "Physics Debug " << std::endl;
}

void  ImguiWrapper::FPSDebug( ) {

}

void ImguiWrapper::QuitMethod() {
    std::cout << "Quit Method " << std::endl;
    Engine::Instance().Quit();
}

void ImguiWrapper::SetGodMode()
{
	GameManager::Instance().GodModeOn();
}

void ImguiWrapper::TurnOffGodMode()
{
	GameManager::Instance().GodModeOff();
}

void ImguiWrapper::ToggleInstantKill()
{
	GameManager::Instance().InstantKillToggle();
}

void ImguiWrapper::RenderUI_Test()
{
    if (windowNeeded == true) {

        ImGui::Begin("DEBUG WINDOW");

        //Section 1 - DEBUG FPS
        ImVec4 sectionColor = ImVec4(0.3f, 0.6f, 0.3f, 1.0f);
        ImVec2 cursorPos1 = ImGui::GetCursorScreenPos();
        ImVec2 textSize1 = ImGui::CalcTextSize("DEBUG FPS");

        ImDrawList* drawList = ImGui::GetWindowDrawList();
        drawList->AddRectFilled(cursorPos1, ImVec2(cursorPos1.x + textSize1.x + 10, cursorPos1.y + textSize1.y + 5), ImColor(sectionColor));

        //Text Color White
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

        // Draw the title text on top of the background
        ImGui::Text("DEBUG FPS");
        //
        ImGui::PopStyleColor();

        // Create a regular separator
        ImGui::Separator();

        // Manually set cursor position for the checkbox and label
        ImVec2 cursorPos2(20, 150); // Set position at (20, 150)
        ImGui::SetCursorPos(cursorPos2);
        bool checkboxState = false;
        ImGui::Checkbox("Enable Feature", &checkboxState);

        // Add some space between the elements
        ImGui::Spacing();

        // Place a button and set cursor position manually
        ImVec2 cursorPos3(20, 200); // Set position at (20, 200)
        ImGui::SetCursorPos(cursorPos3);
        if (ImGui::Button("Click Me"))
        {
            // Button clicked, do something
        }

        // Create another regular separator for grouping
        ImGui::Separator();

        // Section 2 with background
        ImVec2 cursorPos4 = ImGui::GetCursorScreenPos(); // Get position for "Section 2"
        ImVec2 textSize2 = ImGui::CalcTextSize("Section 2");
        drawList->AddRectFilled(cursorPos4, ImVec2(cursorPos4.x + textSize2.x + 10, cursorPos4.y + textSize2.y + 5), ImColor(0.3f, 0.3f, 0.6f, 1.0f)); // Blue background

        // Set text color to white for contrast
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

        // Draw the title text on top of the background
        ImGui::Text("Section 2");

        // Reset text color
        ImGui::PopStyleColor();

        // Manually set cursor position for the checkbox and label in Section 2
        ImVec2 cursorPos5(20, 250); // Set position at (20, 250)
        ImGui::SetCursorPos(cursorPos5);
        bool anotherCheckboxState = false;
        ImGui::Checkbox("Enable Option", &anotherCheckboxState);

        // Add a final button with custom positioning
        ImVec2 cursorPos6(20, 300); // Set position at (20, 300)
        ImGui::SetCursorPos(cursorPos6);
        if (ImGui::Button("Submit"))
        {
            // Submit action
        }

        ImGui::End();

    }
}
