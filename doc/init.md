Sample init scripts and service configuration for mariad
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/mariad.service:    systemd service unit configuration
    contrib/init/mariad.openrc:     OpenRC compatible SysV style init script
    contrib/init/mariad.openrcconf: OpenRC conf.d file
    contrib/init/mariad.conf:       Upstart service configuration file
    contrib/init/mariad.init:       CentOS compatible SysV style init script

Service User
---------------------------------

All three Linux startup configurations assume the existence of a "maria" user
and group.  They must be created before attempting to use these scripts.
The macOS configuration assumes mariad will be set up for the current user.

Configuration
---------------------------------

At a bare minimum, mariad requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, mariad will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that mariad and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If mariad is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running mariad without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see contrib/debian/examples/maria.conf.

Paths
---------------------------------

### Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              /usr/bin/mariad
Configuration file:  /etc/maria/maria.conf
Data directory:      /var/lib/mariad
PID file:            `/var/run/mariad/mariad.pid` (OpenRC and Upstart) or `/run/mariad/mariad.pid` (systemd)
Lock file:           `/var/lock/subsys/mariad` (CentOS)

The configuration file, PID directory (if applicable) and data directory
should all be owned by the maria user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
maria user and group.  Access to maria-cli and other mariad rpc clients
can then be controlled by group membership.

NOTE: When using the systemd .service file, the creation of the aforementioned
directories and the setting of their permissions is automatically handled by
systemd. Directories are given a permission of 710, giving the maria group
access to files under it _if_ the files themselves give permission to the
maria group to do so (e.g. when `-sysperms` is specified). This does not allow
for the listing of files under the directory.

NOTE: It is not currently possible to override `datadir` in
`/etc/maria/maria.conf` with the current systemd, OpenRC, and Upstart init
files out-of-the-box. This is because the command line options specified in the
init files take precedence over the configurations in
`/etc/maria/maria.conf`. However, some init systems have their own
configuration mechanisms that would allow for overriding the command line
options specified in the init files (e.g. setting `BITCOIND_DATADIR` for
OpenRC).

### macOS

Binary:              `/usr/local/bin/mariad`
Configuration file:  `~/Library/Application Support/MARIA/maria.conf`
Data directory:      `~/Library/Application Support/MARIA`
Lock file:           `~/Library/Application Support/MARIA/.lock`

Installing Service Configuration
-----------------------------------

### systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start mariad` and to enable for system startup run
`systemctl enable mariad`

NOTE: When installing for systemd in Debian/Ubuntu the .service file needs to be copied to the /lib/systemd/system directory instead.

### OpenRC

Rename mariad.openrc to mariad and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/mariad start` and configure it to run on startup with
`rc-update add mariad`

### Upstart (for Debian/Ubuntu based distributions)

Upstart is the default init system for Debian/Ubuntu versions older than 15.04. If you are using version 15.04 or newer and haven't manually configured upstart you should follow the systemd instructions instead.

Drop mariad.conf in /etc/init.  Test by running `service mariad start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

### CentOS

Copy mariad.init to /etc/init.d/mariad. Test by running `service mariad start`.

Using this script, you can adjust the path and flags to the mariad program by
setting the MARIAD and FLAGS environment variables in the file
/etc/sysconfig/mariad. You can also use the DAEMONOPTS environment variable here.

### macOS

Copy org.maria.mariad.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.maria.mariad.plist`.

This Launch Agent will cause mariad to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run mariad as the current user.
You will need to modify org.maria.mariad.plist if you intend to use it as a
Launch Daemon with a dedicated maria user.

Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
