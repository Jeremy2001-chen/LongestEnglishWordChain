# coding=gbk

import ctypes
import os

from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *


def calculate(sur, fileName, start, end, problemType, loopEnable):
    print(os.getcwd())

    commandDLL = ctypes.windll.LoadLibrary("./control.dll")

    call_func = commandDLL.call_by_cmd

    call_func.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_char)]

    cmd = "Wordlist.exe"

    if start != "":
        cmd += " " + "-h " + start

    if end != "":
        cmd += " " + "-t " + end
        
    if loopEnable == "yes":
        cmd += " -r"

    cmd += " " + problemType + " " + fileName

    print(cmd)

    call_func.restype = ctypes.c_char_p


    result = commandDLL.call_by_cmd(len(cmd), ctypes.c_char_p(cmd.encode('utf-8'))).decode('gbk')

    print(result)

    if result == "":
        from output import outputSurface
        sur.close()
        global surface
        surface = outputSurface()
        surface.show()
    else:
        QMessageBox.information(sur, '警告', result)
        sur.close()
        from inputWord import inputWordSurface
        surface = inputWordSurface()
        surface.show()

