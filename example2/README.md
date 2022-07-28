# 用例2

### 目标：静态库与头文件的生成与使用。

本用例有两个部分的需求：
1. 将src目录中的代码的编成静态库，库文件放在lib目录下，头文件放在include目录下。
2. test中的测试用例链接静态库并include头文件。


本例中共添加了三个CMakeLists，我们一个一个看

### example2/CMakeLists.txt
```
CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
PROJECT(learn-cmake)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)
``` 
此文件做了以下定义：
1. 限制了cmake的最小版本为3.9
2. 设置了项目名称为learn-cmake。
3. 使用ADD_SUBDIRECTORY导入子目录。

### example2/src/CMakeLists.txt
```
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/hello2 SRC_LIST)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

ADD_LIBRARY(hello STATIC ${SRC_LIST})

FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION ${PROJECT_SOURCE_DIR}/include
        FILES_MATCHING PATTERN "*.h"
        )
```
此文件做了以下定义：
1. 发现两个目录下的源码并保存到SRC_LIST变量中。
2. 生成静态库并指定生成路径。
3. 将头文件拷贝到指定目录中。

因为没有定义PROJECT，所以获取到的PROJECT_NAME以及PROJECT_SOURCE_DIR
得到的值是与上层CMakeList一致的。

AUX_SOURCE_DIRECTORY的作用是发现一个目录下的源代码并将列表储存到一个变量中。
CMAKE_CURRENT_SOURCE_DIR获取的是当前CMakeList所在的路径，此处值为example2/src/。

结合起来看AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)的意思是将example2/src/目录中的源码缓存到SRC_LIST变量中。

LIBRARY_OUTPUT_PATH变量的意思与example1中的EXECUTABLE_OUTPUT_PATH类似：设置库文件生成的路径。
因为最近的定义了PROJECT变量的CMakeList路径在example2/中，
所以SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)定义的库文件生成目的地路径为example2/lib。

ADD_LIBRARY的功能也与ADD_EXECUTABLE也类似，通过列表SRC_LIST中的源码生成名字为hello的静态库。

外部要调用我们生成的函数除了链接静态库外，还需要导入相应的头文件，所以我们需要将所需头文件拷贝到指定目录中方便被导入。
FILE命令目的是将指定目录下的所有文件拷贝到DESTINATION中，因为我们只需要.h头文件，
所以还要再添加一个FILES_MATCHING做文件匹配，只有.h文件才会执行拷贝操作。
注意在${CMAKE_CURRENT_SOURCE_DIR}的最后还有个/，表示拷贝的内容不包括本目录，此处${CMAKE_CURRENT_SOURCE_DIR}的值为example2/src，
如果没有最后的/，则拷贝到include中的结构为include/src/...，加上/后结构为include/...。FILE会根据所属目录中的文件结构来执行拷贝操作。
在src/hello2/里的文件拷贝后存放在include/hello2/中。


### example2/test/CMakeLists.txt
```
CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
PROJECT(test)

INCLUDE_DIRECTORIES(../include)
LINK_DIRECTORIES(../lib)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

ADD_EXECUTABLE(${PROJECT_NAME} test.cpp)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} hello)
```
此文件做了以下定义：
1. 限制了cmake的最小版本为3.9
2. 设置了项目名称为test。
3. 引入头文件搜索路径和添加共享库的搜索路径。
4. 生成可执行文件且设置生成路径。
5. 链接静态库。

本文件新定义了PROJECT变量，所以${PROJECT_NAME}和${PROJECT_SOURCE_DIR}都与上层的CMakeList中的值不一样。
PROJECT_NAME为test，PROJECT_SOURCE_DIR为example2/test。

运行test输出的结果为:
````
in function: Hello1. Hello foo
in function: Hello2. Hello bar
````