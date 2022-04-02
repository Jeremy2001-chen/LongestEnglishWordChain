# coding=gbk

from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from surface import Surface
import os

global surface



class inputWordSurface(Surface):
    nameSignal = pyqtSignal(str)

    def __init__(self):
        super().__init__()

        self.headLabel = QLabel("单词链计算")
        self.headLabel.setAlignment(Qt.AlignHCenter)
        self.headLabel.setStyleSheet("font-size:80px;"
                                     "font-weight:bold;"
                                     "font-family:Roman"
                                     "times;")
        self.headLabel.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.mainLayout.addWidget(self.headLabel, 0, 0, 9, 9)

        self.inputSurface = QWidget()
        self.inputSurfaceLayout = QGridLayout()
        self.inputSurface.setLayout(self.inputSurfaceLayout)
        self.mainLayout.addWidget(self.inputSurface, 1, 1, 8, 8)

        self.workLabel = QLabel("输入单词")
        self.workLabel.setStyleSheet("font-size:30px;"
                                     "font-family:Roman"
                                     "times;")

        self.workLabel.setAlignment(Qt.AlignLeft)
        self.inputSurfaceLayout.addWidget(self.workLabel, 0, 0, 1, 7)

        self.importBut = QPushButton("从文件中导入")
        self.inputSurfaceLayout.addWidget(self.importBut, 0, 5, 1, 1)

        self.wordInput = QPlainTextEdit();
        self.inputSurfaceLayout.addWidget(self.wordInput, 1, 0, 1, 6)

        self.buttonWeight = QWidget()
        self.buttonLayout = QGridLayout()
        self.buttonWeight.setLayout(self.buttonLayout)
        self.inputSurfaceLayout.addWidget(self.buttonWeight, 2, 0, 2, 5)
        self.setButton = QPushButton("确定")
        self.resetButton = QPushButton("重置")
        self.buttonBlank = QLabel("")
        self.buttonLayout.addWidget(self.buttonBlank, 0, 1, 1, 2)
        self.buttonLayout.addWidget(self.setButton, 0, 2, 1, 1)
        self.buttonLayout.addWidget(self.resetButton, 0, 3, 1, 1)


        self.resize(960, 720)
        self.setWindowTitle('单词链计算')

        self.resetButton.clicked.connect(self.reset_btn_clicked)
        self.importBut.clicked.connect(self.upload_btn_clicked)
        self.setButton.clicked.connect(self.set_btn_clicked)

        # self.initPos()
        # self.initEvent()
        
    def reset_btn_clicked(self):
        QMessageBox.information(self, '消息', "您已重置单词！")
        self.wordInput.clear()

    def upload_btn_clicked(self):
        fileName, filetype = QFileDialog.getOpenFileName(self, "选取文件", os.getcwd(), "All Files (*);;Text Files (*.txt)")
        try:
            with open(fileName, 'r') as f:
                text = ""
                line = f.readline()
                while line:
                    text += line
                    line = f.readline()
            self.wordInput.setPlainText(text)
        except Exception as e:
            print(e)
            QMessageBox.information(self, '警告', "上传文件异常！")
            return
        QMessageBox.information(self, '消息', "文件内容已导入到文本框中！")

    def set_btn_clicked(self):
        fileName = "tempFileName.txt"
        with open(fileName, 'w') as f:
            f.write(self.wordInput.toPlainText())
        QMessageBox.information(self, '消息', "文件内容已导入！")
        from inputParameter import inputParameterSurface
        global surface
        surface = inputParameterSurface()
        surface.show()
        self.close()