# SimTesting.pl
# Regression testing script for 2490G/C
#
#


# Pulls in the Code Composer Studio Scripting declarations and definitions
use CCS_SCRIPTING_PERL;

# All errors will go to END subroutine for cleanup
# (not working well on ctl-c)
use sigtrap qw( die normal-signals error-signals INT );


# Declarations and Initializations
# Create Code Composer Studio Scripting object
my $MyCCScripting = new CCS_SCRIPTING_PERL::CCS_Scripting();

my $sCurDir = ".\\"; 
my $sLogFile = "script.log"; 
my $sProject = ".\\2490G_MDT.pjt"; 
my $sProgram = ".\\Build\\2490G_MDT.out"; 

my $currentPDDFile;

my $nPCVal; 
my $nPCVal2;
my $nReturnVal;
my $nMainAddr; 
my $nBreakpoint1; 
my $nBreakpoint2;
my $sHexOutput;
my $sBoardName = "None";
my $sCPUName;
my $sISAMajor;
my $sISAMinor;
my $sVersion;
my $fileName;

# Important subdirectories

my $TestRootDir 	= ".\\Build";
my $tempDir 		= "$TestRootDir\\temp";
my $sPDDPath 		= "$TestRootDir\\PDD";
my $sPDDPassDir 	= "$TestRootDir\\Pass";
my $sPDDFailDir 	= "$TestRootDir\\Fail";
my $sDMPDir			= "$TestRootDir\\OriginalStddmp";


# Important files for/from 2490G

my $sPackageFileName 			= "$TestRootDir\\upload.bin";
my $sDeviceMemoryFileName 		= "device.dm";
my $s2490G_TestOutputFileName 	= "$TestRootDir\\2490G_TestRun.log";
my $sCSPY2PDDFile	 			= "cspy_pdd.c";


# External programs used by this script

my $sPDD2CspyPath 		= "$TestRootDir\\pdd2cspy.exe";
my $packageSplitterPath = "PackageSplitter" ;
my $stddmpPath 			= "\\stddmp.exe"; 


# Strings to be removved from DMP files

my $grepString_Offsets 	= "0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F";
my $grepString_Checksum	= " Checksum: 0x";

print ("Testing...\n");

my $startTime = time;

# Open log file and set to maximum level of debug output
$MyCCScripting -> ScriptTraceBegin($sLogFile);
$MyCCScripting -> ScriptTraceVerbose($CCS_SCRIPTING_PERL::VERBOSE_ERRORS_ONLY);

# Document the current version of Code Composer Studio Scripting
$sVersion = $MyCCScripting->ScriptGetVersion();
$MyCCScripting -> ScriptTraceWrite("$sVersion\n");
print "$sVersion\n";


# Open Code Composer Studio for the C55x Emulator
$MyCCScripting -> CCSOpen($CCS_SCRIPTING_PERL::ISA_C55,
			  0,
              0,
			  $CCS_SCRIPTING_PERL::PLATFORM_EMULATOR,
			  1);

print "CCS opened\n";


# Retrieve the Board, ISA and CPU name of the current configuration
# and write names to log file
$sBoardName = $MyCCScripting -> TargetGetBoardName();
$sISAMajor = $MyCCScripting -> TargetGetMajorISA();
$sISAMinor = $MyCCScripting -> TargetGetMinorISA();

$MyCCScripting -> ScriptTraceWrite("Board Name: $sBoardName\n");
$MyCCScripting -> ScriptTraceWrite("ISA Major: $sISAMajor\n\n");
$MyCCScripting -> ScriptTraceWrite("ISA Minor: $sISAMinor\n\n");


# The previous Board name and CPU name can be used to open other instance of Code Composer Studio
#$MyCCScripting2 -> CCSOpenNamed($sBoardName, $sCPUName, 0);

# Set the Current Directory, if necessary
$MyCCScripting -> CCSSetCurrentDirectory($sCurDir);

print "Opening $sProject\n";

# Open the project
$MyCCScripting -> ProjectOpen($sProject);

# Build the project
$MyCCScripting -> ProjectBuild("Debug");

# Load Gel file - StartUp() is run at load time
$nValResult = $MyCCScripting -> TargetEvalExpression("GEL_LoadGel( \"2490G.gel\")");

# Open directory holding the input PDDs for testing
opendir(IN_DIR, $sPDDPath) or die $!;

# Get list of (only) PDD files.
my @pddfiles = grep /\.pdd/, readdir IN_DIR; 

######################################################
# Create output/result directories
######################################################

if (! -e $sPDDPassDir ) {
	print "Creating $sPDDPassDir\n";
 	if (! mkdir $sPDDPassDir, 0777 ) {
 		die;
 	}
}
 
if (! -e $sPDDFailDir ) {
	print "Creating $sPDDFailDir\n";
 	if (! mkdir $sPDDFailDir, 0777 ) {
 		die;
 	}
}

if (! -e $tempDir ) {
	print "Creating $tempDir\n";
 	if (! mkdir $tempDir, 0777 ) {
 		die;
 	}
}

if (! -e $sDMPDir ) {
	print "Creating $sDMPDir\n";
 	if (! mkdir $sDMPDir, 0777 ) {
 		die;
 	}
}



######################################################
# Main loop
######################################################

my $nCurrentItem = 1;
my $nNumberOfPDDs = @pddfiles;

print "\n\n\n";

foreach my $currentPDD (@pddfiles) {


	print "Processing $currentPDD, file $nCurrentItem of $nNumberOfPDDs. \n";
	$nCurrentItem = $nCurrentItem + 1;

	
	###########################################################
	# Create Original STDDMP output and Device Memory (DM) File
	###########################################################


	# Create STDDMP "*.DMP"  file of input PDD for comparision later.   

	my $sFilename = $currentPDD; # Convert from list item to string?
	
	$sFilename =~ s/.pdd//i ;

	@dm_args = ("$stddmpPath", 
				"$sPDDPath\\$currentPDD ",
				" | grep -v \"$grepString_Offsets\"",
				" \> $sDMPDir\\$sFilename.dmp");

	# Create DMP file - there should be no errors	on this
	#print "@dm_args\n";
   	if (system(@dm_args) != 0) {
   		die "system \@args failed: $?";
   	}

	# Delete device.dm and cspy2pdd.c

	&deleteFile( "$TestRootDir\\$sDeviceMemoryFileName" );
	&deleteFile( $sCSPY2PDDFile );
	
	print "Using $sPDD2CspyPath\n";

	# Create Dev Mem file for testing.   
	# Pipe STDOUT to the DOS "NUL" bit-bucket
	
	$sFilename =  $currentPDD; # Convert from list item to string?
	@dm_args = ("$sPDD2CspyPath", "$sPDDPath\\$currentPDD \> \NUL");

	# Translate - there should be no errors	on this
	if (system(@dm_args) != 0) {
		die "system \@args failed: $?";
	}
	
	# Move Dev Mem (DM) file manually till we finalize our directory structure
	&moveFile ( $sDeviceMemoryFileName, $TestRootDir );

	######################################################
	# Prep and run the 2490G
	######################################################
	 
	# Remove any old package file from 2490G  (upload.bin)
	&deleteFile( $sPackageFileName );

	# Remove any old test run file created by 2490G
	&deleteFile ( $s2490G_TestOutputFileName );


	# This will reset the target and run the OnReset() GEL function
	print "Resetting target.\n";
	$MyCCScripting -> TargetReset;

	# Load the .out file
	print "Loading target firmware.\n";
	$MyCCScripting -> ProgramLoad($sProgram);

	# Get the address of DeviceSimError.  Set a breakpoint there.
	print "Getting/setting error breakpoint.\n";

	$nDevSimErrorAddr = $MyCCScripting -> SymbolGetAddress("DeviceSimErrorBreakpoint");
	$nErrorBreakpoint = $MyCCScripting -> BreakpointSetAddress($nDevSimErrorAddr);

	# Get the address of DeviceSimComplete.  Set a breakpoint there.
	print "Getting/setting completion breakpoint.\n";
	$nDevSimCompleteAddr = $MyCCScripting -> SymbolGetAddress("DeviceSimCompleteBreakpoint");
	$nCompleteBreakpoint = $MyCCScripting -> BreakpointSetAddress($nDevSimCompleteAddr);

	# Run to either breakpoint 
	print "Target running.\n";
	$MyCCScripting -> TargetRun;

	print "Breakpoint was hit.\n";


	# Read the value of the PC and display in the DOS prompt and trace file
	$nPCVal = $MyCCScripting -> RegisterRead("PC");
	$sHexOutput = sprintf("PC=0x%x, Complete= 0x%x, Error= 0x%x \n", $nPCVal, 
		$nDevSimCompleteAddr, $nDevSimErrorAddr);

	#print $sHexOutput;

	$MyCCScripting -> ScriptTraceWrite("$sHexOutput\n");

	# Check values
	if ($nPCVal == $nDevSimCompleteAddr)
	{
	    $MyCCScripting -> ScriptTraceWrite("\nTest Passed\n");
	    print ("\n********\nPassed\n********\n\n");
		&moveResults( $currentPDD, $sPDDPassDir);
		&splitPackage($currentPDD, $sPDDPassDir);
	}
	else
	{
	    $MyCCScripting -> ScriptTraceWrite("\nTest Failed\n");
	    print ("\n********\nFAILED\n********\n\n");
		&moveResults( $currentPDD, $sPDDFailDir);
	}

	# Remove all the breakpoints.  Restart and rerun.
	$MyCCScripting -> BreakpointRemoveAll;
	$MyCCScripting -> TargetReset;

	# Halt target - this command seems to force CCS to close or let go of the
	# "device.dm" file so we can manipulate/move it.
	$MyCCScripting -> TargetHalt;

	# Write comments
	$MyCCScripting -> ScriptTraceWrite("$currentPDD completed.\n");
	print ("$currentPDD completed.\n\n");

} # End of foreach 


END {

	print ("\n\nShutting down...\n");

	my $endTime = time;

	my $minutes = ($endTime - $startTime)/60;

	print "Testing took about $minutes minute(s).\n";

	# Halt target
	#$MyCCScripting -> TargetHalt;
	#print ("Target halted.\n");

	# Close the project file
	$MyCCScripting -> ProjectClose;
	print ("Project closed.\n");

	# Close all current Code Composer Studio processes
	$MyCCScripting -> CCSClose();
	print ("Code Composer closed.\n");


	# Close the trace file
	$MyCCScripting -> ScriptTraceWrite("\n\nEnd of trace.\n");
	$MyCCScripting -> ScriptTraceEnd;
	print ("Trace file closed.\n");


	# Close the directories
	closedir IN_DIR;
	closedir OUT_DIR;

	print ("Done.\n\n");
}


sub moveResults {

	#my $pddFileBase, $directory;
	local ($pddFileBase, $directory) = @_; 

	# From xyz123.pdd, get xyz123

   	if ( $pddFileBase =~  s/.pdd//i ) {
		print "Moving $pddFileBase results to $directory directory.\n";
	}
	else {
		print "There is a non-pdd file in the list\?\!\n";
		die;
	}

	# Move cspy2pdd.c file for help in debugging
	&moveFile( $sCSPY2PDDFile, "$directory\\$pddFileBase.c");

	# Move Dev Mem (DM) file 
	&moveFile(".\\Build\\$sDeviceMemoryFileName", "$directory\\$pddFileBase.dm");

	# Move OUTPUT.BIN file 
	&moveFile (	"$sPackageFileName", "$directory\\$pddFileBase.bin");

	# Move log file from 2490G 
	&moveFile ( $s2490G_TestOutputFileName, "$directory\\$pddFileBase.log");
}    
    


sub deleteFile {

	#my $delFileName;
	local ($delFileName) = @_; 

	# Remove file if it exists

	if ( -e $delFileName ) {

		print "Deleting $delFileName.\n";

		@deleteFile_args = ("del", $delFileName);
		#print "@deleteFile_args\n";
		system(@deleteFile_args);
	}

	# Verify the deletion happened
	if ( -e $delFileName ) {
	 	die "Can't remove $delFileName.\n" ; 
	}
}


sub moveFile {

	#my $source, $destination;

	local ($source, $destination) = @_; 


	# Move file if it exists

	if ( -e $source ) {
							
		print "Moving $source to $destination.\n";

		# Use DOS move
		@move_File_args = ( "move", $source, $destination);

		#print "@move_File_args\n";
		system( @move_File_args );
	}

	# Verify the move happened or didn't have to
	if ( -e $source ) {
	 	die "Can't move $source.\n" ; 
	}
}


sub splitPackage {

	#my $pddFileBase, $directory;
	local ($pddFileBase, $directory) = @_; 

	# From xyz123.pdd, get xyz123

   	if ( $pddFileBase =~  s/.pdd//i ) {
		print "Moving $pddFileBase PackageSplitter results to $directory directory.\n";
	}
	else {
		print "There's a non-pdd file in the list?!\n";
		die;
	}

	# Remove previous files

	unlink("$tempDir\\00000000-0000-0000-0000-000000000000.pdd"); 
	unlink("$tempDir\\00000000-0000-0000-0000-000000000000.pwc"); 
	unlink("$tempDir\\00000000-0000-0000-0000-000000000000.asc");
	unlink("$tempDir\\00000000-0000-0000-0000-000000000000.dmp");
		 
	# http://iis1.cps.unizar.es/Oreilly/perl/cookbook/ch16_05.htm
	# Open PackageSplitter and send it some additional STDIN information
	my $pid = open(WRITEME, "| $packageSplitterPath") or die "Couldn't fork: $!\n";

	# Tell PackageSplitter what Package file to split
	print WRITEME "$directory\\$pddFileBase.bin\n";

	# Tell PackageSplitter where to put the components
	print WRITEME "$tempDir\n";
	close(WRITEME);  

	
	# Run STDDMP on PDD - remove address offset lines 
	@createFile_args = ( $stddmpPath, 
						"$tempDir\\00000000-0000-0000-0000-000000000000.pdd",
						" | grep -v \"$grepString_Offsets\" ", 
						" \> $tempDir\\00000000-0000-0000-0000-000000000000.dmp"); 

	#print "@createFile_args\n";
	system(@createFile_args);

	# Move PDD file 
	&moveFile("$tempDir\\00000000-0000-0000-0000-000000000000.pdd", "$directory\\$pddFileBase.pdd");

	# Move asset file
	&moveFile("$tempDir\\00000000-0000-0000-0000-000000000000.asc", "$directory\\$pddFileBase.asc");

	# Move presenting waveform file 
	&moveFile("$tempDir\\00000000-0000-0000-0000-000000000000.pwc", "$directory\\$pddFileBase.pwc");

	# Move STDDMP file 
	&moveFile("$tempDir\\00000000-0000-0000-0000-000000000000.dmp", "$directory\\$pddFileBase.dmp");
}    
