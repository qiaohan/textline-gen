import random
import codecs

words = []
for line in open("word_dict.txt"):
    w = line.split()[1].decode('utf-8').strip()
    words.append(w)

print len(words)
fout = codecs.open("random_corpus.txt","w","utf-8")
'''
k = 0
while k<len(words):
    length = random.randint(3,15)
    if length+k > len(words):
        length = len(words) - k
    tline = ""
    for j in range(length):
        tline += words[k+j]
    k += length
    fout.write(tline+'\n')
'''
for i in range(300000):
    tline = words[i%len(words)]
    for _ in range(random.randint(3,15)):
        tline += words[random.randint(0,len(words)-1)]
    fout.write(tline+'\n')

for i in range(300000):
    tline = words[i%len(words)]
    for _ in range(random.randint(1,4)):
        tline += words[random.randint(0,len(words)-1)]
    for j in range(random.randint(1,10)):
        tline += str( random.randint(0,100)%10 )
    for k in range(random.randint(1,4)):
        tline += words[random.randint(0,len(words)-1)]
    fout.write(tline+'\n')

fout.close()
