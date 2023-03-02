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
                    airlines: dict = yaml.safe_load(arg_file)
                    airlines_df: pd.DataFrame = pd.json_normalize(airlines["airlines"])

                    # airline_id | airline_name | airline_icao_unique_code | airline_country
                    df_list.append(airlines_df)

                elif key == "AIRPORTS":
                    airports: dict = yaml.safe_load(arg_file)
                    airports_df: pd.DataFrame = pd.json_normalize(airports["airports"])

                    # airport_id | airport_name | airport_city | airport_country | airport_icao_unique_code | airport_altitude
                    df_list.append(airports_df)
                
                elif key == "ROUTES":
                    routes: dict = yaml.safe_load(arg_file)
                    routes_df: pd.DataFrame = pd.json_normalize(routes["routes"])

                    # route_airline_id | route_from_airport_id | route_to_airport_id
                    df_list.append(routes_df)

                else:
                    continue

                arg_file.close()

    return df_list

"""
Function:   a
"""
def question_select(inputs: dict, df_list) -> None:
     parameters: dict
     key: str = "QUESTION"
     if key in inputs:
        #  print(f"Question: {inputs[key]}")

         if inputs[key] == "q1":
            # Q - What are the top 20 airlines that offer the greatest
            # number of routes with destination country Canada?

            # airlines: airline_id, airline_name
            # airports: airport_id, airport_country
            # routes: route_airline_id, route_to_airport_id
            parameters = {"field1" : "add", "field2" : "add2"}

         if inputs[key] == "q2":
            # Q - What are the top 30 countries with least appearances as
            # destination country on the routes data?

            # airlines: NA
            # airports: airport_id, airport_country
            # routes: route_to_airport_id 
            parameters = {"field1" : "add", "field2" : "add2"}

         if inputs[key] == "q3":
            # Q - What are the top 10 destination airports?

            # airlines: NA
            # airports: airport_id, airport_name, airport_city, airport_country, airport_icao_unique_code
            # routes: route_to_airport_id
            parameters = {"field1" : "add", "field2" : "add2"}

         if inputs[key] == "q4":
            # Q - What are the top 10 destination cities?

            # airlines: NA
            # airports: airport_id, airport_city, airport_country
            # routes: route_to_airport_id
            parameters = {"field1" : "add", "field2" : "add2"}

         if inputs[key] == "q5":
            # Q - What are the unique top 10 Canadian routes with the
            # most difference between the destination altitude and the
            # origin altitude? (if CYYJ-CYVR is included, CYVR-CYYJ should not)

            # airlines: NA
            # airports: airport_id, airport_icao_unique_code, airport_altitude
            # routes: route_from_airport_id, route_to_airport_id
            parameters = {"field1" : "add", "field2" : "add2"}
        

def main():
    inputs_dict: dict = get_inputs()

    # print inputs
    for key in inputs_dict:
        print(f"{key} : {inputs_dict[key]}")
    print()

    df_list: list = create_arg_dataframes(inputs_dict)

    question_select(inputs_dict, df_list)


if __name__ == '__main__':
    main()
