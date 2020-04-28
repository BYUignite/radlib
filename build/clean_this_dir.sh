
#!/bin/bash

shopt -s extglob

rm -vrf !("README"|"clean_this_dir.sh"|"user_config")
