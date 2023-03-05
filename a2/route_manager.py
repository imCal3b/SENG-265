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
import numpy
import os # not used


def get_inputs() -> dict:
    """
    Function:   Read and parse the input arguments from program call
                and store data values in the list parameters passed
                to the function.
    Inputs:     NA.
    Return:     dict - A dictionary containing the input arguments.
    """
    arg_type: str
    arg: str

    if len(sys.argv) == 1:
        print("No Arguments Given...")
        return 0
    
    inputs: dict = dict({})
    for i in range(1, len(sys.argv)):
        temp1, temp2 = sys.argv[i].split("=")
        arg_type = temp1.split("--")[1]

        if ".yaml" in temp2:            # NOTE: possible change (not needed) when running in VM??
            arg = "./a2/" + temp2
        else:
            arg = temp2

        inputs.update({arg_type:arg})

    return inputs


def create_arg_dataframes(inputs: dict) -> dict:
    """
    Function:   Take the input arguments and open the specified yaml
                files as pandas DataFrames.
    Inputs:     inputs: dict - Dictionary of the input arguments.
    Return:     list - List containing the created DataFrames.
    """
    df_dict: dict = dict({})

    for key in inputs:

        if ".yaml" in inputs[key]:
            with open(inputs[key], "r") as arg_file:

                if key == "AIRLINES":
                    airlines: dict = yaml.safe_load(arg_file)
                    airlines_df: pd.DataFrame = pd.json_normalize(airlines["airlines"])

                    # airline_id | airline_name | airline_icao_unique_code | airline_country
                    df_dict.update({"AIRLINES":airlines_df})

                elif key == "AIRPORTS":
                    airports: dict = yaml.safe_load(arg_file)
                    airports_df: pd.DataFrame = pd.json_normalize(airports["airports"])

                    # airport_id | airport_name | airport_city | airport_country | airport_icao_unique_code | airport_altitude
                    df_dict.update({"AIRPORTS":airports_df})
                
                elif key == "ROUTES":
                    routes: dict = yaml.safe_load(arg_file)
                    routes_df: pd.DataFrame = pd.json_normalize(routes["routes"])

                    # route_airline_id | route_from_airport_id | route_to_airport_id
                    df_dict.update({"ROUTES":routes_df})

                else:
                    continue

                arg_file.close()

    return df_dict

"""
Function:   a
"""
def question_select(inputs: dict, df_dict: dict) -> None:
     # data fields:
     # airline_id | airline_name | airline_icao_unique_code | airline_country
     # airport_id | airport_name | airport_city | airport_country | airport_icao_unique_code | airport_altitude
     # route_airline_id | route_from_airport_id | route_to_airport_id

     airlines_df: pd.DataFrame = df_dict["AIRLINES"]
     airports_df: pd.DataFrame = df_dict["AIRPORTS"]
     routes_df: pd.DataFrame = df_dict["ROUTES"]
     
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

            airlines_df.drop(['airline_icao_unique_code','airline_country'],inplace=True,axis=1)
            airports_df.drop(['airport_name','airport_city','airport_icao_unique_code','airport_altitude'],inplace=True,axis=1)
            routes_df.drop(['route_from_aiport_id'],inplace=True,axis=1)

            airports_df = airports_df[airports_df['airport_country'] == 'Canada']
            
            merged_df: pd.DataFrame = pd.merge(routes_df,airlines_df, left_on=['route_airline_id'], right_on=['airline_id'])
            merged_df = pd.merge(merged_df, airports_df, left_on=['route_to_airport_id'], right_on=['airport_id'])

            result: pd.DataFrame = merged_df.groupby(['airline_name'], 
                                                     as_index=False).size().sort_values(by=['size','airline_name'],
                                                     ascending=[False,True]).head(20)

            print(result)

         elif inputs[key] == "q2":
            # Q - What are the top 30 countries with least appearances as
            # destination country on the routes data?

            # airlines: NA
            # airports: airport_id, airport_country
            # routes: route_to_airport_id 
            airports_df.drop(['airport_name','airport_city','airport_icao_unique_code','airport_altitude'],inplace=True,axis=1)
            routes_df.drop(['route_airline_id','route_from_aiport_id'],inplace=True,axis=1)

            airports_df['airport_country'] = airports_df['airport_country'].str.strip()
            merged_df: pd.DataFrame = pd.merge(routes_df,airports_df,left_on=['route_to_airport_id'],right_on=['airport_id'])

            result: pd.DataFrame = merged_df.groupby(['airport_country'],
                                                     as_index=False).size().sort_values(by=['size','airport_country'],
                                                     ascending=[True,True]).head(30)

            print(result)

         elif inputs[key] == "q3":
            # Q - What are the top 10 destination airports?

            # airlines: NA
            # airports: airport_id, airport_name, airport_city, airport_country, airport_icao_unique_code
            # routes: route_to_airport_id
            airports_df.drop(['airport_altitude'],inplace=True,axis=1)
            routes_df.drop(['route_airline_id','route_from_aiport_id'],inplace=True,axis=1)

            merged_df: pd.DataFrame = pd.merge(routes_df,airports_df,left_on=['route_to_airport_id'],right_on=['airport_id'])

            result: pd.DataFrame = merged_df.groupby(['airport_name'],
                                                     as_index=False).size().sort_values(by=['size','airport_name'],
                                                     ascending=[False,True]).head(10)

            print(result)

         elif inputs[key] == "q4":
            # Q - What are the top 15 destination cities?

            # airlines: NA
            # airports: airport_id, airport_city, airport_country
            # routes: route_to_airport_id
            airports_df.drop(['airport_name','airport_icao_unique_code','airport_altitude'],inplace=True,axis=1)
            routes_df.drop(['route_airline_id','route_from_aiport_id'],inplace=True,axis=1)

            merged_df: pd.DataFrame = pd.merge(routes_df,airports_df,left_on=['route_to_airport_id'],right_on=['airport_id'])

            result: pd.DataFrame = merged_df.groupby(['airport_city','airport_country'],
                                                     as_index=False).size().sort_values(by=['size','airport_city'],
                                                     ascending=[False,True]).head(15)

            print(result)

         elif inputs[key] == "q5":
            # Q - What are the unique top 10 Canadian routes with the
            # most difference between the destination altitude and the
            # origin altitude? (if CYYJ-CYVR is included, CYVR-CYYJ should not)

            # airlines: NA
            # airports: airport_id, airport_country, airport_icao_unique_code, airport_altitude
            # routes: route_from_airport_id, route_to_airport_id
            airports_df.drop(['airport_name','airport_city'],inplace=True,axis=1)
            routes_df.drop(['route_airline_id'],inplace=True,axis=1)
            
            airports_df['airport_altitude'] = pd.to_numeric(airports_df['airport_altitude'])

            merged_from_df: pd.DataFrame = pd.merge(routes_df,airports_df,
                                                    left_on=['route_from_aiport_id'],right_on=['airport_id'])
            
            airports_df.rename(columns={"airport_id":"to_airport_id"}, inplace=True)
            airports_df.rename(columns={"airport_country":"to_airport_country"}, inplace=True)
            airports_df.rename(columns={"airport_icao_unique_code":"to_airport_icao_unique_code"}, inplace=True)
            airports_df.rename(columns={"airport_altitude":"to_airport_altitude"}, inplace=True)

            result: pd.DataFrame = pd.merge(merged_from_df,airports_df,
                                            left_on=['route_to_airport_id'],right_on=['to_airport_id'])

            result['EL_Delta'] = numpy.where(result['airport_altitude'] == result['to_airport_altitude'], 0,
                                             abs(result['airport_altitude'] - result['to_airport_altitude']))
            
            result = result[result['airport_country'] == 'Canada']
            result = result[result['to_airport_country'] == 'Canada']
            
            result = result.sort_values(by=['EL_Delta'], ascending=False).head(10)
            
            print(result)

        # else: Invalid Input 

def main():
    inputs_dict: dict = get_inputs()

    # print inputs
    for key in inputs_dict:
        print(f"{key} : {inputs_dict[key]}")
    print()

    df_dict: dict = create_arg_dataframes(inputs_dict)

    question_select(inputs_dict, df_dict)


if __name__ == '__main__':
    main()
