#ifndef GAME_XAMLPROVIDER_HPP
#define GAME_XAMLPROVIDER_HPP


#include <array>

#include "NsCore/Noesis.h"
#include "NsApp/ProvidersApi.h"
#include "NsGui/XamlProvider.h"

class XamlProvider : public Noesis::XamlProvider {
    public:
        XamlProvider(const char* rootPath);

    private:
        Noesis::Ptr<Noesis::Stream> LoadXaml(const char* filename) override;

    private:
        std::array<char, 512> m_rootPath;
};


#endif
