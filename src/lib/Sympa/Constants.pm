# Sympa::Constants.pm - This module contains all installation-related variables
# RCS Identication ; $Revision: 5768 $ ; $Date: 2009-05-21 16:23:23 +0200 (jeu. 21 mai 2009) $ 
#
# Sympa - SYsteme de Multi-Postage Automatique
# Copyright (c) 1997, 1998, 1999, 2000, 2001 Comite Reseau des Universites
# Copyright (c) 1997,1998, 1999 Institut Pasteur & Christophe Wolfhugel
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

package Sympa::Constants;
use strict;

use Exporter;
our @ISA = qw(Exporter);


use constant VERSION => '6.0';
use constant USER    => 'sympa';
use constant GROUP   => 'sympa';

use constant CONFIG           => '/usr/local/sympa-unstable/etc/sympa.conf';
use constant WWSCONFIG        => '/usr/local/sympa-unstable/etc/wwsympa.conf';
use constant SENDMAIL_ALIASES => '/etc/mail/aliases-sympa-unstable';

use constant PIDDIR     => '/usr/local/sympa-unstable';
use constant EXPLDIR    => '/usr/local/sympa-unstable/list_data';
use constant SPOOLDIR   => '/usr/local/sympa-unstable/spool';
use constant SYSCONFDIR => '/usr/local/sympa-unstable/etc';
use constant LOCALEDIR  => '/usr/local/sympa-unstable/locale';
use constant LIBEXECDIR => '/usr/local/sympa-unstable/bin';
use constant SBINDIR    => '/usr/local/sympa-unstable/bin';
use constant SCRIPTDIR  => '/usr/local/sympa-unstable/bin';
use constant MODULEDIR  => '/usr/local/sympa-unstable/bin';
use constant DEFAULTDIR => '/usr/local/sympa-unstable/default';
use constant STATICDIR  => '/usr/local/sympa-unstable/static_content';
use constant ARCDIR    => '/usr/local/sympa-unstable/arc';
use constant BOUNCEDIR  => '/usr/local/sympa-unstable/bounce';

1;
