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
        return "Cirlce(%r, %r)" % (self.cntr, self.r)

    def area(self):
        return (math.pi * self.r * self.r)

    def perimeter(self):
        return (2 * math.pi * self.r)

    def translate(self, dx, dy):
        return Circle(self.cntr.translate(dx, dy), self.r)

class Rectangle:
    def __init__(self, upper_left, lower_right):
        self.upper_left = upper_left
        self.lower_right = lower_right

    def __rpr__(self):
        return "Rectangle(Point(%r,%r),Point(%r,%r))" % (self.upper_left.x, self.upper_left.y, self.lower_right.x, self.lower_right.y)

    def area(self):
        height = self.lower_right.delta_y(self.upper_left.y)
        width = self.lower_right.delta_x(self.upper_left.x)
        return height.y * width.x

    def perimeter(self): 
        height = self.lower_right.delta_y(self.upper_left.y)
        width = self.lower_right.delta_x(self.upper_left.x)
        return 2 * width + 2 * height

    def translate(self, dx, dy):
        height = self.lower_right.delta_y(self.upper_left.y)
        width = self.lower_right.delta_x(self.upper_left.x)
        
        new_LR = self.lower_right.translate(dx, dy)
        new_UL = new_LR.translate(height.y, width.x)

        return Rectangle(new_UL, new_LR)
        
