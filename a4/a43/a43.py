#!/usr/bin/env python
"""Assignment 4 Part 1 | Brayden Shkwarok V00866278"""
from typing import IO
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
rec = namedtuple('rec',['x','y','w','h']) # rectangle
eli = namedtuple('eli',['x','y','rx','ry']) # ellipse

class Shape:
    """Shape Class"""
    __num_shapes: int = 0

    def __init__(self, x:int, y:int, colour:namedtuple) -> None:
        """Shape constructor"""
        self.x: int = x
        self.y: int = y
        self.red: int = colour.red
        self.green: int = colour.green
        self.blue: int = colour.blue
        self.opac: int = colour.opac

        Shape.__num_shapes += 1

    @classmethod
    def get_shape_count(cls) -> int:
        """get_shape_count() method"""
        return cls.__num_shapes


class CircleShape(Shape):
    """CircleShape Class"""

    def __init__(self, cir:namedtuple, colour:namedtuple) -> None:
        """Circle constructor"""
        super().__init__(cir.x, cir.y, colour)
        self.radius = cir.radius

    @classmethod
    def drawCircleLine(cls, f: IO[str], t: int, c: 'CircleShape') -> None:
        """drawCircleLine() method"""
        ts: str = "   " * t
        line1: str = f'<circle cx="{c.x}" cy="{c.y}" r="{c.radius}" '
        line2: str = f'fill="rgb({c.red}, {c.green}, {c.blue})" fill-opacity="{c.opac}"></circle>'
        f.write(f"{ts}{line1+line2}\n")


class RectangleShape(Shape):
    """RectangleShape Class"""
    
    def __init__(self, rec:namedtuple, colour:namedtuple) -> None:
        """Rectangle constructor"""
        super().__init__(rec.x, rec.y, colour)
        self.h = rec.h
        self.w = rec.w

    @classmethod
    def drawRectangleLine(cls, f: IO[str], t: int, r: 'RectangleShape') -> None:
        """drawRectangleLine() method"""
        ts: str = "   " * t
        line1: str = f'<rect x="{r.x}" y="{r.y}" width="{r.w}" height="{r.h}" '
        line2: str = f'fill="rgb({r.red}, {r.green}, {r.blue})" fill-opacity="{r.opac}"></rect>'
        f.write(f"{ts}{line1+line2}\n")


class EllipseShape(Shape):
    """EllipseShape Class"""

    def __init__(self, eli:namedtuple, colour:namedtuple) -> None:
        """Ellipse constructor"""
        super().__init__(eli.x, eli.y, colour)
        self.rx = eli.rx
        self.ry = eli.ry

    @classmethod
    def drawEllipseLine(cls, f: IO[str], t: int, e: 'EllipseShape') -> None:
        """drawEllipseLine() method"""
        ts: str = "   " * t
        line1: str = f'<ellipse cx="{e.x}" cy="{e.y}" rx="{e.rx}" ry="{e.ry}" '
        line2: str = f'fill="rgb({e.red}, {e.green}, {e.blue})" fill-opacity="{e.opac}"></ellipse>'
        f.write(f"{ts}{line1+line2}\n")


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

    def __str__(cls) -> None:
        return f"{cls.sha} {cls.coord} {cls.rad} {cls.eli_rad} {cls.rec_dim} {cls.red} {cls.green} {cls.blue} {cls.opac}"


class HtmlDocument:
    """HtmlDocument Class"""

    @classmethod
    def writeHTMLline(cls,f: IO[str], t: int, line: str) -> None:
     """writeHTMLline() method"""
     ts = "   " * t
     f.write(f"{ts}{line}\n")


    @classmethod
    def writeHTMLHeader(cls,f: IO[str], title: str) -> None:
        """writeHTMLHeader() method"""
        cls.writeHTMLline(f, 0, "<html>")
        cls.writeHTMLline(f, 0, "<head>")
        cls.writeHTMLline(f, 1, f"<title>{title}</title>")
        cls.writeHTMLline(f, 0, "</head>")
        cls.writeHTMLline(f, 0, "<body>")


    @classmethod
    def writeHTMLcomment(cls,f: IO[str], t: int, com: str) -> None:
        """writeHTMLcomment() method"""
        ts: str = "   " * t
        f.write(f"{ts}<!--{com}-->\n")


    @classmethod
    def writeHTMLfile(cls, canvas:tuple, config:PyArtConfig, fnam:str) -> None:
        """writeHTMLfile() method"""
        title = "My Art"
        f: IO[str] = open(fnam, "w")
        cls.writeHTMLHeader(f, title)
        SvgCanvas.openSVGcanvas(f, 1, canvas)

        for i in range(0,config.cnt.max):
            RandomShape.as_svg(config, i, f, 2)

        SvgCanvas.closeSVGcanvas(f, 1)
        f.close()


class SvgCanvas:
    """SvgCanvas Class"""

    @classmethod
    def openSVGcanvas(cls,f: IO[str], t: int, canvas: tuple) -> None:
        """openSVGcanvas() method"""
        ts: str = "   " * t
        HtmlDocument.writeHTMLcomment(f, t, "Define SVG drawing box")
        f.write(f'{ts}<svg width="{canvas[0]}" height="{canvas[1]}">\n')


    @classmethod
    def closeSVGcanvas(cls,f: IO[str], t: int) -> None:
        """closeSVGcanvas() method"""
        ts: str = "   " * t
        f.write(f"{ts}</svg>\n")
        f.write(f"</body>\n")
        f.write(f"</html>\n")


class RandomShape:
    """RandomShape Class"""

    @classmethod
    def  as_Part2_line(cls, cnt:int, config:PyArtConfig) -> str:
        """as_Part2_line() method"""
        sha:int = r.randrange(config.sha.min, config.sha.max)
        x:int = r.randint(config.coord.x_min, config.coord.x_max)
        y:int = r.randint(config.coord.y_min, config.coord.y_max)
        rad:int = r.randint(config.rad.min, config.rad.max)
        rx:int = r.randint(config.eli_rad.rx_min, config.eli_rad.rx_max)
        ry:int = r.randint(config.eli_rad.ry_min, config.eli_rad.ry_max)
        w:int = r.randint(config.rec_dim.w_min, config.rec_dim.w_max)
        h:int = r.randint(config.rec_dim.h_min, config.rec_dim.h_max)
        R:int = r.randint(config.red.min, config.red.max)
        G:int = r.randint(config.green.min, config.green.max)
        B:int = r.randint(config.blue.min, config.blue.max)
        OP:int= r.uniform(config.opac.min, config.opac.max)

        string1:str = f"{cnt:>3} {sha:>3} {x:>3} {y:>3} {rad:>3} {rx:>3} {ry:>3} {w:>3} {h:>3} "
        string2:str = f"{R:>3} {G:>3} {B:>3} {OP:>.1f}"

        return f"{string1}{string2}"

    @classmethod
    def as_svg(cls, config:PyArtConfig, cnt:int, f: IO[str], t: int) -> str:
        """as_svg() method"""
        string:str = cls.as_Part2_line(cnt, config)
        vals:tuple = tuple(map(float, string.split()))
        
        shape:int = vals[1]
        string_colour:str = f'fill="rgb({int(vals[9])},{int(vals[10])},{int(vals[11])})" fill-opacity="{vals[12]}">'
        colour:namedtuple = col(int(vals[9]),int(vals[10]),int(vals[11]),vals[12])

        if shape == 0:
            string_circle:str = f'<circle cx="{int(vals[2])}" cy="{int(vals[3])}" r="{int(vals[4])}" '
            string_circle_end:str = '</circle>'
            circle:namedtuple = cir(int(vals[2]),int(vals[3]),int(vals[4]))
            CircleShape.drawCircleLine(f, t, CircleShape(circle, colour))

            return f"{string_circle}{string_colour}{string_circle_end}"
        
        elif shape == 1:
            string_rect:str = f'<rect x="{int(vals[2])}" y="{int(vals[3])}" width="{int(vals[7])}" height="{int(vals[8])}" '
            string_rect_end:str = '</rect>'
            rectangle:namedtuple = rec(int(vals[2]),int(vals[3]),int(vals[7]),int(vals[8]))
            RectangleShape.drawRectangleLine(f, t, RectangleShape(rectangle, colour))

            return f"{string_rect}{string_colour}{string_rect_end}"

        else:
            string_ellipse:str = f'<rect cx="{int(vals[2])}" cy="{int(vals[3])}" rx="{int(vals[7])}" ry="{int(vals[8])}" '
            string_ellipse_end:str = '</ellipse>'
            ellipse:namedtuple = eli(int(vals[2]),int(vals[3]),int(vals[7]),int(vals[8]))
            EllipseShape.drawEllipseLine(f, t, EllipseShape(ellipse, colour))

            return f"{string_ellipse}{string_colour}{string_ellipse_end}"


    def __str__(cls) -> str:
        """"__str__() method"""
        string:str = f'{"CNT":>3} {"SHA":>3} {"X":>3} {"Y":>3} {"RAD":>3} {"RX":>3} {"RY":>3} {"W":>3} {"H":>3} {"R":>3} {"G":>3} {"B":>3} {"OP":>3}\n'

        for i in range(0,cls.config.cnt.max):
            string += (cls.as_Part2_line(i) + "\n")

        return string


#-----------------------------------------------------------------------
def main() -> None:
    """Main method"""
    fnam: str = "./a431.html"
    HtmlDocument.writeHTMLfile((500,300), PyArtConfig(count=cnt(0,15), c_blue=blue(50,150), c_red=red(50,200), c_green=green(15,30), c_opac=opac(0.3,1)), fnam)

    fnam: str = "./a432.html"
    HtmlDocument.writeHTMLfile((500,500), PyArtConfig(count=cnt(0,500), c_green=green(100,255), c_red=red(50,200), c_opac=opac(0.3,0.8)), fnam)

    fnam: str = "./a433.html"
    HtmlDocument.writeHTMLfile((800,500), PyArtConfig(count=cnt(0,100), shape=sha(1,2), c_blue=blue(50,150), c_red=red(0,0), c_green=green(0,50)), fnam)

if __name__ == "__main__":
    main()
