import sys
def convert(string):
    li = list(string.split(" "))
    return li
file=open(sys.argv[1],"r")
info=file.readlines()
print(info)