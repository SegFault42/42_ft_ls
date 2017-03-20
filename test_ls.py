import sys
import os
import subprocess

def test_myoutput1(capsys): # or use "capfd" for fd-level
     str1 = os.system("./ft_ls .")
     str2 = os.system("ls . ")
     assert str1 == str2

#def test_myoutput2(capsys): # or use "capfd" for fd-level
     #str1 = os.system("./ft_ls .")
     #str2 = os.system("ls .")
     #assert str1 == str2
