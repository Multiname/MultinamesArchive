A = bool(int(input("A: ")))
B = bool(int(input("B: ")))
C = bool(int(input("C: ")))
print("F: " + str(((A == B) == C) or not A))
