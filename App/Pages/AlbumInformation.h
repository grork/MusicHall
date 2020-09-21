#pragma once
#include "AlbumInformation.g.h"

namespace winrt::Codevoid::MusicHall::implementation
{
    struct AlbumInformation : AlbumInformationT<AlbumInformation>
    {
        AlbumInformation() = default;

        hstring Title();
        void Title(hstring const& value);
        hstring Artist();
        void Artist(hstring const& value);
        int32_t Year();
        void Year(int32_t value);
        Windows::Foundation::Uri CoverArt();
        void CoverArt(Windows::Foundation::Uri const& value);

    private:
        winrt::hstring m_title;
        winrt::hstring m_artist;
        int32_t m_year;
        Windows::Foundation::Uri m_coverArt{ nullptr };
    };
}
namespace winrt::Codevoid::MusicHall::factory_implementation
{
    struct AlbumInformation : AlbumInformationT<AlbumInformation, implementation::AlbumInformation>
    {
    };
}
