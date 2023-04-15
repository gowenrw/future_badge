# future_badge

Future Badge Artifacts

This is a DEFCON Indie badge created for DC31.

This is where all the files for the Future Badge will be stored.

This includes code and art and cad and fab files.  All the things.

## File Structure

This is the file structure of this repository

* [/](/README.md) - YOU ARE HERE
* [/art/](./art/) - Artwork and other graphics created by this project
  * /art/inspiration/ - Art and graphics pulled from other sources used as inspiration for this project
* [/code/](./code/) - All project related Code / Firmware
  * /code/corsage/ - Code for the Raspberry Pi Pico on the corsage PCB
  * /code/firmware/ - CircuitPython firmware used by this project
* [/docs/](./docs/) - Documentation created by this project including web pages
* [/eda/](./eda/) - Electronic Design Automation files (i.e. KiCad)
  * /eda/hom3c0ming_boutonniere/ - KiCad project folder for the boutonniere PCB
  * /eda/hom3c0ming_corsage/ - KiCad project folder for the corsage PCB
* [/reference_parts/](./reference_parts/) - Documentation pulled from other sources related to components
* [./README.md](/README.md) - This File
* [./LICENSE](/LICENSE) - Currently set to MIT

Note: the reference_parts directory is a link to a submodule repository.
To add it use the following cmd after cloning this:
```
git submodule add https://github.com/gowenrw/reference_parts reference_parts
```
This will make a link to the current commit of that repo.
To update it to a newer commit after its been added use this cmd:
```
git submodule update --recursive
```
