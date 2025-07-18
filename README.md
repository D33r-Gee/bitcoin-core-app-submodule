# Bitcoin Core App With Snapshot Support

Contains code authored by @pinheadmz and @johnny9.

This is an experimental build configuration that allows you to use the Bitcoin Core App with a snapshot of the Bitcoin Core blockchain.

Expirimental build configuration:

- bitcoin/bitcoin is included as a git submodule `bitcoin/`
- `qml/` directory is pulled from bitcoin-core/gui-qml
- `bitcoin-core-app` is built from both `bitcoin` and `qml` directories

Currently, tested on Ubuntu 22.04:

```
git clone https://github.com/D33r-Gee/bitcoin-core-app-submodule
cd bitcoin-core-app-submodule
git submodule update --init --recursive
cmake -B build
cmake --build build -j 8
build/bin/bitcoin-core-app
```

![Bitcoin Core App demo gif](doc/bitcoin-core-app.gif)