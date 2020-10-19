#!/bin/bash

shopt -s extglob

rm -vrf !("README.md"|"clean_this_dir.sh"|"user_config")
