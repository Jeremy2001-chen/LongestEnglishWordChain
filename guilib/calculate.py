import ctypes
import os



def calculate(fileName, start, end, problemType, loopEnable):
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

    call_func.restype = ctypes.c_char_p

    print(cmd)

    result = commandDLL.call_by_cmd(len(cmd), ctypes.c_char_p(cmd.encode('utf-8'))).decode('gbk')

    print(result)

    from output import outputSurface
    global surface
    surface = outputSurface()
    surface.show()

