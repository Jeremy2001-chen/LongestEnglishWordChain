# 结对编程项目说明

## 模块介绍

bin：可执行文件Wordlist.exe和所有依赖的动态链接库

src：所有项目的源代码，包括控制模块control、计算模块core、单词读取模块getwords、输出模块output和可执行项目Wordlist

test：所有单元测试代码和数据

guilib：GUI界面的所有代码

## 图形化界面介绍

### 环境

采用 Python 的 PyQt5 进行的图形化界面构建。

如果本地不存在环境，请使用 pip3 安装：

```shell
pip3 install sip
pip3 install PyQt5
```

### 使用

使用时请将 bin 目录下面的所有 **dll** 文件和 guilib 目录下的所有 python 文件放在一块，执行命令：

```python
python3 guilib.py
```

### 界面

界面总共包含三个界面，分别是单词读入界面、参数输入界面和输出界面。

单词读入可以通过向文本框输入或者导入文件的方式读入。

参数输入界面则会通过点击方式选择参数。

当单词和参数选择确认完毕后，系统会计算获得参数和单词的选择是否合法（如果不合法则会进行相应的提示，并返回到单词输入界面），若合法则会得到结果并跳转到输出界面。

在输出界面用户可以用文本框导出或者文件导出的方式对答案进行导出。

### 注意

在计算过程中会产生文件 solution.txt error.log tempFileName.txt 做为中间结果。
