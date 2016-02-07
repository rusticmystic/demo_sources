# This uses urllib2 and dowloads pdf files from a site

import urllib2

def check_url_valid(url):
    try:
        file_name = url.split("/")[-1]
        url_valid=urllib2.urlopen(url)
    except urllib2.HTTPError, e:
        url_valid = None
    except urllib2.URLError, e:
        url_valid = None
    except httplib.HTTPException, e:
        url_valid = None
    except Exception:
        url_valid = None
    ret = (url_valid,file_name) 
    return ret

def download_file(url_fd,file):
    
    file = open(file, 'wb')
    file.write(url_fd.read())
    file.close()
    print("Completed")

def main():
	pdf_folder="http://onlinetest.damsdelhi.com/document/SolutionPdf/"

	# We will keep the names of files in the list
	file_list=list()

	`#Prepare a list of urls
	for i in range(0,300):
		file_address=pdf_folder + str(i) + ".pdf"
		file_list.append(file_address)
    
	# check on each file
	#for name in file_list:
	for name in file_list:
		ret,file = check_url_valid(name)
		if ret is not None:
			print "Download %s as %s" % (name,file)
			download_file(ret,file) 

if __name__ == "__main__":
    main()
