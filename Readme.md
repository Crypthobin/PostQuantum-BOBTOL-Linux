# Post-Quantum BOB-TOL
BOB-TOL is Based On Bitcoin, Toward Outlasting any Legacy.<br>
BOB-TOL is the safest and fastest cryptocurrency that can respond to quantum computers.
## Reference ##
- Website: (...)
- Whitepaper: (...)
## Guidelines ##
### Cloning a repository ###
```
git clone https://github.com/Crypthobin/PostQuantum-BOBTOL-Linux
```
### Build (Linux) ###
- You have to use C++17 or upper version
- Windows here: https://github.com/Crypthobin/PostQuantum-BOBTOL-Windows

#### 1) Dependency

Build requirements: <br>

### Ubuntu & Debian

``` d
sudo apt-get install build-essential libtool autotools-dev automake pkg-config bsdmainutils python3
```

``` 
sudo apt-get install libevent-dev libboost-system-dev libboost-filesystem-dev libboost-test-dev libboost-thread-dev
```

``` sudo apt install libsqlite3-dev
sudo apt install libsqlite3-dev
sudo apt-get install libminiupnpc-dev
sudo apt-get install libzmq3-dev
sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools
sudo apt-get install libqrencode-dev
```

### Fedora

``` 
sudo dnf install gcc-c++ libtool make autoconf automake libevent-devel boost-devel libdb4-devel libdb4-cxx-devel python3
sudo dnf install miniupnpc-devel
sudo dnf install zeromq-devel
```

``` 
sudo dnf install qt5-qttools-devel qt5-qtbase-devel
sudo dnf install qrencode-devel
sudo dnf install sqlite-devel
```

#### 2) (Optional) Data Directory ####

- Default data directory is "~/.bitcoin"
- Create directory what you want to use data directory for BOBTOL
- If you want to change default directory, copy and paste "BOBTOL/Src/BOBTOL-Linux/share/examples/bitcoin.conf" into "~/.bitcoin"
- Add the content below to "~/.bitcoin/bitcoin.conf"

```
# Options only for pqcnet
[pqcnet]
datadir=<your data directory> # This is the path of the data folder you created.
```
- example : datadir=~/BOBTOL/Src/BOBTOL-Linux/data

#### 3) Berkeley DB

- run install_db4.sh in Src/BOBTOL-Linux/contrib
- example : ./install_db4.sh "directory you want"
- memo BDB_PREFIX when running install_db4.sh is done

#### 4) To Build

- Run shell and makefile

``` 
cd BOBTOL/Src/BOBTOL-Linux
./autogen.sh
export BDB_PREFIX='your bdb directory what you memo in 3) Berkeley DB'
./configure BDB_LIBS="-L${BDB_PREFIX}/lib -ldb_cxx-4.8" BDB_CFLAGS="-I${BDB_PREFIX}/include"
make
make install # optional
./exec.sh
```

#### 5) Start BOBTOL

- In BOBTOL/Src/BOBTOL-Linux/exec , bobtold is daemon fie 
- bobtol-cli is file that you can command to bobtol
- You have to run bobtold first, and then you can use bobtol-cli
- example

``` 
./bobtold
./bobtol-cli createwallet "wallet"
```

