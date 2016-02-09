# centreon-connectors Debian packge build

This repository allows you to build Debian packages for the
[centreon-connectors](https://github.com/centreon/centreon-connectors).

Please note that you need to install
[libcentreon-clib-dev](https://github.com/centreon-deb/centreon-clib/tree/debian)
before building *centreon-connectors*.

## How to build in 3 commands

First you need to install
[git-deb-pkg](https://github.com/renard/git-deb-pkg) git plugging that will
help you to build the package. Then you just need to run:

    git clone https://github.com/centreon-deb/centreon-connectors.git
    cd centreon-connectors/
    git deb-pkg -C -U -u 1.1.1 -d origin/debian  build

## How to build the hard way

If you don't want to install *git-deb-pkg* you can run following and you
want to build the last version of the Debian package (1.1.1 at time of
writing), you need to run:

    git clone https://github.com/centreon-deb/centreon-connectors.git
    cd centreon-connectors/
	git checkout -b build 1.1.1
	git checkout origin/debian -- ./debian
	git archive --format=tar --prefix="$(basename `pwd`).orig/" \
        1.1.1 | gzip > "../$(basename `pwd`)_1.1.1.orig.tar.gz"
	debuild -I.git -i'\.git/'

Once the package is built, you can clean the repository and switch back to
the *master* branch:

	debuild clean
	git reset --hard HEAD
	git checkout master

Are you sure you don't want to install *deb-git-pkg*?

# Copyright

Copyright © 2016 Sébastien Gross \<seb•ɑƬ•chezwam•ɖɵʈ•org\>.

Released under WTFPL (http://sam.zoy.org/wtfpl/COPYING).

Feel free to contact me if you want to participate.

Follow me on twitter https://twitter.com/renard_0

# Links

- https://centreon.com
- https://github.com/centreon/centreon-connectors
- https://github.com/centreon/centreon-connectors.git
