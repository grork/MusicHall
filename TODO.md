## General Todo
- [ ] Move `#includes` into the PCH for common winrt types

## Skeleton Project
- [x] Create sample Project (Name: `MusicHall`)
- [x] Update / Configure the manifest / Project info to look correct for that
  name
- [x] Add README.md with details on how to build & run
- [x] Add TODO.md with Todo list
- [x] Add DESIGN-NOTES.md for details on different design decisions
- [x] Push to Repo on GH

## App Skeleton
- [ ] Extended View into title bar
  - [ ] Create some sort of header for window-control area to look sensible
- [x] Add click handler to navigate to controls test page (using placeholder)
- [x] Add isolated controls test page
- [x] Add Secret button on ctrl being pressed to navigate to controls test page
- [x] Create Default control/main layout
- [x] Handle Navigation to placeholder Navigation Items/Pages
  - [x] Single page w/ passed in param for display
  - [x] Use Xaml's `TypeName` for navigation for decoupling
- [x] Add Secret Button Key handler for getting to a Special Test page
- [x] Add Empty Albums page with �Page left intentionally blank�
  page)
- [x] Create an Icon Tile Set based on a music note icon using built in
Asset generator
- [x] Add ItemsRepeater & Simple Text Template to Albums Page

## Loading Load Placeholder Data
- [x] Create Basic Album Data object that just exposes a Title, Artist, Release
  Year, Album URL (place kitten)
- [x] Generate Async on Startup, and Bind into Items Repeater

## Implement Album Control
- [x] Create Boilerplate Album Custom Control w/ Template, add to controls test page
- [ ] Create Wrapper control to support hover / keyboard focus
  - [ ] Keyboard Focus Visual State
  - [ ] Hover Visual State
  - [ ] Content Control Wrapper for arbitary child content
  - [ ] Add to Test Page
- [x] Create Basic Album Templated Control
    - [x] Album Name Property
    - [x] Artist Name Property
    - [x] Art URI Property
    - [x] Release Year
    - [x] Simple ugly template
- [x] Add Placeholder that can be used as generic background while loading
- [x] Add Album Tempalte & Basic layout to the Albums Page
- [ ] Extend Album control with Recycling from the ItemsRepeater to handle image
  loading / display of some text

## Application UI
- [ ] Add Navigation View
- [ ] Update the IsTitleBarAutoPaddingEnabled to false
- [ ] Create data class to be used for menu item data
- [ ] Add Basic Menu items for common navigational items in the UI
  - [ ] Navigate to the simple placeholder page created earlier on
- [ ] Update Keyboard Control Toggle to show the secret item while held using
  data source

## Nice-To-Have UI
- [ ] Allow grouping by Artist
- [ ] Allow grouping by A-Z
- [ ] Allow Sorting by Album Name
- [ ] Allow Sorting by Release Year
- [ ] Word Wheel search
- [ ] Consider: Restyling the `ScrollViewer` so that the scrollbar is inset to
  allow it to go under the navigation bar