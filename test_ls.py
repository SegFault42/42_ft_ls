import sys
import os
import subprocess

os.system("rm -fr sandbox")
os.system("mkdir sandbox")

def reset_sandbox():
	os.system("rm -fr ../sandbox/*")

def test_myoutput1(capsys): # or use "capfd" for fd-level
	str1 = os.system("./ft_ls .")
	str2 = os.system("ls .")
	assert str1 == str2

ef test_myoutput2(capsys): # or use "capfd" for fd-level
	reset_sandbox()
	os.system("touch sandbox/aaa sandbox/bbb sandbox/ccc")
	str1 = os.system("./ft_ls -1")
	str2 = os.system("ls -1")
	assert str1 == str2

##################################### test: -r ################################
def test_minus_r_1(capsys): # or use "capfd" for fd-level
	reset_sandbox()
	os.system("touch sandbox/a sandbox/b sandbox/c sandbox/d sandbox/e sandbox/f sandbox/g sandbox/h sandbox/i sandbox/j sandbox/k sandbox/l sandbox/m sandbox/n sandbox/o sandbox/p sandbox/q sandbox/r sandbox/s sandbox/t sandbox/u sandbox/v sandbox/w sandbox/x sandbox/y sandbox/z")
	str1 = os.system("./ft_ls -1r")
	str2 = os.system("ls -1r")
	assert str1 == str2

def test_myoutput3(capsys): # or use "capfd" for fd-level
	str1 = os.system("./ft_ls -1")
	str2 = os.system("ls -1")
	assert str1 == str2

os.system("rm -fr sandbox")
