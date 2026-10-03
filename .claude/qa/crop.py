import sys
from PIL import Image
# crop.py OUT x0 y0 x1 y1 scale IN...
out=sys.argv[1]; x0,y0,x1,y1,s=map(int,sys.argv[2:7]); fs=sys.argv[7:]
w,h=(x1-x0)*s,(y1-y0)*s; W=Image.new('RGB',(w*len(fs)+4*(len(fs)-1),h),'white')
for i,f in enumerate(fs): W.paste(Image.open(f).convert('RGB').crop((x0,y0,x1,y1)).resize((w,h),Image.NEAREST),(i*(w+4),0))
W.save(out)
