#ifndef EMBEDDEDXAMLPROVIDER_HPP
#define EMBEDDEDXAMLPROVIDER_HPP


#include "NsCore/Noesis.h"
#include "NsCore/Vector.h"
#include "NsCore/ArrayRef.h"
#include "NsCore/Ptr.h"
#include "NsApp/ProvidersApi.h"
#include "NsGui/XamlProvider.h"

struct EmbeddedXaml {
    const char* name{};
    Noesis::ArrayRef<uint8_t> data;
};

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

class EmbeddedXamlProvider : public Noesis::XamlProvider {
    public:
        explicit EmbeddedXamlProvider(Noesis::ArrayRef<EmbeddedXaml> xamls, XamlProvider* fallback = nullptr);

    private:
        Noesis::Ptr<Noesis::Stream> LoadXaml(const char* uri) override;

    private:
        Noesis::Vector<EmbeddedXaml> m_xamls;
        Noesis::Ptr<XamlProvider> mFallback;
};

NS_WARNING_POP


#endif