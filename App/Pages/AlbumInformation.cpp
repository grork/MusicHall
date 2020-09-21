#include "pch.h"
#include "AlbumInformation.h"
#include "AlbumInformation.g.cpp"

namespace winrt::Codevoid::MusicHall::implementation
{
    hstring AlbumInformation::Title()
    {
        return m_title;
    }
    void AlbumInformation::Title(hstring const& value)
    {
        m_title = value;
    }
    hstring AlbumInformation::Artist()
    {
        return m_artist;
    }
    void AlbumInformation::Artist(hstring const& value)
    {
        m_artist = value;
    }
    int32_t AlbumInformation::Year()
    {
        return m_year;
    }
    void AlbumInformation::Year(int32_t value)
    {
        m_year = value;
    }
    Windows::Foundation::Uri AlbumInformation::CoverArt()
    {
        return m_coverArt;
    }
    void AlbumInformation::CoverArt(Windows::Foundation::Uri const& value)
    {
        m_coverArt = value;
    }
}
