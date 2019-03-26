#!/bin/bash

sudo apt -y update
sudo apt-get install -y libc6-dev g++-multilib python p7zip-full pwgen jq curl
cd ~

if [ -f supremecoin.zip ]
then
    rm supremecoin.zip
fi
wget -O supremecoin.zip `curl -s 'https://api.github.com/repos/supremecoin-pod/supremecoin/releases/latest' | jq -r '.assets[].browser_download_url' | egrep "supremecoin.+x64.zip"`
7z x -y supremecoin.zip
chmod -R a+x ~/supremecoin-pkg
rm supremecoin.zip

cd ~/supremecoin-pkg
./fetch-params.sh

if ! [[ -d ~/.supremecoin ]]
then
    mkdir -p ~/.supremecoin
fi

if ! [[ -f ~/.supremecoin/supremecoin.conf ]]
then
    echo "rpcuser=rpc`pwgen 15 1`" > ~/.supremecoin/supremecoin.conf
    echo "rpcpassword=rpc`pwgen 15 1`" >> ~/.supremecoin/supremecoin.conf
fi

./supremecoind
