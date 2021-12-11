#!/bin/bash

rm -rf exec

mkdir exec
cd src
cp bitcoind ../exec
cp bitcoin-cli ../exec

cd ../exec
mv bitcoind bobtold
mv bitcoin-cli bobtol-cli
