#! /bin/sh

aclocal \
&& automake --add-missing \
&& ./bootstrap \
&& autoconf

