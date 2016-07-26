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

# Preparing the ebook
from ebooklib import epub

book = epub.EpubBook()

# set metadata
book.set_title('Kabit Sawaiye')
book.set_language('pun')

book.add_author('Author Bhai Gurdas Bhalla')

# define CSS style
style = 'BODY {color: white;}'
nav_css = epub.EpubItem(uid="style_nav", file_name="style/nav.css", media_type="text/css", content=style)
	
	# add CSS file
book.add_item(nav_css)

	# add default NCX and Nav file
book.add_item(epub.EpubNcx())
book.add_item(epub.EpubNav())

book.spine.append('nav')	
	
# We have a database of 675 kabits
KabitRange = range(1,676)
html=[1] * KabitRange.__len__()
ch = [1] * KabitRange.__len__()

#print "Shiva %s" % KabitRange.__len__()
count=0

for KabitNumber in KabitRange:
#	print KabitNumber
	Plist=GetKabitTextList(KabitNumber,Pun)
	Elist=GetKabitTextList(KabitNumber,Tr)

	Title="Kabit " + str(KabitNumber)

	# Generate HTML with Poem data
	htmllist=[]

	htmllist.append(AddHTMLTag(Center(AddHTMLTag(Bold(TextSize(Title,5)),"p")),"h1"))
	htmllist.append(Center(Bold(TextSize("\n\n",5))))
	htmllist.append(Center(Bold(TextSize("Gurmukhi",5))))
	# Add punjabi portion to html
	for num,name in enumerate(Plist):
		htmllist.append(Center(AddHTMLTag(Plist[num],"p")))
    
    # Add english translation to html
	htmllist.append(Center(Bold(TextSize("\n\nEnglish\n",5))))
	htmllist.append(AddHTMLTag("\n","p"))
	for num,name in enumerate(Plist):
    	#htmllist.append(Center(AddHTMLTag(Plist[num],"p")))
		htmllist.append(Italics(TextSize(Elist[num],3)))

	body=' '.join(htmllist)
	# Necessary for unicode rendering
	headuni="<meta http-equiv=\"Content-Type\" content=\"text\/html; charset=utf-8\">"

	html[count]= AddHead(headuni) + AddBody(body)

	chap_title="Kabit_"+ str(KabitNumber)
	file_name_='chap_'+ str(KabitNumber) + ".xhtml"

	# If you wish to save a html file
#	fhtml=open(file_name_,"wb")
#	fhtml.write(html[count].encode('utf-8'))
#	fhtml.close()

	# create chapter
	c1 = epub.EpubHtml(title=chap_title, file_name=file_name_)
	c1.content=html[count]

	book.add_item(c1)

	# basic spine
	book.spine.append(c1)
	
	count += 1

	# write to the file

epub.write_epub('test.epub', book, {})

