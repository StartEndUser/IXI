# T2S （Tab转空格）

[English Document](README.md)

将所有指定的文件的Tab转空格

版本: 0.0.0 （测试）
**由于本项目处于测试版本。如果有任何BUG请汇报。谢谢。**

**！！非常重要！！ 如果你的代码的字符串内含有任何Tab（或者别处也有但你不想要将其替换）请将Tab替换成`\t`。不要直接输入Tab！！**

## 下载
下载源代码 *（需要使用`git`）*
```
git https://github.com/StartEndUser/T2S.git
```

编译代码 *（需要使用`g++`）*

Windows:
```
g++ Main.cpp -o t2s.exe
```
Linux:
```
g++ Main.cpp -o t2s
```

**务必将`t2s`添加到`$PATH`否则你需要`t2s`放到你要操作的目录里**
## 使用
### 选择文件
*这是示范文件。你现在在`Example`文件夹里运行`t2s`*
```
Example
├── Binary
│   └── Example
├── Build
│   ├── BLABLABLA
│   └── CMAKE-STUF
├── CMakeLists.txt
└── Source
    ├── Feature1.cpp
    ├── Feature1.hpp
    ├── Feature2.cpp
    ├── Feature2.hpp
    └── Main.cpp
```
*（文件末尾有星号表示该文件选中）*

如果想选择单个文件：
```
t2s Source Source/Main.cpp
```
运行后：
```
Example
├── Binary
│   └── Example
├── Build
│   ├── BLABLABLA
│   └── CMAKE-STUF
├── CMakeLists.txt
└── Source
    ├── Feature1.cpp
    ├── Feature1.hpp
    ├── Feature2.cpp
    ├── Feature2.hpp
    └── Main.cpp *
```

也可以一次性选择多个文件：
```
t2s Source/Main.cpp Source/Feature1.cpp Source/Feature2.cpp
```
*（注意：如果你的文件以`-`开头。比如`-Minus`如果想要添加它，输入`@-Minus`如果想要删除它，输入`--Minus`）*

*（`@`在这里会将特殊意义（对于此程序）的符号转换成普通的字符）*

*（注意：如果你的文件包含`@`。比如`@@@///`如果想要添加它，输入`@@@@@@///`（每一个`@`对应一个`@@`）删除与添加类似，但前面要加上那个`-`）*

*（`@`和`\`是两码事。`\`是在bash里面的转义字符。`@`是在此程序的转义字符）*

运行后：
```
Example
├── Binary
│   └── Example
├── Build
│   ├── BLABLABLA
│   └── CMAKE-STUF
├── CMakeLists.txt
└── Source
    ├── Feature1.cpp *
    ├── Feature1.hpp
    ├── Feature2.cpp *
    ├── Feature2.hpp
    └── Main.cpp *
```

选择一个文件夹也是可行的:
```
t2s Source
```
运行后：
```
Example
├── Binary
│   └── Example
├── Build
│   ├── BLABLABLA
│   └── CMAKE-STUF
├── CMakeLists.txt
└── Source
    ├── Feature1.cpp *
    ├── Feature1.hpp *
    ├── Feature2.cpp *
    ├── Feature2.hpp *
    └── Main.cpp *
```

将一个`-`放在文件前就可以取消对其转换：

*（注意：顺序很重要。程序是从左到右读的）*

*（注意：如果取消了本来就不存在于操作列表的文件。程序不会报错。只会继续）*
```
t2s Source -Source/Main.cpp
```
After:
```
Example
├── Binary
│   └── Example
├── Build
│   ├── BLABLABLA
│   └── CMAKE-STUF
├── CMakeLists.txt
└── Source
    ├── Feature1.cpp *
    ├── Feature1.hpp *
    ├── Feature2.cpp *
    ├── Feature2.hpp *
    └── Main.cpp
```

*技巧：如果想要将当前文件夹下所有文件选中：*
```
t2s .
```

### 缩进
按下<kbd>Enter</kbd>键运行`t2s`。
程序会输出：
```
Indent length （default 4）:
```

按下<kbd>Enter</kbd>键将缩进长度设为默认的4。
或者先输入一个数字再按下<kbd>Enter</kbd>键。

## 计划
 - 添加一个文件操作进度。
 - 添加二进制文件警告（当发现文件可能是二进制文件）。
 - 添加*作为通配符。
 - 添加多线程支持。
 - 添加Windows, Macos, Linux......的可执行文件到Github Release。
 - 添加一个控制台界面。*（此功能可能会被添加到下面这个计划中）*
 - 更名此项目为**Code File Tools** 。*（并添加更多工具）*

**感谢使用**
