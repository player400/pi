hex_list = []
with open('hello_world.hex', 'r') as fp:
    for line in fp:
        hex_list.extend(line.split())
    
pc = hex_list[1]
alpha = hex_list[2]
beta = hex_list[3]
acc = hex_list[4]

gpr = ""
for i in range(5, 17):
    gpr = hex_list[i] + gpr 
    
mem = ""
for i in range(17, len(hex_list)):
    mem = hex_list[i] + mem
    
for i in range(len(hex_list), 257):
    mem = "00" + mem

print("Program counter: ", pc)
print("Alpha: ", alpha)
print("Beta: ", beta)
print("Accumulator: ", acc)
print("General Purpose Registers: ", gpr)
print("Memory: ", mem)