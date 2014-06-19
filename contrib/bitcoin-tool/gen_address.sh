#!/bin/sh

# Create private key
openssl rand 32 > key.bin

# store private key in readable form:
hexdump -e '32/1 "%02X" "\n"' key.bin > key.priv.asc

#Convert private key to WIF (Wallet Import Format)
./bitcoin-tool \
        --network terracoin \
        --input-type private-key \
        --input-format raw \
        --input-file key.bin \
        --output-type private-key-wif \
        --output-format base58check \
        --public-key-compression uncompressed > key.priv.wif

# useful outputs:
# private-key-wif.base58check   (to import keypair into wallet)
# address.base58check     (public terracoin address)
# public-key.hex    (public key usable in wallet source (alertpubkey, ...) 
./bitcoin-tool \
            --network terracoin \
            --input-type private-key \
            --input-format raw \
            --input-file key.bin \
            --output-type all \
            --public-key-compression uncompressed > key.fulldump.txt




