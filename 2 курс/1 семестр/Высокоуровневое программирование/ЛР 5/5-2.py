from abc import ABC, abstractmethod

class Calculate(ABC):
    @abstractmethod
    def Calculate(self):
        pass

class ArithmeticMean(Calculate):
    def __init__(self, row):
        self.row = row
        
    def Calculate(self):
        return sum(self.row) / len(self.row)
        
    row = [int]

mean = ArithmeticMean([1, 2, 6])
print(mean.Calculate())
