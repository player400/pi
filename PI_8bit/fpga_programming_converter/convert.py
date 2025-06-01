filename = input()

extension = filename.split('.')[-1]

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
    
mem = ""
for i in range(1, len(hex_list)):
    mem = hex_list[i] + mem
    
for i in range(len(hex_list), 257):
    mem = "00" + mem

print("Program image: ", mem)