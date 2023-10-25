from pulp import *

x1 = pulp.LpVariable("x1", lowBound=0)
x2 = pulp.LpVariable("x2", lowBound=0)
x3 = pulp.LpVariable("x3", lowBound=0)
x4 = pulp.LpVariable("x4", lowBound=0)
x5 = pulp.LpVariable("x5", lowBound=0)
x6 = pulp.LpVariable("x6", lowBound=0)

problem = pulp.LpProblem('0', pulp.const.LpMinimize)
problem += x1 + x2 + x3 + x4 + x5 + x6, "Функция цели"
problem += x6 + x1 >= 4,  "24-4"
problem += x1 + x2 >= 8,  "4-8"
problem += x2 + x3 >= 10, "8-12"
problem += x3 + x4 >= 7,  "12-16"
problem += x4 + x5 >= 12, "16-20"
problem += x5 + x6 >= 4,  "20-24"

problem.solve()
for var in problem.variables():
    print(var.name, '=', var.varValue)
print("z =", value(problem.objective))