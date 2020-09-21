#pragma once

#include "AlbumsPage.g.h"

namespace winrt::Codevoid::MusicHall::implementation
{
    struct AlbumsPage : AlbumsPageT<AlbumsPage>
    {
        AlbumsPage();

    private:
        Windows::Foundation::IAsyncAction LoadDataAndDisplayAsync();
    };
}

namespace winrt::Codevoid::MusicHall::factory_implementation
{
    struct AlbumsPage : AlbumsPageT<AlbumsPage, implementation::AlbumsPage>
    {
    };
}
