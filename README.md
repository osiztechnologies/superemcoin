# Supremecoin
**Keep running wallet to strengthen the Supremecoin network. Backup your wallet in many locations & keep your coins wallet offline.**

### Ports:
- RPC port: 2332
- P2P port: 12342

Install
-----------------
### Linux

### [Quick guide for beginners](https://github.com/supremecoin-pod/supremecoin/wiki/Quick-guide-for-beginners)

Get dependencies
```{r, engine='bash'}
sudo apt-get install \
      build-essential pkg-config libc6-dev m4 g++-multilib \
      autoconf libtool ncurses-dev unzip git python \
      zlib1g-dev wget bsdmainutils automake
```

Install

```{r, engine='bash'}
# Clone Supremecoin Repository
git clone https://github.com/sghx/supremecoin
# Build
cd supremecoin/
./zcutil/build.sh -j$(nproc)
# fetch key
./zcutil/fetch-params.sh
# Run
./src/supremecoind
# Test getting information about the network
cd src/
./supremecoin-cli getmininginfo
# Test creating new transparent address
./supremecoin-cli getnewaddress
# Test creating new private address
./supremecoin-cli z_getnewaddress
# Test checking transparent balance
./supremecoin-cli getbalance
# Test checking total balance 
./supremecoin-cli z_gettotalbalance
# Check all available wallet commands
./supremecoin-cli help
# Get more info about a single wallet command
./supremecoin-cli help "The-command-you-want-to-learn-more-about"
./supremecoin-cli help "getbalance"
```

### Docker

Build
```
$ docker build -t sghx/supremecoin .
```

Create a data directory on your local drive and create a supremecoin.conf config file
```
$ mkdir -p /ops/volumes/supremecoin/data
$ touch /ops/volumes/supremecoin/data/supremecoin.conf
$ chown -R 999:999 /ops/volumes/supremecoin/data
```

Create supremecoin.conf config file and run the application
```
$ docker run -d --name supremecoin-node \
  -v supremecoin.conf:/supremecoin/data/supremecoin.conf \
  -p 2342:2342 -p 127.0.0.1:2332:2332 \
  sghx/supremecoin
```

Verify supremecoin-node is running
```
$ docker ps
CONTAINER ID        IMAGE                  COMMAND                     CREATED             STATUS              PORTS                                              NAMES
31868a91456d        sghx/supremecoin          "supremecoind --datadir=..."   2 hours ago         Up 2 hours          127.0.0.1:2332->2332/tcp, 0.0.0.0:2342->2342/tcp   supremecoin-node
```

Follow the logs
```
docker logs -f supremecoin-node
```

The cli command is a wrapper to supremecoin-cli that works with an already running Docker container
```
docker exec -it supremecoin-node cli help
```

## Using a Dockerfile
If you'd like to have a production btc/supremecoin image with a pre-baked configuration
file, use of a Dockerfile is recommended:

```
FROM sghx/supremecoin
COPY supremecoin.conf /supremecoin/data/supremecoin.conf
```

Then, build with `docker build -t my-supremecoin .` and run.

### Windows
Windows build is maintained in [supremecoin-win project](https://github.com/supremecoin-pod/supremecoin-win).

Security Warnings
-----------------

**Supremecoin is experimental and a work-in-progress.** Use at your own risk.
