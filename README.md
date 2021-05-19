# openaroam

## Installation
These libraries are required for the software to run on your PC:

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
The software will not keep the whole scan in the RAM to avoid memory issues. Instead only the averaged version of the last B scan will be kept and the full raw data will be stored onto the disc during imaging.

There is a default path which will be used to store the `h5` datafiles under: `~/ScanData` where `~` represents your user folder. Please create this folder before trying to perform the scan.