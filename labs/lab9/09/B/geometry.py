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


