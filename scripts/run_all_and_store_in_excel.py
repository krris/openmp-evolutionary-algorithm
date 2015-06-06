import xlwt
import subprocess
import sys
import os

repeat_no = 2
book = xlwt.Workbook(encoding="utf-8")
sheet = book.add_sheet("Sheet 1")

excel_file = sys.argv[1]
print "Excel file: " + excel_file

program = sys.argv[2]
print "Program name: " + program

initialPopulation=10000
tempPopulation=20000
epsilon=0.2
N=100

generations = [1000, 2000, 3000, 4000, 5000] 

col = 0
for gen in generations: 
    for i in range(repeat_no):
        print(gen)
        process = subprocess.Popen(
            ['/home/krris/mgr/openmp-evolutionary-algorithm-results/build/' + program, str(gen), str(initialPopulation), str(tempPopulation), str(epsilon), str(N), 'parallel'],
             stdout=subprocess.PIPE)
        out, err = process.communicate()
        time = out.split('\n')[3]
        print(time)

        if i == 0:
            sheet.write(0, col, gen)
        sheet.write(i + 1, col, time)

    col += 1

book.save(excel_file)
