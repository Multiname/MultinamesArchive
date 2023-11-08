from docplex.mp.model import Model

m = Model()
x_1 = m.integer_var(name='x_1', lb=0)
x_2 = m.integer_var(name='x_2', lb=0)

m.add_constraint(2 * x_1 + 5 * x_2 >= 12)
m.add_constraint(5 * x_1 + 2 * x_2 >= 14)

m.minimize(3 * x_1 + 4 * x_2)

c = m.get_cplex()
c.parameters.simplex.limits.iterations.set(100)
c.parameters.lpmethod.set(c.parameters.lpmethod.values.primal)

while c.solution.get_status() != c.solution.status.optimal:
    c.solve()
    print("=== Симплекс-таблица ===")
    for tableau_row in c.solution.advanced.binvarow():
        print(tableau_row)

m.solve()
print("\n=== Решение задачи, где x_1 - целое, а x_2 - целое ===")
m.print_solution()
