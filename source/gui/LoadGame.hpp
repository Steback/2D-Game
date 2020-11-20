#ifndef INC_2D_GAME_LOADGAME_HPP
#define INC_2D_GAME_LOADGAME_HPP


#include "NsCore/Noesis.h"
#include "NsGui/UserControl.h"


namespace GameGUI {
    class LoadGame final : public Noesis::UserControl{
        public:
            LoadGame();

        private:
            void InitializeComponent();

            NS_DECLARE_REFLECTION(LoadGame, UserControl)
    };
}


#endif
