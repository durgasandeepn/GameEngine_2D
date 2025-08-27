/****************************************************************
// File Name: LobbyUICreator
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Creates the layout for the lobby screen and various UI components
****************************************************************/

#pragma once
class GameObject;
class Vector3;
class LobbyUICreator
{
public:
	LobbyUICreator();

    GameObject* CreateCharacterBackgroundUI(Vector3 pos, Vector3 scale);
    GameObject* CreateStartUI(Vector3 pos, Vector3 scale);
    GameObject* CreateSelectYourCharacterUI(Vector3 pos, Vector3 scale);
    GameObject* CreateCharacterUI(Vector3 pos, Vector3 scale, int playerIndex);
    GameObject* CreateReadyIndicator(Vector3 pos, Vector3 scale);
    GameObject* CreateJoinPrompt(Vector3 pos, Vector3 scale);
};
