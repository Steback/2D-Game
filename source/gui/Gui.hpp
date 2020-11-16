#ifndef GAME_GUI_HPP
#define GAME_GUI_HPP


#include "NsGui/FontProperties.h"
#include "NsGui/IntegrationAPI.h"
#include "NsGui/IRenderer.h"
#include "NsGui/IView.h"
#include "NsGui/Grid.h"
#include "NsApp/ThemeProviders.h"
#include "NsRender/GLFactory.h"
#include "NsGui/Button.h"


class Gui {
    public:
        Gui();
        ~Gui();
        void init();
        void update(double time) const;
        void render() const;
        void clear() const;
        void reshapeFunc(int width, int height) const;
        void mouseMoveFunc(int x, int y) const;
        static Noesis::Key getKeyCode(int code);

    public:
        Noesis::IView* m_view{};
        Noesis::Ptr<Noesis::FrameworkElement> m_xaml;
};


#endif
