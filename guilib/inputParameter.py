# coding=gbk

from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from inputWord import inputWordSurface
from surface import Surface
import os

global surface



class inputParameterSurface(Surface):
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

        self.workLabel = QLabel("参数选择")
        self.workLabel.setStyleSheet("font-size:30px;"
                                     "font-family:Roman"
                                     "times;")

        self.workLabel.setAlignment(Qt.AlignLeft)
        self.inputSurfaceLayout.addWidget(self.workLabel, 0, 0, 1, 7)

        self.typeBox = QGroupBox("请选择问题参数")
        self.typeLayout = QVBoxLayout()
        self.typeBox.setLayout(self.typeLayout)
        self.inputSurfaceLayout.addWidget(self.typeBox, 1, 0, 1, 5)
        
        self.checkBox = []
        self.checkBox.append(QRadioButton("-n: 求单词文本能构成的单词链数量"))
        self.checkBox.append(QRadioButton("-w: 求单词数量最多的单词链"))
        self.checkBox.append(QRadioButton("-m: 求首字不能相同的最多的单词链"))
        self.checkBox.append(QRadioButton("-c: 求字母数量最多的单词链"))

        for i in range(0, 4):
            self.typeLayout.addWidget(self.checkBox[i])

        
        self.otherBox = QGroupBox("请选择其他参数")
        self.otherLayout = QVBoxLayout()
        self.otherBox.setLayout(self.otherLayout)

        self.startWeight = QWidget()
        self.startLayout = QGridLayout()
        self.startWeight.setLayout(self.startLayout)

        self.startLabel = QLabel("-h: 起始字母设定")
        self.startCharBox = QComboBox()
        
        self.startCharBox.addItem('不设定')
        for ch in range(ord('a'), ord('z')):
            self.startCharBox.addItem(chr(ch))

        self.startLayout.addWidget(self.startLabel, 1, 0, 1, 1)
        self.startLayout.addWidget(self.startCharBox, 1, 1, 1, 1)

        self.endWeight = QWidget()
        self.endLayout = QGridLayout()
        self.endWeight.setLayout(self.endLayout)

        self.endLabel = QLabel("-t: 终止字母设定")

        self.endCharBox = QComboBox()
        self.endCharBox.addItem('不设定')
        for ch in range(ord('a'), ord('z')):
            self.endCharBox.addItem(chr(ch))
            
        self.endLayout.addWidget(self.endLabel, 1, 0, 1, 1)
        self.endLayout.addWidget(self.endCharBox, 1, 1, 1, 1)

        self.loopWeight = QWidget()
        self.loopLayout = QGridLayout()
        self.loopWeight.setLayout(self.loopLayout)

        self.loopLabel = QLabel("-r: 是否允许自环")

        self.loopBox = QComboBox()
        self.loopBox.addItems(["不允许", "允许"])
        
        self.loopLayout.addWidget(self.loopLabel, 1, 0, 1, 1)
        self.loopLayout.addWidget(self.loopBox, 1, 1, 1, 1)

        self.otherLayout.addWidget(self.startWeight)
        self.otherLayout.addWidget(self.endWeight)
        self.otherLayout.addWidget(self.loopWeight)
        self.inputSurfaceLayout.addWidget(self.otherBox, 2, 0, 1, 5)

        #self.wordInput = QPlainTextEdit();
        #self.inputSurfaceLayout.addWidget(self.wordInput, 1, 0, 1, 6)

        self.buttonWeight = QWidget()
        self.buttonLayout = QGridLayout()
        self.buttonWeight.setLayout(self.buttonLayout)
        self.inputSurfaceLayout.addWidget(self.buttonWeight, 3, 0, 2, 5)
        self.setButton = QPushButton("确定")
        self.backButton = QPushButton("返回")
        self.buttonBlank = QLabel("")
        self.buttonLayout.addWidget(self.buttonBlank, 0, 1, 1, 2)
        self.buttonLayout.addWidget(self.setButton, 0, 2, 1, 1)
        self.buttonLayout.addWidget(self.backButton, 0, 3, 1, 1)


        self.resize(960, 720)
        self.setWindowTitle('单词链计算')


        self.backButton.clicked.connect(self.back_btn_clicked)
        self.setButton.clicked.connect(self.set_btn_clicked)
        # self.initPos()
        # self.initEvent()
        
    def back_btn_clicked(self):
        QMessageBox.information(self, '消息', "您已返回初始页面！")
        from inputWord import inputWordSurface
        global surface
        surface = inputWordSurface()
        self.close()
        surface.show()

    def set_btn_clicked(self):
        checkPara = ['-n', '-w', '-m', '-c']
        problemType = ""
        for i in range(0, 4):
            if self.checkBox[i].isChecked():
                problemType = checkPara[i]
        if problemType == "":
            QMessageBox.information(self, '警告', "未选择题目类型！")
            return

        QMessageBox.information(self, '消息', "您已成功提交参数！")

        start = self.startCharBox.currentText()
        if len(start) > 1:
           start = ""
        
        end = self.endCharBox.currentText()
        if len(end) > 1:
            end = ""

        loop = self.loopBox.currentText()
        if loop == "允许":
            loop = "yes"
        else:
            loop = "no"

        fileName = "tempFileName.txt"

        print("###############当前参数情况类型")
        print(start)
        print(end)
        print(loop)
        print(problemType)
        print(fileName)

        from calculate import calculate
        calculate(self, fileName, start, end, problemType, loop)
