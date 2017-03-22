import sys
import os
import subprocess

os.system("rm -fr sandbox")
os.system("mkdir sandbox")

def reset_sandbox():
	os.system("rm -fr ../sandbox/*")

def test_myoutput1(capsys): # or use "capfd" for fd-level
	str1 = os.system("./ft_ls -1 .")
	str2 = os.system("ls -1 .")
	assert str1 == str2

def test_myoutput2(capsys): # or use "capfd" for fd-level
	str1 = os.system("./ft_ls -1 . . . . .")
	str2 = os.system("ls -1 . . . . .")
	assert str1 == str2

def test_myoutput3(capsys): # or use "capfd" for fd-level
	reset_sandbox()
	os.system("touch sandbox/{aaa, bbb, ccc}")
	str1 = os.system("./ft_ls -1")
	str2 = os.system("ls -1")
	assert str1 == str2


##################################### test: -r ################################
def test_minus_r_1(capsys): # or use "capfd" for fd-level
	reset_sandbox()
	os.system("touch sandbox/{a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z}")
	str1 = os.system("./ft_ls -1r")
	str2 = os.system("ls -1r")
	assert str1 == str2

def test_myoutput4(capsys): # or use "capfd" for fd-level
	str1 = os.system("./ft_ls -1")
	str2 = os.system("ls -1")
	assert str1 == str2

os.system("rm -fr sandbox")
