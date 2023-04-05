import math
class Point:

    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def __repr__(self):
        return "Point(%r, %r)" % (self.x, self.y)

    def delta_x(self, dx):
        d_x = dx - self.x
        return Point(d_x, 0)

    def delta_y(self, dy):
        d_y = dy - self.y
        return Point(0, d_y)

    def translate(self, dx, dy):
        new_x = self.x + dx
        new_y = self.y + dy
        return Point(new_x, new_y)

class Circle:

    def __init__(self, cntr, r):
        self.cntr = cntr
        self.r = r

    def __repr__(self):
        return "Cirlce(Point(%r, %r), %r)" % (self.cntr.x, self.cntr.y, self.r)

    def area(self):
        return (math.pi * self.r * self.r)

    def perimeter(self):
        return (2 * math.pi * self.r)

    def translate(self, dx, dy):
        return Circle(self.cntr.translate(dx, dy), self.r)
