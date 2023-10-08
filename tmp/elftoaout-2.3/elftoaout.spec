Summary: A utility for converting ELF binaries to a.out binaries.
Name: elftoaout
Version: 2.3
Release: 1
ExclusiveArch: sparc sparc64
Copyright: GPL
Group: System Environment/Kernel
Source: ftp://sunsite.mff.cuni.cz/OS/Linux/Sparc/local/elftoaout/elftoaout-2.3.tgz
BuildRoot: /var/tmp/%{name}-root

%description
The elftoaout utility converts a static ELF binary to a static a.out
binary.  If you're using an ELF system (i.e., Red Hat Linux) on a SPARC,
you'll need to run elftoaout on the kernel image so that the SPARC PROM
can netboot the image.

If you're installing Red Hat Linux on a SPARC, you'll need to install the
elftoaout package.

%prep
%setup -q

%build
make

%install
rm -rf $RPM_BUILD_ROOT

mkdir -p $RPM_BUILD_ROOT/usr/bin
install -m 0755 -s elftoaout $RPM_BUILD_ROOT/usr/bin/elftoaout

mkdir -p $RPM_BUILD_ROOT/usr/share/man/man1
install -m 0644 elftoaout.1 $RPM_BUILD_ROOT/usr/share/man/man1/elftoaout.1

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
/usr/bin/elftoaout
/usr/share/man/man1/elftoaout.*

%changelog
* Sat Jun  3 2000 Jakub Jelinek <jakub@redhat.com>
- 2.3 - -c support by Pete Zaitcev

* Tue Feb 22 2000 Bill Nottingham <notting@redhat.com>
- handle compressed manpages

* Sun Mar 21 1999 Cristian Gafton <gafton@redhat.com> 
- auto rebuild in the new build environment (release 3)

* Sun Jan 17 1999 Jeff Johnson <jbj@redhat.com>
- rebuild for Raw Hide.

* Fri Jul 10 1998 Jeff Johnson <jbj@redhat.com>
- repackage ultrapenguin with build root.
