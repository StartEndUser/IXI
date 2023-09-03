# Simple Fix

[中文文档](README-CHINESE.md)

- Change all tabs to spaces
- Delete useless spaces and tabs
- Leave specific numbers of lines

*(Spaces Are Shown As .)*

*(Tabs Are Shown As --->)*
```cpp
#include.<cstdio>.....       | (Useless Spaces)
....                         | (Useless Spaces)
int.main()
{--->--->                    | (Useless Tabs)
--->printf("Hello.World\n"); | (Using Tabs And Spaces Together)
....                         | (Useless Spaces)
....return.0;
}
--->                         | (Useless Tabs)
.                            | (Useless Spaces)
                             | (Too Much Lines At The Last)
```

Config:
Tab Length: 4
Delete Mode: A *(All)*
Leave Lines: 1

After:
```cpp
#include.<cstdio>

int.main()
{
....printf("Hello.World\n");

....return.0;
}
                             | (Leave One Line)
```

Version: 1.0.0

**If any bug found please report it. Thank you.**

**!!VERY IMPORTANT!! IF YOUR CODE CONTAINS ANY TABS INSIDE A STRING(OR OTHER PLACES THAT YOU DON'T WANT IT TO BE CHANGED) PLEASE REPLACS IT WITH `\t`. DON'T JUST TYPE A TAB INSIDE!!!**

## Install
Download the source code *(`git` is needed)*
```
git clone https://github.com/StartEndUser/SimpleFix.git
```

Enter SimpleFix Directory:
```
cd SimpleFix
```

Compile it *(`g++` is needed)*

Windows:
```
g++ Main.cpp -o sf.exe -O2
```
MacOS/Linux:
```
g++ Main.cpp -o sf -O2
```

**ADD `sf` TO `$PATH` OTHERWISE YOU WOULD NEED TO COPY `sf` TO THE FOLDER YOU'LL CHANGE**
## Instruction
### Select Files
*This is the example folder. Now you are running `sf` at the `Example` folder*
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
*(Files with a star at the back means it will be changed)*

If you want to change only one file:
```
sf Source Source/Main.cpp
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
    ├── Feature1.cpp
    ├── Feature1.hpp
    ├── Feature2.cpp
    ├── Feature2.hpp
    └── Main.cpp *
```

You can also change more at once:
```
sf Source/Main.cpp Source/Feature1.cpp Source/Feature2.cpp
```
*(Notice: if your directory or file STARTS with a `-` such as `-Minus` to add it from changing, input `@-Minus` and to delete it from changing, input `--Minus`)*

*(The `@` in here changes special meaning symbols(this program's) into normal character)*

*(Notice: if your directory or file CONTAINS a `@` such as `@@@///` to add it from changing, input `@@@@@@///`(Every `@` will be changed into `@@`) and add a `-` before it to delete it from changing)*

*(`@` is not `\`. `\` is used for your bash. `@` is used for this program)*

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
    ├── Feature1.hpp
    ├── Feature2.cpp *
    ├── Feature2.hpp
    └── Main.cpp *
```

Selecting a directory is also legal:
```
sf Source
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
    └── Main.cpp *
```

Put a `-` before a directory or a file can stop change it:

*(Notice: The order MATTERS. The program reads from left to right)*

*(Notice: There is no detection wether the directory or file was added. If not added. It will just skip)*
```
sf Source -Source/Main.cpp
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

*Tip: To Add All Files Under The Current Folder:*
```
sf .
```

### Tabs To Spaces
Press <kbd>Enter</kbd> to start `sf`.
The program will output:
```
Tab length (skip if nothing):
```

Press <kbd>Enter</kbd> to skip.

Or input a number to set the tab length and press <kbd>Enter</kbd>.

### Delete Useless Spaces And Tabs
Next the program will output:
```
S: Only Delete Useless Spaces
T: Only Delete Useless Tabs
A: Delete All Useless Spaces And Tabs
Delete mode (skip if nothing):
```

Press <kbd>Enter</kbd> to skip.

Or input a mode *(S/T/A, Capital)* and press <kbd>Enter</kbd>.

### Leave Specific Numbers Of Lines
Last the program will output:
```
Leave line number (skip if nothing):
```

Press <kbd>Enter</kbd> to skip.

Or input a number to set the leave line number and press <kbd>Enter</kbd>.

**THANKS FOR USING**
