# Links #

* http://www.terracoin.org/ - project main website
* https://github.com/terracoin - project main repositoty
* http://sourceforge.net/projects/terracoin/ - sf mirror hosting files, code and soon discussion forum & eventually mailing lists.


# Development process #

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the
terracoin development team members simply pulls it.

Official Bitcoin patches are also regurlarly merged into Terracoin tree.

Newly developped features and additions are submitted to **dev** branch.

When an upcoming milestone is about to be released, code from "dev"
branch is merged into "release" branch, for testing.

Upon validation, "release" branch is merged into "master" branch,
tested again, and a new tag is created.

Feature branches ("feature-shortname") may eventually be created when two
or more developpers works on the same task.


# Build instructions #

    ./autogen.sh
    ./configure
    make -j 4


# Donations #

We now accept donations towards development and hosting costs :

TRC: 1LpnJb98gXwdzriYXnMe2qryW5915Ysg9a

BTC: 1JaqW8LyfShWaGRnDptF2rBkyMwYAW1aR2

