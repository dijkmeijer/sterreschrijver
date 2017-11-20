import subprocess
import ast
from PIL import Image, ImageDraw, ImageFont
im = Image.new('RGBA', (600, 600), (0,0,0, 0))
draw = ImageDraw.Draw(im)
f = 170
longitude=51.43075
p = subprocess.Popen(['./run.sh'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
out, err = p.communicate()
for a in out.split('\n'):
    b = a.split()
    a1=0
    a2=0
    l=im.height/2-int((90-longitude)*im.height/f)
    if (len(b)>1):
        if(b[0]=="xy"):
            b1=int(ast.literal_eval(b[1])*im.width/f)+im.width/2
            b2=im.height/2-int(ast.literal_eval(b[2])*im.height/f)
            # draw.line((a1, a2, b1,b2), fill="#FFFFFF")
            # draw.ellipse((b1-1,b2-1,b1+1,b2+1), fill="#FFFFFF")
            draw.point((b1,b2), fill="#FFFFFF")
            a1=b1
            a2=b2
        if(b[0]=="mid"):
            b1=int(ast.literal_eval(b[1])*im.width/f)+im.width/2
            b2=im.height/2-int(ast.literal_eval(b[2])*im.height/f)
            draw.line((b1, b2, im.width/2,im.height/2-(90-longitude)*im.height/f),fill="#003399")
            # font = ImageFont.truetype("arial.ttf", 15)
            draw.text((b1, b2), b[3]+" "+b[4],fill="#FE2E2E")
        if(b[0]=="top"):
            b1=int(ast.literal_eval(b[1])*im.width/f)+im.width/2
            b2=im.height/2-int(ast.literal_eval(b[2])*im.height/f)
            b3=int(ast.literal_eval(b[3])*im.width/f)+im.width/2
            b4=im.height/2-int(ast.literal_eval(b[4])*im.height/f)
            r1 = b3-b1
            r2 = b4-b2
            m1 = b1+r1/2.
            m2 = b2+r2/2.
            draw.line((b1, b2, b3, b4),fill="#ccff33")
            draw.line((m1, m2, m1-r2*5, m2+r1*5),fill="#993366")
        if(b[0]=="R"):

            R = int(ast.literal_eval(b[1])*im.height/f)
            print "R = ", R
            x1 = im.width/2 - R
            x2 = im.width/2 + R
            y1=l - R
            y2=l + R

            draw.ellipse((x1,y1,x2,y2),outline ="#993366");



    draw.line((im.width/2, 0, im.width/2,im.height),fill="#FE2E2E")
    draw.line((0, im.height/2, im.width,im.height/2),fill="#FE2E2E")
    draw.line((0, l, im.width,l),fill="#600000")
im.show()
