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
import json
import sys
import os

"""
Function:   Read and parse the input arguments from program call
            and store data values in the list parameters passed
            to the function.
Inputs:     NA.
Return:     dict - A dictionary containing the input arguments.
"""
def get_inputs() -> dict:
    arg_type: str
    arg: str

    if len(sys.argv) == 1:
        print("No Arguments Given...")
        return 0
    
    inputs: dict = dict({})
    for i in range(1, len(sys.argv)):
        temp1, temp2 = sys.argv[i].split("=")
        arg_type = temp1.split("--")[1]

        if ".yaml" in temp2: 
            arg = "./a2/" + temp2
        else:
            arg = temp2

        inputs.update({arg_type:arg})

    return inputs

"""
Function:   Take the input arguments and open the specified yaml
            files as pandas DataFrames.
Inputs:     inputs: dict - Dictionary of the input arguments.
Return:     list - List containing the created DataFrames.
"""
def create_arg_dataframes(inputs: dict) -> list:
    df_list: list = []

    for key in inputs:

        if ".yaml" in inputs[key]:
            with open(inputs[key], "r") as arg_file:

                if key == "AIRLINES":
                    airlines = yaml.safe_load(arg_file)
                    airlines_df: pd.DataFrame = pd.json_normalize(airlines["airlines"])

                    df_list.append(airlines_df)

                elif key == "AIRPORTS":
                    airports = yaml.safe_load(arg_file)
                    airports_df: pd.DataFrame = pd.json_normalize(airports["airports"])

                    df_list.append(airports_df)
                
                elif key == "ROUTES":
                    routes = yaml.safe_load(arg_file)
                    routes_df: pd.DataFrame = pd.json_normalize(routes["routes"])

                    df_list.append(routes)

                else:
                    continue

                arg_file.close()

    return df_list

"""
Function:   a
"""
def question(inputs: dict) -> None:
     parameters: dict
     key: str = "QUESTION"
     if key in inputs:
         print(f"Question: {inputs[key]}")

         if inputs[key] == "q1":
            # specify the important data fields for producing
            # the output to the question.
            parameters = {"field1" : "add", "field2" : "add2"}

         if inputs[key] == "q2":
            # specify the important data fields for producing
            # the output to the question.
            parameters = {"field1" : "add", "field2" : "add2"}

         if inputs[key] == "q3":
            # specify the important data fields for producing
            # the output to the question.
            parameters = {"field1" : "add", "field2" : "add2"}

         if inputs[key] == "q4":
            # specify the important data fields for producing
            # the output to the question.
            parameters = {"field1" : "add", "field2" : "add2"}

         if inputs[key] == "q5":
            # specify the important data fields for producing
            # the output to the question.
            parameters = {"field1" : "add", "field2" : "add2"}
        

def main():
    inputs_dict: dict = get_inputs()

    # print inputs
    for key in inputs_dict:
        print(f"{key} : {inputs_dict[key]}")
    print()

    df_list: list = create_arg_dataframes(inputs_dict)

    question(inputs_dict)


if __name__ == '__main__':
    main()
