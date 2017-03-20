import sys
import os
import subprocess

os.system("mkdir sandbox")
os.system("cd sandbox")

#def reset_sandbox():
	#os.system("rm -fr *")

def test_myoutput1(capsys): # or use "capfd" for fd-level
     str1 = os.system("./ft_ls .")
     str2 = os.system("ls . ")
     assert str1 == str2

def test_myoutput2(capsys): # or use "capfd" for fd-level
	 os.system("touch aaa bbb ccc")
	 str1 = os.system("./ft_ls -1")
	 str2 = os.system("ls -1")
	 assert str1 == str2

#os.system("cd ..")
#os.system("rm -fr sandbox")
