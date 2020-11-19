#ifndef INC_2D_GAME_ENDGAME_HPP
#define INC_2D_GAME_ENDGAME_HPP

#include "NsCore/Noesis.h"
#include "NsGui/UserControl.h"


namespace GameGUI {
    class EndGame final : public Noesis::UserControl {
        public:
            EndGame();

        private:
            void InitializeComponent();

            NS_DECLARE_REFLECTION(EndGame, UserControl)
    };
}


#endif
