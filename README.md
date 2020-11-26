# RayTracer
Ray tracing implemented in c++

# Building project
- Create output directory for the build
```
mkdir out
```
- Change directory to newly created directory
```
cd out
``` 
- Generate `Makefile` using `Cmake`, replace `[Release|Debug]` with either `Release` or `Debug`
```
cmake -DCMAKE_BUILD_TYPE=[Release|Debug] ..
```
- Build project using `make`
```
make
```