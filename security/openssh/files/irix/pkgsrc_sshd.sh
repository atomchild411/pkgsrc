#!/bin/sh
##
## Start or stop OpenSSH from @PREFIX@ (the pkgsrc openssh package).
##
## Off until you turn it on:  chkconfig pkgsrc_sshd on
## (and off an older sshd that wants port 22 too, e.g. chkconfig fw_sshd off).
## Custom sshd options go in /etc/config/pkgsrc_sshd.options.
##
## Host keys are made on the first start if there are none.  Where there is
## no /dev/urandom (IRIX 6.5.7; 6.5.22 has one, and sshd reads it directly)
## sshd needs an EGD/PRNGD socket at @SSH_PID_DIR@/egd-pool: an egd.pl in
## @PREFIX@/libexec is started for it if there is one.
##
## Installed by the openssh package from
## @PREFIX@/share/examples/openssh/irix/pkgsrc_sshd; removed with the package
## unless you have changed it.

IS_ON=/etc/chkconfig
CONFIG=/etc/config
SSHD=@PREFIX@/sbin/sshd
KEYGEN=@PREFIX@/bin/ssh-keygen
SSHDIR=@PKG_SYSCONFDIR@
PIDFILE=@SSH_PID_DIR@/sshd.pid
EGD=@PREFIX@/libexec/egd.pl
POOL=@SSH_PID_DIR@/egd-pool
PERL=/usr/freeware/bin/perl
[ -x $PERL ] || PERL=/usr/sbin/perl           # IRIX's own perl 5.004

egd_pids() {
    /bin/ps -ef | /usr/bin/awk '/egd\.pl/ && !/awk/ { print $2 }'
}

start_egd() {
    if [ -c /dev/urandom ] || [ -n "`egd_pids`" ]; then
        return
    fi
    if [ ! -r $EGD ]; then
        echo "pkgsrc_sshd: no /dev/urandom and no $EGD: sshd will have no entropy" >&2
        return
    fi
    /bin/rm -f $POOL
    $PERL $EGD $POOL < /dev/null > /dev/null 2>&1 &
    n=0
    while [ ! -S $POOL -a $n -lt 10 ]; do
        sleep 1
        n=`expr $n + 1`
    done
}

make_keys() {
    for k in $SSHDIR/ssh_host_*_key; do
        [ -f "$k" ] && return
    done
    $KEYGEN -A
}

start_sshd() {
    if [ -r $CONFIG/pkgsrc_sshd.options ]; then
        $SSHD `cat $CONFIG/pkgsrc_sshd.options`
    else
        $SSHD
    fi
}

# Only the listening sshd of this package (by its pid file): sessions and
# any other sshd on the machine are left alone.
stop_sshd() {
    if [ -r $PIDFILE ]; then
        kill -TERM `cat $PIDFILE` 2> /dev/null
        /bin/rm -f $PIDFILE
    fi
}

stop_egd() {
    pids=`egd_pids`
    if [ -n "$pids" ]; then
        kill -TERM $pids
    fi
}

case "$1" in
    start)
        if $IS_ON pkgsrc_sshd && test -x $SSHD; then
            start_egd
            make_keys
            start_sshd
        fi
        ;;

    restart)
        if $IS_ON pkgsrc_sshd && test -x $SSHD; then
            stop_sshd
            sleep 1
            start_egd
            make_keys
            start_sshd
        fi
        ;;

    stop)
        if $IS_ON pkgsrc_sshd; then
            stop_sshd
            stop_egd
        fi
        ;;

    *)
        echo "usage: $0 {start|stop|restart}"
        ;;
esac
