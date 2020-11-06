#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP


#include "NsCore/Noesis.h"
#include "NsApp/Window.h"


namespace GameGUI {

    class MainWindow final : public NoesisApp::Window {
        public:
            MainWindow();

        private:
            void InitializeComponent();
            void OnLoaded(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&);

        private:
            NS_DECLARE_REFLECTION(MainWindow, Window)
    };

}


#endif