#!/bin/zsh

rm -fr ./test
rm -fr ./log/result_ft_ls
rm -fr ./log/result_ls

mkdir test
#------------------------------------------------------------------------------
rm -fr ./log/result_ft_ls
rm -fr ./log/result_ls
ls -1 > log/result_ls
../ft_ls -1 > log/result_ft_ls
result=$(`diff log/result_ls log/result_ft_ls`)
if [[ $result = '' ]] ; then
	echo "OK"
else
	echo "KO"
fi

#------------------------------------------------------------------------------
rm -fr ./log/result_ft_ls
rm -fr ./log/result_ls
ls -- -1 > log/result_ls
../ft_ls -- -1 > log/result_ft_ls
result=$(`diff log/result_ls log/result_ft_ls`)
if [[ $result = '' ]] ; then
	echo "OK"
else
	echo "KO"
fi
