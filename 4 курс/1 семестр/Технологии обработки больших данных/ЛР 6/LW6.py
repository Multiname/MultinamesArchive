import matplotlib.pyplot as plt

f = open('cosineMeasure.txt')
lines = f.readlines()
lines = [line[:-1] for line in lines]
points = []
for line in lines:
        temp = line.split(' : ')
        clusterId = int(temp[1])
        temp = temp[0].split(", ")
        temp[0] = float(temp[0])
        temp[1] = float(temp[1])
        temp.append(clusterId)
        points.append(temp)

plt.grid()
colors = ['red', 'blue']
for point in points:
        plt.scatter(point[0], point[1], c=colors[point[2]])
    
plt.title("cosineMeasure")
plt.show()

f = open('manhattanMeasure.txt')
lines = f.readlines()
lines = [line[:-1] for line in lines]
points = []
for line in lines:
        temp = line.split(' : ')
        clusterId = int(temp[1])
        temp = temp[0].split(", ")
        temp[0] = float(temp[0])
        temp[1] = float(temp[1])
        temp.append(clusterId)
        points.append(temp)

plt.grid()
colors = ['red', 'blue']
for point in points:
        plt.scatter(point[0], point[1], c=colors[point[2]])
    
plt.title("manhattanMeasure")
plt.show()
