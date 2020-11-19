#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP


#include "NsCore/Noesis.h"
#include "NsApp/Window.h"

#include "ViewModel.hpp"


namespace GameGUI {

    class MainWindow final : public NoesisApp::Window {
        public:
            MainWindow();

        public:
            static Noesis::Ptr<ViewModel> view;

        private:
            void InitializeComponent();
            void OnLoaded(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&);

        private:
            NS_DECLARE_REFLECTION(MainWindow, Window)
    };

}


#endif