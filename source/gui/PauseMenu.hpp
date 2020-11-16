#ifndef INC_2D_GAME_PAUSEMENU_HPP
#define INC_2D_GAME_PAUSEMENU_HPP


#include "NsCore/Noesis.h"
#include "NsGui/UserControl.h"


namespace GameGUI {
    class PauseMenu final : public Noesis::UserControl {
        public:
            PauseMenu();

        private:
            void InitializeComponent();

            NS_DECLARE_REFLECTION(PauseMenu, UserControl)
    };
}


#endif
