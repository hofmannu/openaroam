# openaroam

## Installation
These libraries are required for the software to run on your PC:

*  `hdf5` general purpose library and file format for storing scientific data
*  `cmake` and `make`
*  `glfw-x11`, glew used to display stuff
*  `nlohmann-json` save settings of simulation to json file

To compile the software on your PC run the following lines of code
```
git clone git@github.com:hofmannu/openaroam.git
cd openaroam
git submodule init
git submodule update
mkdir Debug
cd Debug
cmake .. && make all
```

To run, simply run `./openaroam` from your terminal.

## Data storage
The software will not keep the whole scan in the RAM to avoid memory issues. Instead only the averaged version of the last B scan will be kept and the full raw data will be stored onto the disc during imaging. The amount of memory required on the disc will be checked prior scanning.

There is a default path which will be used to store the `h5` datafiles under: `~/ScanData` where `~` represents your user folder. Path handling is automatically done for you and each file will be saved in a subfolder for the date in combination with a unique identifier for each scan. In each dat directory is a file called `.counter` which stores the last given ID. Do not delete it.

Please also make sure that the drive you use for data storage is fast (in best case a SSD) so that it does not substantially slow down the scan process.
