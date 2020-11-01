#ifndef GAME_GUI_HPP
#define GAME_GUI_HPP


#include "NsGui/FontProperties.h"
#include "NsGui/IntegrationAPI.h"
#include "NsGui/IRenderer.h"
#include "NsGui/IView.h"
#include "NsGui/Grid.h"
#include "NsApp/ThemeProviders.h"
#include "NsRender/GLFactory.h"

class Gui {
    public:
        Gui();
        ~Gui();
        void init();
        void update(double time) const;
        void render() const;
        void reshapeFunc(int width, int height) const;
        void mouseMoveFunc(int x, int y) const;

    public:
        Noesis::IView* m_view{};
};


#endif
