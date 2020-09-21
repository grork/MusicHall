#include "pch.h"
#include "AlbumsPage.h"
#include "AlbumsPage.g.cpp"

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

        auto data = winrt::single_threaded_observable_vector<hstring>();
        for (int i = 0; i < 1000; i++)
        {
            data.Append(to_wstring(i));
        }

        co_await ui_thread;
        this->ItemsContainer().ItemsSource(data);
    }
}
