# Electronic Design Automation

This is where all the Electronic Design Automation files for the PCB(s) will be stored.
The EDA used is KiCad 6.x unless otherwise specified.

## File Structure

This is the file structure of this repository

* [/](/README.md) - Home
* [/eda](/eda/) - YOU ARE HERE
  * /eda/<eda_project>/ - KiCad project folder for the named project PCB(s)
    * ./3d_models/ - This directory contains footprint 3d model files
    * ./gerber/ - This directory contains gerber formatted files for manufacturing
    * ./lib_fp/ - This directory contains footprint module directories
    * ./lib_sh/ - This directory contains schematic library files
    * ./snapshots/ - This directory contains prints of schematic / cad files and images of preview / final product
