#include <array>

#include "spdlog/spdlog.h"
#include "NsCore/RegisterComponent.h"
#include "NsApp/EmbeddedXamlProvider.h"
#include "NsCore/EnumConverter.h"
#include "NsApp/Interaction.h"
#include "NsApp/DataTrigger.h"
#include "NsApp/TriggerCollection.h"
#include "NsApp/KeyTrigger.h"
#include "NsApp/InvokeCommandAction.h"
#include "NsApp/ControlStoryboardAction.h"
#include "NsApp/ChangePropertyAction.h"

#include "Gui.hpp"
#include "MainWindow.hpp"
#include "ViewModel.hpp"
#include "MainMenu.hpp"
#include "NewGame.hpp"
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

    Noesis::GUI::Init(NS_LICENSE_NAME, NS_LICENSE_KEY);

    Noesis::TypeOf<NoesisApp::Interaction>();

    Noesis::RegisterComponent<NoesisApp::DataTrigger>();
    Noesis::RegisterComponent<NoesisApp::TriggerCollection>();
    Noesis::RegisterComponent<NoesisApp::KeyTrigger>();
    Noesis::RegisterComponent<NoesisApp::InvokeCommandAction>();
    Noesis::RegisterComponent<NoesisApp::ControlStoryboardAction>();
    Noesis::RegisterComponent<NoesisApp::ChangePropertyAction>();

    Noesis::RegisterComponent<GameGUI::MainWindow>();
    Noesis::RegisterComponent<GameGUI::MainMenu>();
    Noesis::RegisterComponent<GameGUI::NewGame>();
    Noesis::RegisterComponent<Noesis::EnumConverter<GameGUI::State>>();

    NoesisApp::SetThemeProviders();
    Noesis::GUI::LoadApplicationResources("Theme/NoesisTheme.DarkBlue.xaml");

    NoesisApp::EmbeddedXaml xamls[] = {
            "MainWindow.xaml", MainWindow_xaml,
            "MainMenu.xaml", MainMenu_xaml,
            "NewGame.xaml", NewGame_xaml
    };

    Noesis::GUI::SetXamlProvider(Noesis::MakePtr<NoesisApp::EmbeddedXamlProvider>(xamls));

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
