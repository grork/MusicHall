#pragma once
#include "App.xaml.g.h"
#include "Controls\AlbumControl.h"

namespace winrt::Codevoid::MusicHall::implementation
{
    struct App : AppT<App>
    {
        App();
        void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const&);

    private:
        /// <summary>
        /// Performs any background initialization if it has not already been
        /// performed. This is to ensure that the background initialization can
        /// be called in prelaunch &amp; launch scenarios consistently.
        /// </summary>
        void BeginBackgroundInitializationIfNeeded();

        /// <summary>
        /// Handle arguments from launch, and perform any required UI instantiation
        /// and initialization.
        /// </summary>
        /// <param name="window">Window that we are placing this launch into</param>
        /// <param name="arguments">Any arguments passed by the operatin system</param>
        void HandleLaunchArguments(Windows::UI::Xaml::Window const& frame, winrt::hstring const& arguments);
    };
}
