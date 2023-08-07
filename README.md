# T2S (Tab To Space)

[中文文档](README-CHINESE.md)

Change all tabs to spaces under the specific files.

Version: 0.0.1 (TEST)

**Since this project is in TEST. If any bug found please report it. Thank you.**

**!!VERY IMPORTANT!! IF YOUR CODE CONTAINS ANY TABS INSIDE A STRING(OR OTHER PLACES THAT YOU DON'T WANT IT TO BE CHANGED) PLEASE REPLACS IT WITH `\t`. DON'T JUST TYPE A TAB INSIDE!!!**

## Install
Download the source code *(`git` is needed)*
```
git clone https://github.com/StartEndUser/T2S.git
```

Enter T2S Directory:
```
cd T2S
```

Compile it *(`g++` is needed)*

Windows:
```
g++ Main.cpp -o t2s.exe
```
Linux:
```
g++ Main.cpp -o t2s
```

**ADD `t2s` TO `$PATH` OTHERWISE YOU WOULD NEED TO COPY `t2s` TO THE FOLDER YOU'LL CHANGE**
## Instruction
### Select Files
*This is the example folder. Now you are running `t2s` at the `Example` folder*
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
t2s Source Source/Main.cpp
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
t2s Source/Main.cpp Source/Feature1.cpp Source/Feature2.cpp
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
t2s Source
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

*Tip: To Add All Files Under The Current Folder:*
```
t2s .
```

### Indent
Press <kbd>Enter</kbd> to start `t2s`.
The program will output:
```
Indent length (default 4):
```

Press <kbd>Enter</kbd> to set as default 4.
Or input a number and press <kbd>Enter</kbd>.

## TODO
 - add a file changing progress.
 - add binary file warning (When a file may be a binary file).
 - add * as wildcard.
 - add multi-thread support.
 - add a github release for Windows, Macos, Linux...
 - add a CLI. *(This might be added in the plan below)*
 - Rename the project to **Code File Tools** .  *(With new features)*

**THANKS FOR USING**
