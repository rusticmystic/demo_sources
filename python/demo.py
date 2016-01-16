#!/usr/bin/env python
# Shivdeep Singh

import sys
import getopt

#Basic script to refresh all python concepts

#-----------------------------------------------------------#
#flatten lists of lists as 
#
#-----------------------------------------------
#simulating switch_case
def opt1():
    print "option 1:"

def opt2():
    print "option 2:"
    
def default():
    print "default option"

def switch_case():
    myoptions={"option1":opt1,"option2":opt2}
    #the options may call functions opt1, opt2 or default
    chooseoption="option1"
    chooseoption_1="option3"
    # this is the way to see the options in the dictionary and call the req function
    myoptions.get(chooseoption,default)()
    #this calls default, because option is not in the dictionary
    myoptions.get(chooseoption_1,default)()
 
#--------------------------------------------------------
# read a file to a list of words, also has function to flatten lists
def read_to_list(fd):
   #read all lines, as list of strings
   list_of_strings_line=fd.readlines()
   #split strings to lists, resultant list of a lists of words
   list_list_of_strings_wrd=map( lambda x: x.split(),list_of_strings_line)
   #flatten to a single list
   list_of_words=[item for sublist in list_list_of_strings_wrd for item in sublist]
   return list_of_words

#lamda
def demo_lambda():
    #using lambda functions
    # we have three functions to iterate over lists
    # map, filter and reduce, they take in input: a list and a function to use over each element
    #we can set lamda function, inline fn, for them
    
    list_for_hex=[2,9,"a","a14",87]
    #representing them as hex
    hx=lambda x: "0x"+str(x)
    #removing 0x from them and convert to decimal
    ihx=lambda x: int(x.split("x")[1],16)
    
    #add 0x before list
    hexp=map(hx,list_for_hex)
    print hexp
    #reconvert to decomal
    decp=map(ihx, hexp)
    print decp
    foo = [2, 18, 9, 22, 17, 24, 8, 12, 27]
    print filter(lambda x: x % 3 == 0, foo)
#-----------------------------------------------------------#
#demo of if and else
def demo_conditional():
	print "\n Demo conditional\n"
	mylist = [1,2,3,4, 5]
	print mylist
	print "checking if 5 is in the list"
	#can also be used in form:-> if (var == 12):
	if 5 in mylist:
		print "yes"
	else:
		print no
	#deleting the variable
	del mylist


#-----------------------------------------------------------#
#demo of looping and switching
def loopme():
	listis = [1,2,3,4,5]
	for i in listis:
		print "The number is", str(i)
	list2=[1,2,"mylist","mountain"]
	for num,name in enumerate(listis):
		print num,name


#-----------------------------------------------------------#
def demo_inputs():
	str = raw_input("Enter your input: ");
	print "Received input is : ", str
#-----------------------------------------------------------#
def simple_write_to_file():
	fo = open("shiv_p.txt","wb")
	fo.write("\n I have written this \n")
	mylist=[1,2,3,4]
	#convert list to strings before writing
	fo.write(str(mylist))
	fo.close()
#-----------------------------------------------------------#
def readfile():
	fo = open("demo.py","rb");
	#reads file to list
	#listread = fo.readlines()
	#print listread
	
	str = fo.read(10);
	print "Read String is : ", str
	#reads from current position upto newline character
	str = fo.readline()
	print "Reading Line  : ", str
	# Check current position
	position = fo.tell();
	print "Current file position : ", position

	# Reposition pointer at the beginning once again
	position = fo.seek(0, 0);
	str = fo.read(10);
	print "Again read String is : ", str
	# Close opend file
	fo.close()
#-----------------------------------------------------------#
#dictionary usage
def dict_usage():
	mydict = {"jan":"raman","feb":"harjap","march":"chakkoo","April":"Rohit"}
	#mydict.keys give a list of keys
	for i in mydict.keys():
		print mydict[i], " was born in ",i.upper()
	#use dictionary for swicth case , can keep function names as values also

#--------------------------------------------------------------#
#demo socket server
def socket_server():
	#import library
	import socket
	#create a socket object
	mysoc = socket.socket()
	#create and address tuple for the socket to bind.
	#(host_ip,port)
	host = socket.gethostname() # Get local machine name
	port = 12000
	addr_tuple=(host,port)
	
	#bind the socket to address
	mysoc.bind(addr_tuple)
	
	#Listen to socket and accept connections
	mysoc.listen(5)                 # Now wait for client connection.
	
	while True:
        connection = mysoc.accept()
        print 'Got connection from', addr
        connection.send('Thank you for connecting')
        connection.close()                # Close the connection
	
#demo socket client
def socket_client():
	import socket               # Import socket module
	s = socket.socket()         # Create a socket object
	host = socket.gethostname() # Get local machine name
	port = 12345                # Reserve a port for your service.
	s.connect((host, port))
	print s.recv(1024)
	s.close   

#---------------------------------------------------------------#
#simple Thread
#using Thread module
def thread_function(msg):
	print "My thread"

def demo_thread():
	thread.start_new_thread( thread_functtion, ('Message', ))
#-----------------


# thread with more features using threading module

#-----------------------------------------------------------#
def main(argv):
	print "This is the basic script for python reference"
	print 'Number of arguments:', len(sys.argv), 'arguments.'
	print 'Argument List:', str(sys.argv)
	demo_inputs()
	simple_write_to_file()
	readfile()
	demo_conditional()
	loopme()
	dict_usage()
	demo_lambda()
	
if __name__ == "__main__":
	main(sys.argv[1:])
