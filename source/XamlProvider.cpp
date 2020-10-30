#include <NsCore/Ptr.h>
#include <NsCore/StringUtils.h>
#include <NsGui/Stream.h>

#include "XamlProvider.hpp"

XamlProvider::XamlProvider(const char *rootPath) {
    Noesis::StrCopy(&m_rootPath[0], m_rootPath.size(), rootPath);
}

Noesis::Ptr<Noesis::Stream> XamlProvider::LoadXaml(const char *filename) {
    char uri[512];

    if (Noesis::StrIsNullOrEmpty(&m_rootPath[0])) {
        Noesis::StrCopy(uri, sizeof(uri), filename);
    } else {
        Noesis::StrCopy(uri, sizeof(uri), &m_rootPath[0]);
        Noesis::StrAppend(uri, sizeof(uri), "/");
        Noesis::StrAppend(uri, sizeof(uri), filename);
    }

    return Noesis::OpenFileStream(uri);
}
