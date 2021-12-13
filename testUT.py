import os
import sys

files = os.listdir("./")
for file in files:
    if file.endswith("TestSuite"):
        res = os.system("./" + file)
        if res == 0:
            print("-------------------------------------")
        else:
            break