const {readFileSync} = require('fs');

const data = readFileSync('data', {encoding: 'utf8'}).split('\n');

data.pop();

let stats = [];

for(let i = 1; i < 6; ++i) {
    stats[i] = 0;
}

for(grade of data) {
    stats[grade - 1]++;
}

for(let i = 1; i < 6; ++i) {
    console.log(`${i + 1}: ${stats[i]}`);
}
