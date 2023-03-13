#!/usr/bin/env python3

import datetime

def every_lab(foo):
    print("This is outrageous! Unfair!")
    return None


def main():
    """
    Create a datetime object for today's date
    """
    # COMPLETE IMPLEMENTATION
    todays_date: datetime = datetime.date(2023,3,3)

    date_list = every_lab(todays_date)

    """ 
    variable date_list should contain datetime objects 
    for all the days when you have a lab
    print these dates in the format "Mon, 15 Jan 21"
    """

    # COMPLETE IMPLEMENTATION
    print(f"{date_list}")

    


def every_lab(todays_date: datetime) -> list:
    """
    Assume that you have a lab every week till the end of classes. 
    (Only your lab, in this instance.)

    This function will create datetimes objects for those labs, 
    add them to a list and then return this list
    """

    # COMPLETE IMPLEMENTATION
    date_list: list = list(())
    
    delta = datetime.timedelta(days=7)
    end_date: datetime = datetime.date(2023,4,6)
    cur_date: datetime = todays_date

    date_str: str
    while cur_date <= end_date:
        date_str = cur_date.strftime("%a, %d %b %m")
        date_list.append(cur_date)
        cur_date = cur_date + delta
    
    return date_list

if __name__ == "__main__":
    main()
