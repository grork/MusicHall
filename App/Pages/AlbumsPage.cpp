#include "pch.h"
#include "..\Controls\AlbumControl.h"
#include "AlbumsPage.h"
#include "AlbumsPage.g.cpp"
#include "AlbumInformation.h"

using namespace winrt::Microsoft::UI::Xaml::Controls;
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
        for (int idx = 0; idx < 1000; idx += 1)
        {
            auto itemIndexAsString = to_wstring(idx);
            auto item = make<AlbumInformation>();
            item.Title(L"Album " + itemIndexAsString);
            item.Artist(L"Artist " + itemIndexAsString);
            
            // Skip every 11th image to show no-art scenario
            if (((idx % 11) != 0) || idx == 0)
            {
                Uri placeholder_image{ L"https://loremflickr.com/300/300/cat?lock=" + itemIndexAsString };
                item.CoverArt(placeholder_image);
            }

            item.Year(idx);
            data.Append(item);
        }

        co_await ui_thread;
        this->ItemsContainer().ItemsSource(data);
    }

    void AlbumsPage::HandleElementClearing(ItemsRepeater const& /*sender*/, ItemsRepeaterElementClearingEventArgs const& args)
    {
        auto projection_albumControl = args.Element().try_as<MusicHall::AlbumControl>();
        if (projection_albumControl == nullptr)
        {
            // This wasn't the droid we were looking for
            return;
        }

        implementation::AlbumControl* albumControl = get_self<implementation::AlbumControl>(projection_albumControl);
        albumControl->ConfigureItemForRecycling();
    }
}
