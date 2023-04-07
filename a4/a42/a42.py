#!/usr/bin/env python
"""Assignment 4 Part 2 | Brayden Shkwarok V00866278"""
from typing import IO
from collections import namedtuple

col = namedtuple('col',['red','green','blue','opac']) # colour
cir = namedtuple('cir',['x','y','radius']) # circle
rec = namedtuple('rec',['x','y','h','w']) # rectangle
eli = namedtuple('eli',['x','y','rx','ry']) # ellipse

coord = namedtuple('coord',['x_min','x_max','y_min','y_max']) # shape coordinate
eli_rad = namedtuple('eli_rad',['rx_min','rx_max','ry_min','ry_max']) # ellipse radius
rec_dim = namedtuple('rec_dim',['w_min','w_max','h_min','h_max']) #rectangle dimensions

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
    def writeHTMLfile(cls) -> None:
        """writeHTMLfile() method"""
        fnam: str = "./a4/a41/a41.html" #TODO: added ./a4/ to run code in vsCode
        title = "My Art"
        f: IO[str] = open(fnam, "w")
        cls.writeHTMLHeader(f, title)
        SvgCanvas.openSVGcanvas(f, 1, (500,300))
        genArt(f, 2)
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


class PyArtConfig:
    """PyArtConfig Class"""
    cnt: tuple = tuple(0,0)
    sha: tuple = tuple(0,3) # TODO: change upper bound based on inclusion
    coord: namedtuple = coord(0,0)
    rad: tuple = tuple()
    eli_rad: namedtuple = eli_rad(0,0)
    rec_dim: namedtuple = rec_dim(0,0)
    red: int = 0
    green: int


#-----------------------------------------------------------------------
def genArt(f: IO[str], t: int) -> None:
   """genART method"""
   RectangleShape.drawRectangleLine(f, t, RectangleShape(rec(0,0,50,50), col(255,0,0,1.0)))
   RectangleShape.drawRectangleLine(f, t, RectangleShape(rec(50,50,50,50), col(255,0,0,1.0)))
   CircleShape.drawCircleLine(f, t, CircleShape(cir(50,50,50), col(255,0,0,1.0)))
   CircleShape.drawCircleLine(f, t, CircleShape(cir(150,50,50), col(255,0,0,1.0)))
   CircleShape.drawCircleLine(f, t, CircleShape(cir(250,50,50), col(255,0,0,1.0)))
   CircleShape.drawCircleLine(f, t, CircleShape(cir(350,50,50), col(255,0,0,1.0)))
   CircleShape.drawCircleLine(f, t, CircleShape(cir(450,50,50), col(255,0,0,1.0)))
   CircleShape.drawCircleLine(f, t, CircleShape(cir(50,250,50), col(0,0,255,1.0)))
   CircleShape.drawCircleLine(f, t, CircleShape(cir(150,250,50), col(0,0,255,1.0)))
   CircleShape.drawCircleLine(f, t, CircleShape(cir(250,250,50), col(0,0,255,1.0)))
   CircleShape.drawCircleLine(f, t, CircleShape(cir(350,250,50), col(0,0,255,1.0)))
   EllipseShape.drawEllipseLine(f, t, EllipseShape(eli(450,250,50, 20), col(0,0,255,1.0)))

def main() -> None:
    """Main method"""
    HtmlDocument.writeHTMLfile()
    print(f"# Shapes: {Shape.get_shape_count()}")

if __name__ == "__main__":
    main()