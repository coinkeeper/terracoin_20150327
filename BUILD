#
# "dev-0.1.3" branch building instructions:
#

# fetching latest updates & tags:
cd /path/to/your/local/clone/
git checkout master
git pull --tags origin master

# headless client build:
cd src
make -f makefile.unix clean
nice make -f makefile.unix -j 4
strip terracoind

# qt client build:
cd /path/to/your/local/clone/
make clean
qmake USE_IPV6=-
nice make -j 4
strip terracoin-qt

