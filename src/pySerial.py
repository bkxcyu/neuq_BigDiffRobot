# -*- coding: utf-8 -*-
import serial
import time

serialPort = "/dev/ttyACM0"  # 串口
baudRate = 115200  # 波特率
ser = serial.Serial(serialPort, baudRate, timeout=0.5)
print("参数设置：串口=%s ，波特率=%d" % (serialPort, baudRate))


while 1:
    c=input('请输入指令:')
    ser.write(c.encode())#ser.write在于向串口中写入数据
    #data = ser.readline().decode()  # Wait for line from Arduino and read it
    #print("Received: '{}'".format(data))  # Print the line to the console
