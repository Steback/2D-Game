#include "NsApp/EmbeddedXamlProvider.h"
#include "NsCore/StringUtils.h"
#include "NsGui/MemoryStream.h"

#include "EmbeddedXamlProvider.hpp"

#include "App.xaml.bin.h"

EmbeddedXamlProvider::EmbeddedXamlProvider(Noesis::ArrayRef<EmbeddedXaml> xamls, Noesis::XamlProvider *fallback)
        : mFallback(fallback) {
    m_xamls.Assign(xamls.Begin(), xamls.End());
}

Noesis::Ptr<Noesis::Stream> EmbeddedXamlProvider::LoadXaml(const char *uri) {
    for (const auto& xaml: m_xamls) {
        if (Noesis::StrEquals(uri, xaml.name)) {
            return *new Noesis::MemoryStream(xaml.data.Data(), xaml.data.Size());
        }
    }

    return mFallback ? mFallback->LoadXaml(uri) : nullptr;
}
