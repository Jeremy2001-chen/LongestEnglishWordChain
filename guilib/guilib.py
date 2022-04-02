import sys
from PyQt5.QtWidgets import QApplication

app = QApplication(sys.argv)

from inputWord import inputWordSurface

if __name__ == '__main__':
    ex = inputWordSurface()
    ex.show()
    app.exec_()
