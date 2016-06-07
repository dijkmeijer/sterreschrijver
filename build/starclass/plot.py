from PIL import Image
from operator import itemgetter
import fileinput
im=Image.new('RGB', (600,600), "white")
pixels=im.load()
a=[]
for line in fileinput.input():
    num=line.split()
    if num[0] == 'c':
    # print  float(num[0]), float(num[1])
		a.append((float(num[1]),float(num[2])))
    if num[0] == 't':
		print num[1]    
    if num[0] == 'r':
		print num[1],num[2],num[3],num[4]
xmax = max(a, key=itemgetter(0))[0]
xmin =  min(a, key=itemgetter(0))[0]
ymax =  max(a, key=itemgetter(1))[1]
ymin =  min(a, key=itemgetter(1))[1]

xsize = xmax-xmin
ysize = ymax-ymin
width, height = im.size
xscale = width/xsize
yscale = height/ysize
if xscale < yscale:
	scale = xscale*0.95
else:
	scale = yscale*0.95



#print a
for n in a:
	#print (int((n[0]-xmin)*scale)+5,(int((n[1]-ymin)*scale))+5)
	pixels[(int((n[0]-xmin)*scale)+5,(int((n[1]-ymin)*scale))+5)]=(0,0,0)
#	pixels[(int(((n[0])))),(int(((n[1]))))]=(0,0,0)
im.show()


