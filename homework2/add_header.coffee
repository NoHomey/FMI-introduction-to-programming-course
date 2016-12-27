{ execSync } = require 'child_process'
{ writeFileSync, existsSync, readFileSync } = require 'fs'

outputDir = 'out'
format = 'clang-format -style=Google'
encoding = 'ascii'
idnumber = 45342

generate = (task) ->
    file = "task#{task}.cc"
    if existsSync file
        code = readFileSync file, encoding
        header = "
/**
\n*  
\n* Solution to homework task
\n* Introduction to programming course
\n* Faculty of Mathematics and Informatics of Sofia University
\n* Winter semester 2016/2017
\n*
\n* @author Ivo Stratev
\n* @idnumber #{idnumber}
\n* @task #{task}
\n* @compiler GCC
\n*
\n*/
\n
\n"
        outputFile = "#{outputDir}/fn#{idnumber}_prob#{task}_gcc.cpp"
        writeFileSync outputFile, execSync format, encoding: encoding , input: header + code 

execSync "mkdir -p #{outputDir}"
generate task for task in [1..10]