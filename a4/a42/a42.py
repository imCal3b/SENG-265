#!/usr/bin/env python
"""Assignment 4 Part 2 | Brayden Shkwarok V00866278"""
from collections import namedtuple
import random as r

cnt = namedtuple('cnt', ['min','max']) # shape counter
sha = namedtuple('sha', ['min','max']) # shape type
coord = namedtuple('coord',['x_min','x_max','y_min','y_max']) # shape coordinate
rad = namedtuple('rad',['min','max']) # circle radius
eli_rad = namedtuple('eli_rad',['rx_min','rx_max','ry_min','ry_max']) # ellipse radius
rec_dim = namedtuple('rec_dim',['w_min','w_max','h_min','h_max']) #rectangle dimensions
red = namedtuple('red',['min','max'])
green = namedtuple('green',['min','max'])
blue = namedtuple('blue',['min','max'])
opac = namedtuple('opac',['min','max'])

col = namedtuple('col',['red','green','blue','opac']) # colour
cir = namedtuple('cir',['x','y','radius']) # circle
rec = namedtuple('rec',['x','y','h','w']) # rectangle
eli = namedtuple('eli',['x','y','rx','ry']) # ellipse

class PyArtConfig:
    """PyArtConfig Class"""

    def __init__(cls, count:namedtuple = cnt(0,10000), shape:namedtuple = sha(0,3), 
                 coordinate:namedtuple = coord(0,500,0,500), radius:namedtuple = rad(0,100),
                 eli_radius:namedtuple = eli_rad(10,30,10,30), rec_dimensions:namedtuple = rec_dim(0,100,0,100),
                 c_red:namedtuple = red(0,255), c_green:namedtuple = green(0,255),
                 c_blue:namedtuple = blue(0,255), c_opac:namedtuple = opac(0.0,1.0)) -> None:
        """PyArtConfig constructor"""
        cls.cnt = count
        cls.sha = shape
        cls.coord = coordinate
        cls.rad = radius
        cls.eli_rad = eli_radius
        cls.rec_dim = rec_dimensions
        cls.red = c_red
        cls.green = c_green
        cls.blue = c_blue
        cls.opac = c_opac


class RandomShape:
    """RandomShape Class"""
    config: PyArtConfig = PyArtConfig(count = cnt(0,10))

    @classmethod
    def  as_Part2_line(cls, cnt:int) -> str:
        """as_Part2_line() method"""
        sha:int = r.randrange(cls.config.sha.min, cls.config.sha.max)
        x:int = r.randint(cls.config.coord.x_min, cls.config.coord.x_max)
        y:int = r.randint(cls.config.coord.y_min, cls.config.coord.y_max)
        rad:int = r.randint(cls.config.rad.min, cls.config.rad.max)
        rx:int = r.randint(cls.config.eli_rad.rx_min, cls.config.eli_rad.rx_max)
        ry:int = r.randint(cls.config.eli_rad.ry_min, cls.config.eli_rad.ry_max)
        w:int = r.randint(cls.config.rec_dim.w_min, cls.config.rec_dim.w_max)
        h:int = r.randint(cls.config.rec_dim.h_min, cls.config.rec_dim.h_max)
        R:int = r.randint(cls.config.red.min, cls.config.red.max)
        G:int = r.randint(cls.config.green.max, cls.config.green.max)
        B:int = r.randint(cls.config.blue.min, cls.config.blue.max)
        OP:int= r.uniform(cls.config.opac.min, cls.config.opac.max)

        string1:str = f"{cnt:>3} {sha:>3} {x:>3} {y:>3} {rad:>3} {rx:>3} {ry:>3} {w:>3} {h:>3} "
        string2:str = f"{R:>3} {G:>3} {B:>3} {OP:>.1f}"

        return f"{string1}{string2}"

    @classmethod
    def as_svg(cls, cnt:int) -> str:
        """as_svg() method"""
        string:str = cls.as_Part2_line(cnt)
        vals:tuple = tuple(map(float, string.split()))
        
        shape:int = vals[1]
        string_colour:str = f'fill="rgb({int(vals[9])},{int(vals[10])},{int(vals[11])})" fill-opacity="{vals[12]}">'

        if shape == 0:
            string_circle:str = f'<circle cx="{int(vals[2])}" cy="{int(vals[3])}" r="{int(vals[4])}" '
            string_circle_end:str = '</circle>'
            return f"{string_circle}{string_colour}{string_circle_end}"
        
        elif shape == 1:
            string_rect:str = f'<rect x="{int(vals[2])}" y="{int(vals[3])}" width="{int(vals[7])}" height="{int(vals[8])}" '
            string_rect_end:str = '</rect>'
            return f"{string_rect}{string_colour}{string_rect_end}"

        else:
            string_ellipse:str = f'<rect cx="{int(vals[2])}" cy="{int(vals[3])}" rx="{int(vals[7])}" ry="{int(vals[8])}" '
            string_ellipse_end:str = '</ellipse>'
            return f"{string_ellipse}{string_colour}{string_ellipse_end}"


    def __str__(cls) -> str:
        """"__str__() method"""
        string:str = f'{"CNT":>3} {"SHA":>3} {"X":>3} {"Y":>3} {"RAD":>3} {"RX":>3} {"RY":>3} {"W":>3} {"H":>3} {"R":>3} {"G":>3} {"B":>3} {"OP":>3}\n'

        for i in range(0,cls.config.cnt.max):
            string += (cls.as_Part2_line(i) + "\n")

        return string


def main() -> None:
    """Main method"""
    shape_table = RandomShape()
    print()
    print(shape_table)


if __name__ == "__main__":
    main()