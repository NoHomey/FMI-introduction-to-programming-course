{ execSync } = require 'child_process'
{ writeFileSync } = require 'fs'

outputDir = 'out'
begin = '/* @begin */'
std = '#include <iostream>\nusing namespace std;\n'
format = 'clang-format -style=Google'
encoding = 'ascii'
idnumber = 45342

generate = (task) ->
    rawCode = execSync "g++ -E -C task#{task}.cc", encoding: encoding
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
    code =  (rawCode.substring rawCode.indexOf begin).replace begin,  header + std
    writeFileSync "#{outputDir}/fn#{idnumber}_prob#{task}_gcc.cpp", execSync format, encoding: encoding , input: code

execSync "mkdir -p #{outputDir}"
generate task for task in [1..10]
