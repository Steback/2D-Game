#include "NsCore/ReflectionImplementEmpty.h"
#include "NsGui/IntegrationAPI.h"

#include "EndGame.hpp"


namespace GameGUI {

    EndGame::EndGame() {
        InitializeComponent();
    }

    void EndGame::InitializeComponent() {
        Noesis::GUI::LoadComponent(this, "EndGame.xaml");
    }
}

NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(GameGUI::EndGame, "GameGUI.EndGame")