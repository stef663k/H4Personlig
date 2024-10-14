class Shape:
    def area(self) -> float:
        return 0.0

    def perimeter(self) -> float:
        return 0.0
    
class Circle(Shape):
    def __init__(self, radius: float):
        self.radius = radius

    def area(self) -> float:
        return 3.14 * self.radius**2

    def perimeter(self) -> float:
        return 2 * 3.14 * self.radius
    
class Rectangle(Shape):
    def __init__(self, width: float, height: float):
        self.width = width
        self.height = height

    def area(self) -> float:
        return self.width * self.height

    def perimeter(self) -> float:
        return 2 * (self.width + self.height)

def main():
    c = Circle(5)
    print("Circle area: ", c.area())
    print("Circle perimeter: ", c.perimeter())

    r = Rectangle(5, 10)
    print("Rectangle area: ", r.area())
    print("Rectangle perimeter: ", r.perimeter())

if __name__ == "__main__":
    main()