# Using pyqt for pdf
from PyQt4.QtGui import QTextDocument, QPrinter, QApplication, QPainter
from PyQt4.QtCore import QSizeF

import sys
app = QApplication(sys.argv)

gurdasfile=open("GurdasKabit.json")
import json as js
read = gurdasfile.read()

jsondata=js.loads(read)

def GetKabitText(Number , Language):
    # The line numbers are in a dict so they are not sorted
    # Get then in order
    keys=jsondata[0][str(Number)][0].keys()
    sorted = map(lambda x: int(x),keys)
    sorted.sort()
    list = []
    for i in sorted:
         list.append(jsondata[0][str(Number)][0][str(i)][0][Language])
    return "\n".join(list)

def GetKabitTextList(Number , Language):
    # The line numbers are in a dict so they are not sorted
    # Get then in order
    keys=jsondata[0][str(Number)][0].keys()
    sorted = map(lambda x: int(x),keys)
    sorted.sort()
    list = []
    #print sorted
    for i in sorted:
         # check language availabilty in the keys
         languages_available = jsondata[0][str(Number)][0][str(i)][0].keys()
         if Language in languages_available :
             text = jsondata[0][str(Number)][0][str(i)][0][Language]
         else:
             text = "--"
         list.append(text)
      
    return list

# HTML Functions for generating ebook
def AddHTMLTag(str,tag):
    return "<" + tag +">" + str + "</" + tag +">"

def AddHead(str):
    return AddHTMLTag(str,"head")

def AddBody(str):
    return AddHTMLTag(str,"body")

def TextSize(str,fontsize):
    return "<font size=%s> %s </font>" % (fontsize,str) 

def Bold(str):
    return AddHTMLTag(str,"b")

def Italics(str):
    return AddHTMLTag(str,"i")

def Center(str):
    return AddHTMLTag(str,"center")

def link(str,link):
    return "<a href=%s>%s</a>" % (link,str)

# SHortcuts for languages
Pun=u"punjabi"
Hin=u"hindi"
Tr=u"english"
Ro=u"roman"

# Preparing the pdf
doc = QTextDocument()

printer = QPrinter()
printer.setOutputFileName("KabitGurdas2.pdf")
printer.setOutputFormat(QPrinter.PdfFormat)
printer.setPaperSize(QPrinter.A4);
	# page margin

printer.setPageMargins(12, 16, 12, 20, QPrinter.Millimeter)
doc.setPageSize(QSizeF(printer.pageRect().size()))

# We have a database of 675 kabits
KabitRange = range(1,676)
html=[1] * KabitRange.__len__()
ch = [1] * KabitRange.__len__()

count=0

painter = QPainter()
painter.begin( printer )	

for KabitNumber in KabitRange:
#	print KabitNumber
	Plist=GetKabitTextList(KabitNumber,Pun)
	Elist=GetKabitTextList(KabitNumber,Tr)
	
	Title="Kabit " + str(KabitNumber)
	
	# Generate HTML with Poem data
	htmllist=[]
	
	htmllist.append(AddHTMLTag(Center(AddHTMLTag(Bold(TextSize(Title,5)),"p")),"h1"))
	htmllist.append(Center(Bold(TextSize("\n\n",10))))
	htmllist.append(Center(Bold(TextSize("Gurmukhi",10))))
	# Add punjabi portion to html
	for num,name in enumerate(Plist):
		htmllist.append(Center(AddHTMLTag(TextSize(Plist[num],4),"p")))

	# Add english translation to html
	htmllist.append(Center(Bold(TextSize("\n\nEnglish\n",10))))

    # max numbers in one line then add <br> in "english" translation
	no_of_words = 20
	for num,name in enumerate(Plist):
		k = Elist[num].split()
		klen = k.__len__()
		t = klen/no_of_words
		for i in range(t):
			k.insert(no_of_words*(i+1),"<br>")
		strline = ' '.join(k)
		htmllist.append(AddHTMLTag(Center(Italics(TextSize(strline,3))),"p"))
		
	body=' '.join(htmllist)
	# Necessary for unicode rendering
	headuni="<meta http-equiv=\"Content-Type\" content=\"text\/html; charset=utf-8\">"
	
	html[count]= AddHead(headuni) + AddBody(body)

	# A new page
	printer.newPage()
	
	# Draw the first page removing the pageRect offset due to margins.
	doc.setHtml(html[count])
    # Create a QPainter to draw our content    
	
	doc.drawContents(painter)#,printer.pageRect().translated( -printer.pageRect().x(), -printer.pageRect().y() ))
	#QTextDocument.drawContents(QPainter, QRectF rect=QRectF())
	doc.print_(printer)

# Done.
painter.end()

