filename = input()

extension = filename.split('.')[-1]




def getSize(fileobject):
    fileobject.seek(0,2)
    size = fileobject.tell()
    return size

hex_list = []

if extension == 'hex':
    with open(filename, 'r') as fp:
        for line in fp:
            hex_list.extend(line.split())
if extension == 'bin':
    with open(filename,"rb") as f:
        block = f.read()
        hex_string = block.hex()
        hex_list = [hex_string[i:i + 2] for i in range(0, len(hex_string), 2)]
    
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