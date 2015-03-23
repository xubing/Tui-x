import Image

def resize_pic(inPath,outPath,resize):
    im = Image.open(inPath)  
    im = im.resize(resize)
    im.save(outPath)

def split_pic(inPath,outDir,row,col,cellWight,cellHeight):
    im = Image.open(inPath)  
    
    for r in range(row):
    	for c in range(col):
    		 box = (c * cellWight, r * cellHeight,(c + 1) * cellWight ,(r + 1) * cellHeight)
    		 im.crop(box).save(outDir+'\img_m_{0}_{1}.png'.format(r,c)) 



def main():
    inPath  = "G:\workspace\Tui-x\CocosWidgetTestCpp\Resources\scrollcontent.png"
    outPath = "G:\workspace\Tui-x\HelloTuiCpp\Resources\map\img_map.png"
    outDir = "G:\workspace\Tui-x\HelloTuiCpp\Resources\map\\tile"
    row = 16
    col = 16
    resize = (1024, 1024)
    cellWight = 64
    cellHeight = 64

    resize_pic(inPath,outPath,resize)
    split_pic(outPath,outDir,row,col,cellWight,cellHeight)

if __name__ == '__main__':
    main()