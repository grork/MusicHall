## Skeleton Project

- [x] Create sample Project (Name: `MusicHall`)
- [x] Update / Configure the manifest / Project info to look correct for that name
- [x] Add README.md with details on how to build & run
- [x] Add TODO.md with Todo list
- [x] Add DESIGN-NOTES.md for details on different design decisions
- [x] Push to Repo on GH

## App Skeleton

- [ ] Create Default control/main layout
- [ ] Handle Navigation to placeholder Navigation Items/Pages
  - [ ] Single page w/ passed in param for display
  - [ ] Use Xaml's `TypeName` for navigation for decoupling
- [ ] Add Secret Button Key handler for getting to a Special Test page
- [ ] Extended View into title bar
  - [ ] Create some sort of header for window-control area to look sensible
- [ ] Add Empty Albums page with ’Page left intentionally blank’
- [ ] Add click handler to navigate to single Album page (using placeholder page)
- [ ] Add isolated test page for a single album control
- [ ] Add Secret button on ctrl being pressed to navigate to single item page
- [ ] Create simple Album Custom Control w/ Template, add to test page
- [ ] Create an Icon Tile Set based on a music note icon (Use https://marketplace.visualstudio.com/items?itemName=shenchauhan.UWPTileGenerator?)
  - [ ] If it fails/isn't good quality, use Sketch template 

## Loading Load Placeholder Data

- [ ] Define a simple JSON Format containing the information needed
- [ ] Create Basic Album Data object that just exposes a Title, Artist, Release Year, Album URL (place kitten)
- [ ] Load JSON on startup async

## Implement Album Control

- [ ] Create Wrapper control to support hover / keyboard focus
  - [ ] Keyboard Focus Visual State
  - [ ] Hover Visual State
    - [ ] On Demand Creation of hover state?
- [ ] Add Placeholder that can be used as generic background while loading
- [ ] Extend Album control with Recycling from the ItemsRepeater to handle image loading / display of some text

## Application UI

- [ ] Add Navigation View
- [ ] Update the IsTitleBarAutoPaddingEnabled to false
- [ ] Create data class to be used for menu item data
- [ ] Add Basic Menu items for common navigational items in the UI
  - [ ] Navigate to the simple placeholder page created earlier on
- [ ] Update Keyboard Control Toggle to show the secret item while held using data source

## Nice-To-Have UI

- [ ] Allow grouping by Artist
- [ ] Allow grouping by A-Z
- [ ] Allow Sorting by Album Name
- [ ] Allow Sorting by Release Year
- [ ] Word Wheel search
- [ ] Consider: Restyling the `ScrollViewer` so that the scrollbar is inset to allow it to go under the navigation bar