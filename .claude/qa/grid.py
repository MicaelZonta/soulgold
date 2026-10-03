import sys
from PIL import Image
fs=sys.argv[2:]; out=sys.argv[1]
cols=min(3,len(fs)); rows=(len(fs)+cols-1)//cols
W=Image.new('RGB',(240*cols,160*rows))
for i,f in enumerate(fs): W.paste(Image.open(f).convert('RGB'),(240*(i%cols),160*(i//cols)))
W.save(out)
