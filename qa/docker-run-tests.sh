#!/bin/bash

set -e

docker build -f ./qa/Dockerfile.test -t sghx/supremecoin-test .
docker run -it --rm sghx/supremecoin-test ./qa/supremecoin/full_test_suite.py
docker run -it --rm sghx/supremecoin-test ./qa/pull-tester/rpc-tests.sh
