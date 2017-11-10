import subprocess
import ast
from PIL import Image, ImageDraw
im = Image.new('RGBA', (400, 400), (0, 0, 0, 0))
draw = ImageDraw.Draw(im)

p = subprocess.Popen(['./run.sh'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
out, err = p.communicate()
for a in out.split('\n'):
    b = a.split()
    a1=0
    a2=0
    if (len(b)>2):
        if(b[0]=="xy"):
            b1=int(ast.literal_eval(b[1])*im.width/100)
            b2=int(ast.literal_eval(b[2])*im.height/100)
            # draw.line((a1, a2, b1,b2), fill="#FFFFFF")
            # draw.ellipse((b1-1,b2-1,b1+1,b2+1), fill="#FFFFFF")
            draw.point((b1,b2), fill="#FFFFFF")
            a1=b1
            a2=b2
im.show()
