# Music Hall

Sample Application to show an Albums grid in C++/WinRT.

Please look at `DESIGN-NOTES.md` for notes on the technical design.

For work remaining, see `TODO.md`. This also contains work that has been
completed.

## Prerequisites

To be able to build & run this project, you'll need

- Windows 10 20H1 (Version 2004, Build 19041 or higher)
- Visual Studio 2019 (Version 16.7 or higher), with UWP, and C++ tools
- [C++/WinRT VS Extension v2.0 or
  higher](https://marketplace.visualstudio.com/items?itemName=CppWinRTTeam.cppwinrt101804264)

* [Windows SDK
  10.0.19041.0](https://marketplace.visualstudio.com/items?itemName=CppWinRTTeam.cppwinrt101804264)

## Building

Open `MusicHall.sln` from the root of this repo, select the target CPU flavour
for your device (e.g. x86 or amd64, most likely), and hit "Build"

## Usage
Simple navigation is as one would expect with the mouse.

However, by pressing "Ctrl" on your keyboard, you can see a debug menu allowing
navigation to a test page containing standard usages of the `AlbumControl`
making it easier to cover mutiple scenarios in one glance.

### Back Navigation
1. Button in the top left of the window
2. Mouse back button (if you have one)
3. OS Back Keyboard Shortcut (Win+Backspace)