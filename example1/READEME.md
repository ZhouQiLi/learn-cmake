# 用例1

### 目标：生成一个可执行文件到指定目录。

EXECUTABLE_OUTPUT_PATH变量定义了执行文件将安装的路径。

PROJECT_SOURCE_DIR变量返回的是项目的根目录。

本例中SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)的作用是将可执行文件安装到example1/bin目录下。

如果将PROJECT_SOURCE_DIR换成PROJECT_BINARY_DIR会有啥变化呢？

答案是得看是包外执行还是包内执行。如果cmake命令在工程根目录执行是包内，否则是包外。

以下是包外执行的用例：
````
mkdir build
cd build
cmake ..
````
以下是包内执行
````
cmake .
````

PROJECT_SOURCE_DIR会指向工程的根目录，也就是定义了PROJECT变量的CMakeLists.txt所在目录。而PROJECT_BINARY_DIR会指向执行cmake命令时的路径。

所以本例中如果是包内执行cmake，则PROJECT_SOURCE_DIR与PROJECT_BINARY_DIR的路径是一样的，都在example1/bin中。

若是新建了build目录并在build中包外执行cmake，则PROJECT_SOURCE_DIR的路径为example1/bin, PROJECT_BINARY_DIR的路径为example1/build/bin。

