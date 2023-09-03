# IXI
F*IX I*T

[English Document](README.md)

- Tab转空格
- 删除无用的空格和Tab
- 在行末仅留下指定行数

*（空格显示为 .）*

*（Tab显示为 --->）*
```cpp
#include.<cstdio>.....       | （无用空格)
....                         | （无用空格）
int.main()
{--->--->                    | （无用Tab）
--->printf("Hello.World\n"); | （把Tab和空格混在一起)）
....                         | （无用空格）
....return.0;
}
--->                         | （无用Tab）
.                            | （无用空格）
                             | （太多行末换行）
```

配置：

Tab长度：4

删除模式：A *（所有）*

末行数：1

运行后：
```cpp
#include.<cstdio>

int.main()
{
....printf("Hello.World\n");

....return.0;
}
                             | （只留一行）
```

版本: 1.0.0

**如果有任何BUG请汇报。谢谢。**

**！！非常重要！！ 如果你的代码的字符串内含有任何Tab（或者别处也有但你不想要将其替换）请将Tab替换成`\t`。不要直接输入Tab！！**

## 下载
下载源代码 *（需要使用`git`）*
```
git clone https://github.com/StartEndUser/IXI.git
```

进入IXI目录中：
```
cd IXI
```

编译代码 *（需要使用`g++`）*

Windows:
```
g++ Main.cpp -o ixi.exe -O2
```
MacOS/Linux:
```
g++ Main.cpp -o ixi -O2
```

**务必将`ixi`添加到`$PATH`否则你需要`ixi`放到你要操作的目录里**
## 使用
### 选择文件
*这是示范文件。你现在在`Example`文件夹里运行`ixi`*
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
ixi Source Source/Main.cpp
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
ixi Source/Main.cpp Source/Feature1.cpp Source/Feature2.cpp
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
ixi Source
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
ixi Source -Source/Main.cpp
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
ixi .
```

### Tab转空格
按下<kbd>Enter</kbd>键运行`ixi`。
程序会输出：
```
Tab length (skip if nothing):
```

按下<kbd>Enter</kbd>来跳过。

或者先输入一个数字设置Tab长度再按下<kbd>Enter</kbd>键。

### 删除无用的空格和Tab
接下来程序会输出：
```
S: Only Delete Useless Spaces
T: Only Delete Useless Tabs
A: Delete All Useless Spaces And Tabs
Delete mode (skip if nothing):
```

按下<kbd>Enter</kbd>来跳过。

或者先输入一个模式*（S/T/A，大写）*再按下<kbd>Enter</kbd>键。

```
S：仅删除无用空格
T：仅删除无用Tab
A：无用空格和Tab都删除
```

### 在行末仅留下指定行数
最后程序会输出：
```
Leave line number (skip if nothing):
```

按下<kbd>Enter</kbd>来跳过。

或者先输入一个数字设置末行留几行再按下<kbd>Enter</kbd>键。

**感谢使用**
