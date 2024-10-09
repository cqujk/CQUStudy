Building and running the [simple compress](/example/simple_compress.cpp) example:

```sh
cmake -DALP_BUILD_EXAMPLE=ON .   # or set option in the CMakeLists.txt
cd example
make
./simple_compress
```

cmake -DALP_BUILD_EXAMPLE=ON .
告诉CMake配置你的项目，并且通过一个`-D`选项设置了一个变量`ALP_BUILD_EXAMPLE`为`ON`