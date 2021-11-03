from abc import ABC, abstractmethod
import math

class Triangle:
    @abstractmethod
    def FindPerimeter(self):
        pass

    @abstractmethod
    def FindSquare(self):
        pass
    
    firstSide = float
    secondSide = float
    angle = float

class RectangularTriangle:
    def FindPerimeter(self):
        return firstSide + secondSide + math.tan(angle) * secondSide

    def FindSquare(self):
        return 0.5 * secondSide * math.tan(angle) * secondSide

class IsoscelesTriangle:
    def FindPerimeter(self):
        return 2 * firstSide + secondSide

    def FindSquare(self):
        return 0.5 * firstSide * math.sin(angle) + secondSide

class EquilateralTriangle:
    def FindPerimeter(self):
        return 3 * firstSide

    def FindSquare(self):
        return firstSide**2 * 3**0.5 / 4
