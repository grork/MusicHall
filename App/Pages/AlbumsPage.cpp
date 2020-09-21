#include "pch.h"
#include "AlbumsPage.h"
#include "AlbumsPage.g.cpp"
#include "AlbumInformation.h"

#include <chrono>

using namespace std;
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

namespace winrt::Codevoid::MusicHall::implementation
{
    AlbumsPage::AlbumsPage()
    {
        InitializeComponent();
        this->LoadDataAndDisplayAsync();
    }

    IAsyncAction AlbumsPage::LoadDataAndDisplayAsync()
    {
        apartment_context ui_thread;

        co_await winrt::resume_background();

        auto data = winrt::single_threaded_observable_vector<MusicHall::AlbumInformation>();
        for (int i = 0; i < 1000; i++)
        {
            auto item = make<AlbumInformation>();
            
            
            auto itemIndexAsString = to_wstring(i);
            item.Title(L"Album " + itemIndexAsString);
            item.Artist(L"Artist " + itemIndexAsString);
            
            // Skip every 11th image to show no-art scenario
            if ((i % 11) != 0)
            {
                Uri placeholder_image{ L"https://loremflickr.com/300/300?lock=" + itemIndexAsString };
                item.CoverArt(placeholder_image);
            }

            item.Year(i);
            data.Append(item);
        }

        co_await ui_thread;
        this->ItemsContainer().ItemsSource(data);
    }
}
