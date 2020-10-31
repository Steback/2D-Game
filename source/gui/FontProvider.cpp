#include "FontProvider.hpp"

#include <NsCore/Find.h>
#include <NsGui/Stream.h>

FontProvider::FontProvider(const char *rootPath) {
    Noesis::StrCopy(&m_rootPath[0], m_rootPath.size(), rootPath);
}

void FontProvider::ScanFolder(const char *folder) {
    char uri[512] = "";

    if (!Noesis::StrIsNullOrEmpty(&m_rootPath[0])) {
        Noesis::StrCopy(uri, sizeof(uri), &m_rootPath[0]);
        Noesis::StrAppend(uri, sizeof(uri), "/");
    }

    Noesis::StrAppend(uri, sizeof(uri), folder);

    ScanFolder(uri, folder, ".ttf");
    ScanFolder(uri, folder, ".otf");
    ScanFolder(uri, folder, ".ttc");
}

Noesis::Ptr<Noesis::Stream> FontProvider::OpenFont(const char *folder, const char *filename) const {
    char uri[512] = "";

    if (!Noesis::StrIsNullOrEmpty(&m_rootPath[0])) {
        Noesis::StrCopy(uri, sizeof(uri), &m_rootPath[0]);
        Noesis::StrAppend(uri, sizeof(uri), "/");
    }

    Noesis::StrAppend(uri, sizeof(uri), folder);
    Noesis::StrAppend(uri, sizeof(uri), "/");
    Noesis::StrAppend(uri, sizeof(uri), filename);

    return Noesis::OpenFileStream(uri);
}

void FontProvider::ScanFolder(const char *path, const char *folder, const char *ext) {
    Noesis::FindData findData{};

    if (FindFirst(path, ext, findData)) {
        do {
            RegisterFont(folder, findData.filename);
        } while (FindNext(findData));

        FindClose(findData);
    }
}
