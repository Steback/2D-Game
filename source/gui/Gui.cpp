#include <array>

#include "spdlog/spdlog.h"

#include "Gui.hpp"
#include "XamlProvider.hpp"
#include "FontProvider.hpp"

Gui::Gui() = default;

Gui::~Gui() {
    m_view->GetRenderer()->Shutdown();
    m_view->Release();
    Noesis::GUI::Shutdown();
}

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

    Noesis::GUI::SetXamlProvider(Noesis::MakePtr<XamlProvider>("data"));
    Noesis::GUI::SetFontProvider(Noesis::MakePtr<FontProvider>("data/theme"));

    const char* fonts[] = { "fonts/#PT Root UI", "Arial", "Segoe UI Emoji" };
    Noesis::GUI::SetFontFallbacks(fonts, 3);
    Noesis::GUI::SetFontDefaultProperties(15.0f, Noesis::FontWeight_Normal,
                                          Noesis::FontStretch_Normal,
                                          Noesis::FontStyle_Normal);

    Noesis::GUI::LoadApplicationResources("theme/NoesisTheme.DarkBlue.xaml");

    Noesis::Ptr<Noesis::FrameworkElement> xaml = Noesis::GUI::LoadXaml<Noesis::FrameworkElement>("basicView.xaml");

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

void Gui::reshapeFunc(int width, int height) const {
    m_view->SetSize(width, height);
}

void Gui::mouseMoveFunc(int x, int y) const {
    m_view->MouseMove(x, y);
}
