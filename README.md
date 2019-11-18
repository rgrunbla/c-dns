# C-DNS Library

WORK IN PROCESS - STILL IN DEVELOPMENT

Library that converts DNS transmission to C-DNS file format.

## Build

Basic instructions for build. This is not deploy process, it's intended just for development or testing.

    mkdir build
    cd build
    cmake ..
    make
    cd ..
    ./link_and_run_test.sh
    ./a.out

## TODO-List

**High priority**

* [ ] Enhance library interface
* [ ] Finalize file and block preamble

**Medium priotity**

* [ ] CBOR (*libcbor*) performance improve
* [ ] Replace `cmake` with autotools (`automake`)

**Low priority**

* [ ] Deploy
