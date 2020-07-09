# -*- coding: utf-8 -*-
import numpy as np
import os
import base64

RATE = 16000
WIN_LEN = 0.02
WIN_STEP = 0.01


def get_rate():
    print(RATE)


def get_size():
    print(WIN_LEN*WIN_STEP)


def DLC(pathName):
    get_rate()
    get_size()
    print("DLC")
