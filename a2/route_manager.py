#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Wed Feb 8 14:44:33 2023
Based on: https://www.kaggle.com/datasets/arbazmohammad/world-airports-and-airlines-datasets
Sample input: --AIRLINES="airlines.yaml" --AIRPORTS="airports.yaml" --ROUTES="routes.yaml" --QUESTION="q1" --GRAPH_TYPE="bar"
@author: rivera
@author: Brayden Shkwarok V00866278
"""
import pandas as pd
import yaml
import sys
import os

"""
Function:   Read and parse the input arguments from program call
            and store data values in the list parameters passed
            to the function.
Inputs:     arg_type: list - list to store the argument types.
            arg: list - list of the specified arguments.
Return: NA
"""
def get_inputs(arg_type: list, arg: list) -> int:
    if len(sys.argv) == 1:
        print("No Arguments Given...")
        return 0
    
    for i in range(1, len(sys.argv)):
        temp1, temp2 = sys.argv[i].split("=")
        arg_type.append(temp1.split("--")[1])
        arg.append(temp2)

    return len(sys.argv)-1

    

def main():
    arg_type: list = []
    arg: list = []
    argc: int = get_inputs(arg_type, arg)

    for i in range(argc):
        print(f"{arg_type[i]} : {arg[i]}")


if __name__ == '__main__':
    main()
