# mtt_rayTracer
一个path tracing render.做起来先，淦

Only tested in macOS 12.0.1.

## modules or lib used
- using googletest as UT module
- using eigen3 to do mathemtical calculating.

## How to compile
Please edit following line in CMakeLists.txt
```
# where you should include your eigen include path
include_directories(/opt/homebrew/include)
```
the path of eigen header file should be provided.

To compile, please run
```
mkdir build
cd build
cmake ..
make
```

## How to run UT
Entering the build directory, run
```
python3 ../testUT.py
```

## Some note
you may find there are codes like 
```
#if __INTELLISENSE__
#undef __ARM_NEON
#undef __ARM_NEON__
#endif
```
it is to fix some vscode bug in my environment. Please refer to https://github.com/microsoft/vscode-cpptools/issues/7413
