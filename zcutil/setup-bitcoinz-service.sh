#!/bin/bash

if [ $# -eq 0 ]
then
    echo "Supremecoin systemd unit setup."
    echo -e "Run:\n$0 user\nor install for current user\n$0 $USER"
    exit 1
fi

if id "$1" >/dev/null 2>&1
then
    echo "Installing Supremecoin service for $1 user..."
else
    echo -e "User $1 does not exist.\nTo add user run the following command:\nsudo adduser --disabled-password --gecos '' $1"
    exit 1
fi

cat > /tmp/config_setup.sh << EOF
#!/bin/bash
if ! [[ -d ~/.supremecoin ]]
then
    mkdir -p ~/.supremecoin
fi

if ! [[ -f ~/.supremecoin/supremecoin.conf ]]
then
    echo "rpcuser=rpc`pwgen 15 1`" > ~/.supremecoin/supremecoin.conf
    echo "rpcpassword=rpc`pwgen 15 1`" >> ~/.supremecoin/supremecoin.conf
fi
EOF
chmod +x /tmp/config_setup.sh
sudo -H -u $1 /tmp/config_setup.sh
sudo -H -u $1 ~/supremecoin-pkg/fetch-params.sh


cat > /etc/systemd/system/supremecoin.service << EOF
[Unit]
Description=supremecoin

[Service]
ExecStart=`cd ~; pwd`/supremecoin-pkg/supremecoind
User=$1
Restart=always


[Install]
WantedBy=multi-user.target
EOF

systemctl daemon-reload
systemctl enable supremecoin
systemctl start supremecoin

systemctl status supremecoin
