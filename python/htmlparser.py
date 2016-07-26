# coding: utf-8

# In[169]:

from HTMLParser import HTMLParser
from htmlentitydefs import name2codepoint

# HTML parser
class MyHTMLParser(HTMLParser):
	
    def handle_starttag(self, tag, attrs):
        print "Start tag:", tag
        if tag=="table":
                print "table start"
        for attr in attrs:
			print "     attr:", attr
       
                

    def handle_endtag(self, tag):
        print "End tag  :", tag
        if tag=="table":
                print "table end"
        pass

    def handle_data(self, data):
        print "Data     :", data
        #print "SHiva %s" % self.langindex
		#pass
    def handle_comment(self, data):
        #print "Comment  :", data
        pass
        
    def handle_entityref(self, name):
        #c = unichr(name2codepoint[name])
        #print "Named ent:", unicode(c)
        pass
        
    def handle_charref(self, name):
        #if name.startswith('x'):
        #    c = unichr(int(name[1:], 16))
        #else:
        #    c = unichr(int(name))
        #print "Num ent  :", c
        pass
        
    def handle_decl(self, data):
        #print "Decl     :", data
        pass


f = open("Kabir_0.htm")
data = f.read()

hp = MyHTMLParser()

hp.feed(data)
print "Hello"
