#include <array>

#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"
#include "NsCore/RegisterComponent.h"
#include "NsApp/EmbeddedXamlProvider.h"
#include "NsApp/EmbeddedTextureProvider.h"
#include "NsCore/EnumConverter.h"
#include "NsApp/Interaction.h"
#include "NsApp/DataTrigger.h"
#include "NsApp/TriggerCollection.h"
#include "NsApp/KeyTrigger.h"
#include "NsApp/InvokeCommandAction.h"
#include "NsApp/ControlStoryboardAction.h"
#include "NsApp/ChangePropertyAction.h"
#include "NsApp/EventTrigger.h"
#include "NsApp/TriggerActionCollection.h"
#include "NsApp/SetFocusAction.h"
#include "NsApp/PlaySoundAction.h"

#include "Gui.hpp"
#include "MainWindow.hpp"
#include "ViewModel.hpp"
#include "MainMenu.hpp"
#include "NewGame.hpp"
#include "Loading.hpp"
#include "GameView.hpp"
#include "PauseMenu.hpp"
#include "EndGame.hpp"
#include "LoadGame.hpp"
#include "Resourses.hpp"


Gui::Gui() = default;

Gui::~Gui() = default;

void Gui::init() {
    Noesis::SetLogHandler([](const char*, uint32_t, uint32_t level, const char*, const char* msg)
                          {
                              // [TRACE] [DEBUG] [INFO] [WARNING] [ERROR]
                              std::array<char, 5> prefixes = { 'T',
                                                               'D',
                                                               'I',
                                                               'W',
                                                               'E' };

                              switch (prefixes[level]) {
                                  case 'T':
                                      spdlog::trace("[NOESIS] {}" , msg); break;
                                  case 'D':
                                      spdlog::debug("[NOESIS] {}" , msg); break;
                                  case 'I':
                                      spdlog::info("[NOESIS] {}" , msg); break;
                                  case 'W':
                                      spdlog::warn("[NOESIS] {}" , msg); break;
                                  case 'E':
                                      spdlog::error("[NOESIS] {}" , msg); break;
                              }
                          });

    Noesis::GUI::Init("Steback", "HLwRF7P0EReiR6OQGGCrekCPPyct2yzQmIsRKrTRHSnlGE7C");

    Noesis::TypeOf<NoesisApp::Interaction>();

    Noesis::RegisterComponent<NoesisApp::DataTrigger>();
    Noesis::RegisterComponent<NoesisApp::TriggerCollection>();
    Noesis::RegisterComponent<NoesisApp::KeyTrigger>();
    Noesis::RegisterComponent<NoesisApp::InvokeCommandAction>();
    Noesis::RegisterComponent<NoesisApp::ChangePropertyAction>();
    Noesis::RegisterComponent<NoesisApp::EventTrigger>();
    Noesis::RegisterComponent<NoesisApp::PropertyChangedTrigger>();
    Noesis::RegisterComponent<NoesisApp::TriggerActionCollection>();
    Noesis::RegisterComponent<NoesisApp::SetFocusAction>();
    Noesis::RegisterComponent<NoesisApp::ControlStoryboardAction>();
    Noesis::RegisterComponent<NoesisApp::PlaySoundAction>();
    Noesis::RegisterComponent<Noesis::EnumConverter<NoesisApp::ComparisonConditionType>>();
    Noesis::RegisterComponent<Noesis::EnumConverter<NoesisApp::KeyTriggerFiredOn>>();

    Noesis::RegisterComponent<GameGUI::MainWindow>();
    Noesis::RegisterComponent<GameGUI::MainMenu>();
    Noesis::RegisterComponent<GameGUI::NewGame>();
    Noesis::RegisterComponent<GameGUI::Loading>();
    Noesis::RegisterComponent<GameGUI::GameView>();
    Noesis::RegisterComponent<GameGUI::PauseMenu>();
    Noesis::RegisterComponent<GameGUI::EndGame>();
    Noesis::RegisterComponent<GameGUI::LoadGame>();
    Noesis::RegisterComponent<Noesis::EnumConverter<GameGUI::State>>();

    NoesisApp::SetThemeProviders();
    Noesis::GUI::LoadApplicationResources("Theme/NoesisTheme.DarkAqua.xaml");

    NoesisApp::EmbeddedXaml xamls[] = {
            {"MainWindow.xaml", MainWindow_xaml},
            {"MainMenu.xaml", MainMenu_xaml},
            {"NewGame.xaml", NewGame_xaml},
            {"Loading.xaml", Loading_xaml},
            {"GameView.xaml", GameView_xaml},
            {"radar.xaml", radar_xaml},
            {"PauseMenu.xaml", PauseMenu_xaml},
            {"EndGame.xaml", EndGame_xaml},
            {"LoadGame.xaml", LoadGame_xaml}
    };

    NoesisApp::EmbeddedTexture textures[] = {
            "Level1.jpg", Level1_jpg,
            "radar.png", radar_png,
    };

    Noesis::GUI::SetXamlProvider(Noesis::MakePtr<NoesisApp::EmbeddedXamlProvider>(xamls));
    Noesis::GUI::SetTextureProvider(Noesis::MakePtr<NoesisApp::EmbeddedTextureProvider>(textures));

    Noesis::Ptr<Noesis::FrameworkElement> xaml = Noesis::GUI::LoadXaml<Noesis::FrameworkElement>("MainWindow.xaml");
    m_view = Noesis::GUI::CreateView(xaml).GiveOwnership();

    m_view->SetFlags(Noesis::RenderFlags_PPAA | Noesis::RenderFlags_LCD);
    m_view->GetRenderer()->Init(NoesisApp::GLFactory::CreateDevice(false));
}

void Gui::update(double time) const {
    m_view->Update(time / 1000.0);

    m_view->GetRenderer()->UpdateRenderTree();
    m_view->GetRenderer()->RenderOffscreen();
}

void Gui::render() const {
    m_view->GetRenderer()->Render();
}

void Gui::clear() const {
    GameGUI::MainWindow::view->Release();
    m_view->GetRenderer()->Shutdown();
    m_view->Release();
    Noesis::GUI::Shutdown();
}

void Gui::reshapeFunc(int width, int height) const {
    m_view->SetSize(width, height);
}

void Gui::mouseMoveFunc(int x, int y) const {
    m_view->MouseMove(x, y);
}

Noesis::Key Gui::getKeyCode(int code) {
    switch (code) {
        case GLFW_KEY_ESCAPE:
            return Noesis::Key_Escape; break;
        case GLFW_KEY_SPACE:
            return Noesis::Key_Space; break;
        default:
            return Noesis::Key_None; break;
    }
}
