#include "pch.h"
#include "App.h"
#include "MainUI.h"

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Codevoid::MusicHall;
using namespace Codevoid::MusicHall::implementation;

#pragma region Boilerplate App Code
App::App()
{
    InitializeComponent();

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
    UnhandledException([this](IInspectable const&, UnhandledExceptionEventArgs const& e)
    {
        if (IsDebuggerPresent())
        {
            auto errorMessage = e.Message();
            __debugbreak();
        }
    });
#endif
}

void App::OnLaunched(LaunchActivatedEventArgs const& e)
{
    // Make sure that basic, minimal work has been initiated if needed. This
    // can happen when launched, or prelaunched, so just fire-and-forget
    this->BeginBackgroundInitializationIfNeeded();

    // When prelaunched, we don't want do to the expensive work of navigating
    // to anything, or do other expensive work, so exit early
    if (e.PrelaunchActivated() == true)
    {
        return;
    }
    
    this->HandleLaunchArguments(Window::Current(), e.Arguments());

    // No matter what, we need to activate the window
    Window::Current().Activate();
}
#pragma endregion

void App::BeginBackgroundInitializationIfNeeded()
{
    // TODO: Begin Initialization if it hasn't already been started
}

void App::HandleLaunchArguments(Window const& window, hstring const& /*arguments*/)
{
    MusicHall::MainUI mainUI = window.Content().try_as<MusicHall::MainUI>();

    // Theres no content in the Window, so we need to create our UI
    if (window.Content() == nullptr)
    {
        mainUI = winrt::make<MainUI>();
        window.Content(mainUI);

        // Since this is the default navigation (We just created the UI)
        // perform a default navigation
        Interop::TypeName pageType;
        pageType.Name = L"Codevoid.MusicHall.PlaceholderPage";
        pageType.Kind = Interop::TypeKind::Primitive;

        mainUI.Navigate(pageType, box_value(L"First Page Placeholder"));
    }

    // TODO: Handle other activation / launch argument behaviours
}