#!/usr/bin/python                                                                                                                                                                  

import sys, string, locale
from optparse import OptionParser


def main():
    locale.setlocale(locale.LC_ALL, 'C')
    version_msg = "%prog 2.0"                                                                                                                                                      
    usage_msg = "%prog [-123u] FILE1 FILE2"
    #deal with arguments parsing                                                                                                                                       
    parser = OptionParser(version=version_msg, usage=usage_msg)  
    parser.add_option("-u", action="store_true", dest="dashyou", default=0, help="use it if unsorted")
    parser.add_option("-1", action="store_true", dest="dashone", default=0, help="supress line 1")
    parser.add_option("-2", action="store_true", dest="dashtwo", default=0, help="supress line 2")
    parser.add_option("-3", action="store_true", dest="dashthree", default=0, help="supress line 3")
    options, args = parser.parse_args(sys.argv[1:])
    
    if len(args)!=2:
        parser.error("Error: Wrong number of arguments!")
    
    file1=args[0]
    file2=args[1]
    lines1 = []
    lines2 =[]
    if file2=="-":
        lines1=sys.stdin.readlines()

        try:
            f2 = open (file1, 'r')
            lines2 = f2.readlines()
            f2.close()
        except:
            parser.error("Error loading files")

    else:
        try:
            f1 = open (file1, 'r')
            f2 = open (file2, 'r')
            lines1 = f1.readlines()
            lines2 = f2.readlines()
            f1.close()
            f2.close()
        except:
            parser.error("Error loading files")
        
        
    dashyou=options.dashyou
    dashone=options.dashone
    dashtwo=options.dashtwo
    dashthree=options.dashthree


    columnumn1 = []
    column2 = []
    column3 = []

    #if sorted
    if dashyou==0:

        #if the files are not sorted but user indicates that they are sorted
        if lines1 != sorted(lines1) or lines2 != sorted(lines2):
            print ("Don't troll: Do not pretend or assume that they are sorted")


        
        column1=lines1
        column2=lines2
        for i in lines1:
            if i in lines2:
                column3.append(i)

        for i in column3:
            if i in column2:
                column2.remove(i)
        for i in column3:
            if i in column1:
                column1.remove(i)

        ans=sorted(column1+column2+column3)


        for i in ans:
            #write column 1
            if i in column1 and dashone!=1:
                sys.stdout.write(i)
        #write column 2
            if i in column2 and dashone!=1 and dashtwo!=1:
                sys.stdout.write("\t"+i)
            elif i in column2 and dashone==1 and dashtwo!=1:
                sys.stdout.write(i)
#below are all wiriting column 3
            if i in column3 and dashone!=1 and dashtwo!=1 and dashthree!=1:
                sys.stdout.write("\t\t"+i)
            elif i in column3 and dashone==1 and dashtwo!=1 and dashthree!=1:
                sys.stdout.write("\t"+i)
            elif i in column3 and dashone!=1 and dashtwo==1 and dashthree!=1:
                sys.stdout.write("\t"+i)
            elif i in column3 and dashone==1 and dashtwo==1 and dashhree!=1:
                sys.stdout.write(i)

    #if unsorted
    if dashyou==1:
        for i in lines1:
            if i in lines2:
                column3.append(i)

        for i in column3:
            if i in lines2:
                lines2.remove(i)
            
        #print line 1 and 3
        for i in lines1:
            #both in 1 n 2
            if i in column3 and dashone!=1 and dashtwo!=1 and dashthree!=1:
                sys.stdout.write("\t\t"+i)
            elif i in column3 and dashone==1 and dashtwo!=1 and dashthree!=1:
                sys.stdout.write("\t"+i)
            elif i in column3 and dashone!=1 and dashtwo==1 and dashthree!=1:
                sys.stdout.write("\t"+i)
            elif i in column3 and dashone==1 and dashtwo==1 and dashthree!=1:
                sys.stdout.write(i)
            #not in 2
            elif i not in column3 and dashone!=1:
                sys.stdout.write(i)
        #print line 2
        for i in lines2:
            if dashone!=1 and dashtwo!=1:
                sys.stdout.write("\t"+i)
            elif dashone==1 and dashtwo!=1:
                sys.stdout.write(i)
                                                                                                                                                                                                                                                                                                                    
if __name__ == "__main__":
    main()