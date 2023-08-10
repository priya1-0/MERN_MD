-----Original Message-----
From: VOCAL Technologies, Ltd. [mailto:vocal@vocal.com]
Sent: Monday, February 09, 2004 7:41 PM
To: Terry Sherman
Cc: Pat Wilson
Subject: source release


Terry,
	Here is the release with source for the network layers.  If there are any
questions let me know.  It can be built by typing "gmake subs all" in the
root of the tree.  Do not put this tree in a path that contains long
directory (>8 char) names (gmake will not always like that).
For reference, this is built from our 2_39 revision.

Dave

Notes:
A listing of the files associated with the network exist @ "arch\link_grp.src"




Terry,

	Attached you should find 031117A.zip, which contains the following: 
plexusA.zpd - a zip file of all the necessary object files 
plexusA.cmd - the linker command file for the above files 
cx077.h     - interface header file 
plxcfg.cmd  - the linker command file created by the DSP/BIOS config tool from plx.cdb 
plx.cdb     - the DSP/BIOS configuration database, based on the 2490.cdb that you provided when you were here. 
mcbsp.c     - the MCBSP code we are using for configuration.

	Concerning the UART interface, this code doesn't handle any of the UART interface.  Since your application will be using it most of the time, perhaps you can provide a function for each direction, which we can use when we want to grab control of the interface for testing.

Matt Bivans & Dave Satterle
Associates
VOCAL Technologies