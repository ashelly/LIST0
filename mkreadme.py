#!/usr/local/bin/python3
md = open("README.md","w")
echo = False
f = open("l0.h")
if True:
  for line in f:
#    print(line)
    if "~~~*/" in line:
      echo = False
#      print(line,echo)
    if echo:
      md.write(line)
    if "/*~~~" in line:
      echo = True
md.close()

     
