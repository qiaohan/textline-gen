import cv2

gt = {}
kk = ''
#for ll in open("segtrain.txt"):
for ll in open("test.txt"):
    l = ll.split()
    key = l[0].split('/')[-1]   
    gt[key] = [int(k) for k in l[1:]]
    kk = key
fname = kk
im = cv2.imread("test/"+fname)
print gt[fname]
for i in gt[fname]:
    im[:,i] = 0
cv2.imwrite(fname,im)
