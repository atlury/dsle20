# Aplicações Embarcadas

Alguns exemplos de aplicações para sistemas embarcados, que normalmente possuem recursos limitados \(memória, processador, etc\):

* **Dropbear:** é um cliente e servidor SSH que possui aproximadamente 110KB
* **Thttpd:** é um servidor web com aproximadamente 88KB;
* **DIrectFB:** é uma biblioteca gráfica, útil para alguns sistemas embarcados possuem display LCD, possibilita exibir gráficos, desenhos e imagens, com apenas 1.4MB;
* **SQLite:** um sistema de banco de dados com apenas 250KB! 

Essas aplicações apenas ressaltam a eficiência do kernel linux, como é possível rodar um sistema completo e robusto com pouco hardware.

### **Busybox**

Uma outra aplicação, comumente utilizada em sistemas Linux embarcados é a **Busybox.** 

Normalmente, um sistema Linux necessita de um conjunto mínimo de ferramantas para funcionar, como por exemplo o _`init`_, `shell`, alguns utilitários para manipulação de arquivos e configuração do sistema ****e ****etc. 

Estas ferramentas representam, basicamente, todos o ferramental que o Linux Desktop carrega nativamente, através de seus binários que normalmente são fornecidos por diferentes projetos. Desta forma, se para utilizar estas ferramentas em um ambiente embarcado seria necessário sua integração, além do fato de não serem projetadas inicialmente para sistemas embarcados, não fornecem uma grande liberdade em termos de configuração e incluindo diversas funcionalidades que geralmente não usadas em embarcados.

Uma solução para isso é o **Busybox,** que é considerado o canivete suiço dos sistemas LInux embarcados. Ele combina as ferramentas UNIX mais utilizadas, otimizadas por tamanho em um único binário, retirando tudo aquilo desncessário e apresenta estas ferramentas de forma altamente configurável. 

A seguir uma lista de ferramentas contidas no **Busybox.**

> addgroup, adduser, adjtimex, ar, arp, arping, ash, awk, basename, bbconfig, bbsh, brctl, bunzip2, busy- box, bzcat, bzip2, cal, cat, catv, chat, chattr, chcon, chgrp, chmod, chown, chpasswd, chpst, chroot, chrt, chvt, cksum, clear, cmp, comm, cp, cpio, crond, crontab, cryptpw, cttyhack, cut, date, dc, dd, deallocvt, del- group, deluser, depmod, devfsd, df, dhcprelay, diff, dirname, dmesg, dnsd, dos2unix, dpkg, dpkg\_deb, du, dumpkmap, dumpleases, e2fsck, echo, ed, egrep, eject, env, envdir, envuidgid, ether\_wake, expand, expr, fakeidentd, false, fbset, fbsplash, fdflush, fdformat, fdisk, fetchmail, fgrep, find, findfs, fold, free, freeram- disk, fsck, fsck\_minix, ftpget, ftpput, fuser, getenforce, getopt, getsebool, getty, grep, gunzip, gzip, halt, hd, hdparm, head, hexdump, hostid, hostname, httpd, hush, hwclock, id, ifconfig, ifdown, ifenslave, ifup, inetd, init, inotifyd, insmod, install, ip, ipaddr, ipcalc, ipcrm, ipcs, iplink, iproute, iprule, iptunnel, kbd\_mode, kill, killall, killall5, klogd, lash, last, length, less, linux32, linux64, linuxrc, ln, load\_policy, loadfont, loadkmap, logger, login, logname, logread, losetup, lpd, lpq, lpr, ls, lsattr, lsmod, lzmacat, makedevs, man, match- pathcon, md5sum, mdev, mesg, microcom, mkdir, mke2fs, mkfifo, mkfs\_minix, mknod, mkswap, mktemp, modprobe, more, mount, mountpoint, msh, mt, mv, nameif, nc, netstat, nice, nmeter, nohup, nslookup, od, openvt, parse, passwd, patch, pgrep, pidof, ping, ping6, pipe\_progress, pivot\_root, pkill, poweroff, printenv, printf, ps, pscan, pwd, raidautorun, rdate, rdev, readahead, readlink, readprofile, realpath, reboot, renice, reset, resize, restorecon, rm, rmdir, rmmod, route, rpm, rpm2cpio, rtcwake, run\_parts, runcon, runlevel, runsv, runsvdir, rx, script, sed, selinuxenabled, sendmail, seq, sestatus, setarch, setconsole, setenforce, setfiles, setfont, setkeycodes, setlogcons, setsebool, setsid, setuidgid, sh, sha1sum, showkey, slattach, sleep, softlimit, sort, split, start\_stop\_daemon, stat, strings, stty, su, sulogin, sum, sv, svlogd, swapoff, swapon, switch\_root, sync, sysctl, syslogd, tac, tail, tar, taskset, tcpsvd, tee, telnet, telnetd, test, tftp, tftpd, time, top, touch, tr, traceroute, true, tty, ttysize, tune2fs, udhcpc, udhcpd, udpsvd, umount, uname, uncom- press, unexpand, uniq, unix2dos, unlzma, unzip, uptime, usleep, uudecode, uuencode, vconfig, vi, vlock, watch, watchdog, wc, wget, which, who, whoami, xargs, yes, zcat, zcip

O **Busybox** fornece praticamente tudas as ferramentas abaixo em aproximadamente 1MB, e é possível deixa-lo menor, eliminando tudo aquilo que sua aplicação não necessita ou depende. Desta forma, desenvolver sistemas Linux embarcado é muito parecido com brincar de Lego.

