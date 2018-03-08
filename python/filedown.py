import httplib
conn = httplib.HTTPConnection("http://stage.paf.free.fr/Video/Logiciels/FLV-Parser-FLV-Extract/")
conn.request("HEAD", "/index.html")
r1 = conn.getresponse()
print r1
print dir(r1)
print r1.status, r1.reason
print r1.getheader('Content-Type') #类型
print r1.getheader('Content-Length') # 大小
print r1.getheader('Last-Modified') #修改时间
