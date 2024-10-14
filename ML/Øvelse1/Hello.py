from math import sqrt
print("Hello world")

def hypotanusen(a_val, b_val) -> float:
    c_val = sqrt(a_val**2 + b_val**2)
    return c_val

print("Input lenghts of shorter triangle sides: ")

a = float(input("a: "))
b = float(input("b: "))

c = hypotanusen(a, b)
print("The lenght of the hypotenusen is: ", c)
