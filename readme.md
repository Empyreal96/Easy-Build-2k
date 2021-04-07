# Easy-Build Environment for Windows 2000 (NT 5)

<img src="C:\2k_diff\menu.png" alt="menu" />



## Current Features

FIRST REVISION

- Free and Checked Builds
- Razzle

### NOTES:

- **This is VERY EARLY STAGES, NOT EVERYTHING WORKS YET**
- Missing headers were taken from Windows 2000 DDK and Plat SDK, some things may need to be taken from NT 4 base.
- Currently Issues with CL.exe and some files.
- Currently Issues with cvtres unable to read `obj{d}\i386\*.tmp`.
- Razzle and Easy-Build were ported from the Xbox Tree so there may be a few issues there.
- Updates to this will NOT be frequent, this is a pet project to originally see if Easy-Build can be made 'portable'

# Setting up the tree:

- You will need to download the `Windows_2000_Source_Code.7z` that can be found on [archive.org](https://archive.org/download/wnt-src).

- Extract `private\` and `public\` folders from the .7z, and place inside a folder called `NT\` at the **ROOT** of a drive, e.g: `W:\NT\public` and `W:\NT\private`

- Clone this repo, and place `NT\` and `2k_razzle.cmd` in the **ROOT** of a drive e.g: `W:\NT\` `W:\2k_Razzle.cmd`. (OVERWRITE ANY FILES IF ASKED)

- Launch `2k_Razzle.cmd` and follow on-screen instructions.

  