#!/usr/bin/env python
#Author: Shivdeep Singh
#It decodes rap index and time index files (.idx and .rap)
#works on python 2.7 not compatible with python 3
import sys
import struct
#in RAP , we have 3 elems in struct: 64b, 32b, 32b, unpacked as QLI
#in timeindex we have 2 elems in struct:  64b, 64bit, unpacked as QQ

def conv_timeindex(set,i):
    unpacked=struct.unpack("QQ",set)
    pkt_time=unpacked[0]
    pktpos=unpacked[1]
    print "%8s." % i,"%10s" % unpacked[0]," %10s" % unpacked[1]

def conv_rapindex(set,i):
    unpacked=struct.unpack("QLI",set)
    pkt_time=unpacked[0]
    pktpos=unpacked[1]
    data=unpacked[2]
    print "%8s." % i,"%10s" % pkt_time,"%10s " % pktpos,"%10s" %data

def main(argv):
    filename=argv[0]
    index_dict={"rap":conv_rapindex,"idx":conv_timeindex}
    extn=str(filename.split(".")[1])

    conv=index_dict[extn]
    fd=open(filename,"rb")

    set=fd.read(16)
    i=0
    if extn=="idx":
        print "Decoding Time Index %s" % filename
        print "%8s %10s %10s" % (" S.No"," Time in ms"," No of Pkts")
    elif extn=="rap":
        print "Decoding RAP Index %s" % filename
        print "%8s %10s %10s %10s" % (" S.No"," Time in ms"," Pos in Pkt"," RapSize")
    while set:
        i=i+1
        conv(set,i)
        set=fd.read(16)
    #this causes
    fd.close

if __name__ == "__main__":
    main(sys.argv[1:])
