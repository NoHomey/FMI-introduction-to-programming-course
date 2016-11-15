{ execSync } = require 'child_process'
{ writeFileSync } = require 'fs'

outputDir = 'out'
begin = '/* @begin */'
std = '#include <iostream>\nusing namespace std;\n'
format = 'clang-format -style=Google'
encoding = 'utf8'

generate = (task) ->
    rawCode = execSync "g++ -E -C task#{task}.cc", encoding: encoding
    code =  (rawCode.substring rawCode.indexOf begin).replace begin, std
    writeFileSync "#{outputDir}/fn45342_prob#{task}_gcc.cpp", execSync format, encoding: encoding , input: code

execSync "mkdir -p #{outputDir}"
generate task for task in [1..10]