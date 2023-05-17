# XeLab Monte Carlo Simulation

GEANT4-based physics simulation of the XeLab experiment at LPNHE (Paris, France).

## Versions

- CMake 3.26.3
- ROOT 6.26/10 (only if you want to open `*.root` files generated during simulation)
- GEANT4 10.7.4
- (Python 3.8.15—not used at the moment)

## How to build and run?

To build the project, do the following:

```
cd xelab-mc
mkdir build && cd build
cmake ..
make -j16
```

To run the simulation program, type `./xelab_mc`.
