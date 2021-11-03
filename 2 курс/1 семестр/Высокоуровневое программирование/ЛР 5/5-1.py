class People:
    def __init__(self):
        self.names = [str]

    names = [str]


class Students(People):
    def __init__(self):
        self.esitames = [int]

    def ChangeEstimate(self, index, estimate):
        if estimate > 0 and estimate < 6:
            self.estimates[index] = estimate

    def WriteEstimates(self):
        print('\n'.join("{}: {}".format(self.names[index], self.estimates[index]) for index in range(len(self.names))))
        
    estimates = [int]

arr = Students()
arr.names = ["Kate", "Bob", "Mike"]
arr.estimates = [5, 3, 4]
arr.WriteEstimates()
