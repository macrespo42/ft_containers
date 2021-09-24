#!/bin/bash

if [ ! -s ./diff ]
then
	echo "No diff between std and ft in test located in main.cpp ✅"
else
	echo "Diff between std and ft check diff file for more details ... ❗️"
fi