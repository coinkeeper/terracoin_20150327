AM_CPPFLAGS =  $(INCLUDES)
AM_LDFLAGS = $(PTHREAD_CFLAGS)


if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(CXXFLAGS) $(CPPFLAGS)"
endif

TERRACOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS)

noinst_LIBRARIES = \
  libterracoin_server.a \
  libterracoin_common.a \
  libterracoin_cli.a
if ENABLE_WALLET
TERRACOIN_INCLUDES += $(BDB_CPPFLAGS)
noinst_LIBRARIES += libterracoin_wallet.a
endif

bin_PROGRAMS =
TESTS =

if BUILD_TERRACOIND
  bin_PROGRAMS += terracoind
endif

if BUILD_TERRACOIN_CLI
  bin_PROGRAMS += terracoin-cli
endif

.PHONY: FORCE
# terracoin core #
TERRACOIN_CORE_H = \
  addrman.h \
  alert.h \
  allocators.h \
  base58.h \
  bloom.h \
  chainparams.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  core.h \
  crypter.h \
  db.h \
  hash.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  miner.h \
  mruset.h \
  netbase.h \
  net.h \
  noui.h \
  protocol.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  script.h \
  serialize.h \
  sync.h \
  threadsafety.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  util.h \
  version.h \
  walletdb.h \
  wallet.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libterracoin_common_a-version.$(OBJEXT): obj/build.h

libterracoin_server_a_CPPFLAGS = $(TERRACOIN_INCLUDES)
libterracoin_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  checkpoints.cpp \
  coins.cpp \
  init.cpp \
  keystore.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  txdb.cpp \
  txmempool.cpp \
  $(JSON_H) \
  $(TERRACOIN_CORE_H)

libterracoin_wallet_a_CPPFLAGS = $(TERRACOIN_INCLUDES)
libterracoin_wallet_a_SOURCES = \
  db.cpp \
  crypter.cpp \
  rpcdump.cpp \
  rpcwallet.cpp \
  wallet.cpp \
  walletdb.cpp \
  $(TERRACOIN_CORE_H)

libterracoin_common_a_CPPFLAGS = $(TERRACOIN_INCLUDES)
libterracoin_common_a_SOURCES = \
  base58.cpp \
  allocators.cpp \
  chainparams.cpp \
  core.cpp \
  hash.cpp \
  key.cpp \
  netbase.cpp \
  protocol.cpp \
  rpcprotocol.cpp \
  script.cpp \
  sync.cpp \
  util.cpp \
  version.cpp \
  $(TERRACOIN_CORE_H)

if GLIBC_BACK_COMPAT
libterracoin_common_a_SOURCES += compat/glibc_compat.cpp
libterracoin_common_a_SOURCES += compat/glibcxx_compat.cpp
endif

libterracoin_cli_a_SOURCES = \
  rpcclient.cpp \
  $(TERRACOIN_CORE_H)

nodist_libterracoin_common_a_SOURCES = $(srcdir)/obj/build.h
#

# terracoind binary #
terracoind_LDADD = \
  libterracoin_server.a \
  libterracoin_common.a \
  $(LIBLEVELDB) \
  $(LIBMEMENV)
if ENABLE_WALLET
terracoind_LDADD += libterracoin_wallet.a
endif
terracoind_SOURCES = bitcoind.cpp
#

if TARGET_WINDOWS
terracoind_SOURCES += bitcoind-res.rc
endif

terracoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS)
terracoind_CPPFLAGS = $(TERRACOIN_INCLUDES)

# terracoin-cli binary #
terracoin_cli_LDADD = \
  libterracoin_cli.a \
  libterracoin_common.a \
  $(BOOST_LIBS)
terracoin_cli_SOURCES = bitcoin-cli.cpp
terracoin_cli_CPPFLAGS = $(TERRACOIN_INCLUDES)
#

if TARGET_WINDOWS
terracoin_cli_SOURCES += bitcoin-cli-res.rc
endif

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(CXXFLAGS)  -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

LIBTERRACOIN_SERVER=libterracoin_server.a
LIBTERRACOIN_WALLET=libterracoin_wallet.a
LIBTERRACOIN_COMMON=libterracoin_common.a
LIBTERRACOIN_CLI=libterracoin_cli.a
LIBTERRACOINQT=qt/libterracoinqt.a

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
