#ifndef INC_2D_GAME_MAINMENU_HPP
#define INC_2D_GAME_MAINMENU_HPP


#include "NsCore/Noesis.h"
#include "NsGui/UserControl.h"


namespace GameGUI {
    class MainMenu : public Noesis::UserControl {
        public:
            MainMenu();

        private:
            void InitializeComponent();

        NS_DECLARE_REFLECTION(MainMenu, UserControl)
    };
}


#endif
