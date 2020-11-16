#include "NsCore/ReflectionImplementEmpty.h"
#include "NsGui/IntegrationAPI.h"

#include "PauseMenu.hpp"


namespace GameGUI {
    PauseMenu::PauseMenu() {
        InitializeComponent();
    }

    void PauseMenu::InitializeComponent() {
        Noesis::GUI::LoadComponent(this, "PauseMenu.xaml");
    }
}

NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(GameGUI::PauseMenu, "GameGUI.PauseMenu")
