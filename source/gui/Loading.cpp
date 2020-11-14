#include "NsCore/ReflectionImplementEmpty.h"
#include "NsGui/IntegrationAPI.h"

#include "Loading.hpp"


namespace GameGUI {
    Loading::Loading() {
        InitializeComponent();
    }

    void Loading::InitializeComponent() {
        Noesis::GUI::LoadComponent(this, "Loading.xaml");
    }
}

NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(GameGUI::Loading, "GameGUI.Loading")
