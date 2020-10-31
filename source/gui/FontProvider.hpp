#ifndef FONTPROVIDER_HPP
#define FONTPROVIDER_HPP


#include <array>

#include <NsCore/Noesis.h>
#include <NsGui/CachedFontProvider.h>
#include <NsApp/ProvidersApi.h>

class FontProvider : public Noesis::CachedFontProvider {
    public:
        explicit FontProvider(const char* rootPath);

    private:
        void ScanFolder(const char* folder) override;

        Noesis::Ptr<Noesis::Stream> OpenFont(const char* folder, const char* filename) const override;

        void ScanFolder(const char* path, const char* folder, const char* ext);

    private:
        std::array<char, 512> m_rootPath{};
};


#endif