
## ######################################################################### ##
##
 #	vocal.pm
 #
 #	(C) 2001 VOCAL Technologies, Ltd.
 #
 #	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 #
 #	VOCAL Technologies, Ltd.
 #	90A John Muir Drive.
 #	Buffalo, NY  14228
 #
 #	Product:	MODEM 101
 #
 #	Module:		UTILITY
 #
 #	This file contains the standard vocal perl module.
 #
 #	Revision Number:	$Revision$
 #	Revision Status:	$State$
 #	Last Modified:		$Date$
 #	Identification:		$Id$
 #
 #	Revision History:	$Log$
 #	Revision History:	Revision 1.1.24.1  2009/04/28 20:18:47  zhangn1
 #	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 #	Revision History:	
 #
 #
## ######################################################################### ##

package vocal;

# Initialize
&set_print_debug_level (0);
&set_print_std_level (1);
&clear_options ();

%type_suffix = (
				PARM_D0	  => "PARMS0",
				PARM_D1	  => "PARMS1",
				PARM_D2	  => "PARMS2",
				PARM_D	  => "PARMS",
				STAT_D0	  => "STATS0",
				STAT_D1	  => "STATS1",
				STAT_D2	  => "STATS2",
				STAT_D	  => "STATS",
				VAR_D0	  => "VARS0",
				VAR_D1	  => "VARS1",
				VAR_D2	  => "VARS2",
				VAR_D	  => "VARS",
				FAST_D0	  => "FAST0",
				FAST_D1	  => "FAST1",
				FAST_D2	  => "FAST2",
				FAST_D	  => "FAST",
				PERSIST_D0 => "PERSIST0",
				PERSIST_D1 => "PERSIST1",
				PERSIST_D2 => "PERSIST2",
				PERSIST_D => "PERSIST",
				SHARED_D0  => "SHARED0",
				SHARED_D1  => "SHARED1",
				SHARED_D2  => "SHARED2",
				SHARED_D  => "SHARED",
				TEMP_D0	  => "TEMP0",
				TEMP_D1	  => "TEMP1",
				TEMP_D2	  => "TEMP2",
				TEMP_D	  => "TEMP",
				CONST_D0	  => "CONST0",
				CONST_D1	  => "CONST1",
				CONST_D2	  => "CONST2",
				CONST_D	  => "CONST",
				DEBUG_D0	  => "DEBUG0",
				DEBUG_D1	  => "DEBUG1",
				DEBUG_D2	  => "DEBUG2",
				DEBUG_D	  => "DEBUG",
				LOCAL_D0	  => "LOCAL0",
				LOCAL_D1	  => "LOCAL1",
				LOCAL_D2	  => "LOCAL2",
				LOCAL_D	  => "LOCAL",
				COEF_D0	  => "COEF0",
				COEF_D1	  => "COEF1",
				COEF_D2	  => "COEF2",
				COEF_D	  => "COEF",
				LARGE_D0	  => "LARGE0",
				LARGE_D1	  => "LARGE1",
				LARGE_D2	  => "LARGE2",
				LARGE_D	  => "LARGE",
			   );

%lc_type_suffix = (
				parm_d0	  => "parms0",
				parm_d1	  => "parms1",
				parm_d2	  => "parms2",
				parm_d	  => "parms",
				stat_d0	  => "stats0",
				stat_d1	  => "stats1",
				stat_d2	  => "stats2",
				stat_d	  => "stats",
				var_d0	  => "vars0",
				var_d1	  => "vars1",
				var_d2	  => "vars2",
				var_d	  => "vars",
				fast_d0	  => "fast0",
				fast_d1	  => "fast1",
				fast_d2	  => "fast2",
				fast_d	  => "fast",
				persist_d0 => "persist0",
				persist_d1 => "persist1",
				persist_d2 => "persist2",
				persist_d => "persist",
				shared_d0  => "shared0",
				shared_d1  => "shared1",
				shared_d2  => "shared2",
				shared_d  => "shared",
				temp_d0	  => "temp0",
				temp_d1	  => "temp1",
				temp_d2	  => "temp2",
				temp_d	  => "temp",
				const_d0	  => "const0",
				const_d1	  => "const1",
				const_d2	  => "const2",
				const_d	  => "const",
				debug_d0	  => "debug0",
				debug_d1	  => "debug1",
				debug_d2	  => "debug2",
				debug_d	  => "debug",
				local_d0	  => "local0",
				local_d1	  => "local1",
				local_d2	  => "local2",
				local_d	  => "local",
				coef_d0	  => "coef0",
				coef_d1	  => "coef1",
				coef_d2	  => "coef2",
				coef_d	  => "coef",
				large_d0	  => "large0",
				large_d1	  => "large1",
				large_d2	  => "large2",
				large_d	  => "large",
			   );

%suffix_type = (
				PARMS0	=> "PARM_D0",
				PARMS1	=> "PARM_D1",
				PARMS2	=> "PARM_D2",
				PARMS	=> "PARM_D",
				STATS0	=> "STAT_D0",
				STATS1	=> "STAT_D1",
				STATS2	=> "STAT_D2",
				STATS	=> "STAT_D",
				VARS0	=> "VAR_D0",
				VARS1	=> "VAR_D1",
				VARS2	=> "VAR_D2",
				VARS	=> "VAR_D",
				FAST0	=> "FAST_D0",
				FAST1	=> "FAST_D1",
				FAST2	=> "FAST_D2",
				FAST	=> "FAST_D",
				PERSIST0 => "PERSIST_D0",
				PERSIST1 => "PERSIST_D1",
				PERSIST2 => "PERSIST_D2",
				PERSIST => "PERSIST_D",
				SHARED0	=> "SHARED_D0",
				SHARED1	=> "SHARED_D1",
				SHARED2	=> "SHARED_D2",
				SHARED	=> "SHARED_D",
				TEMP0	=> "TEMP_D0",
				TEMP1	=> "TEMP_D1",
				TEMP2	=> "TEMP_D2",
				TEMP	=> "TEMP_D",
				CONST0	=> "CONST_D0",
				CONST1	=> "CONST_D1",
				CONST2	=> "CONST_D2",
				CONST	=> "CONST_D",
				DEBUG0	=> "DEBUG_D0",
				DEBUG1	=> "DEBUG_D1",
				DEBUG2	=> "DEBUG_D2",
				DEBUG	=> "DEBUG_D",
				LOCAL0	=> "LOCAL_D0",
				LOCAL1	=> "LOCAL_D1",
				LOCAL2	=> "LOCAL_D2",
				LOCAL	=> "LOCAL_D",
				COEF0	=> "COEF_D0",
				COEF1	=> "COEF_D1",
				COEF2	=> "COEF_D2",
				COEF	=> "COEF_D",
				LARGE0	=> "LARGE_D0",
				LARGE1	=> "LARGE_D1",
				LARGE2	=> "LARGE_D2",
				LARGE	=> "LARGE_D",
			   );

%keep_empty =  (
				parm_d0	  => 1,
				parm_d1	  => 1,
				parm_d2	  => 1,
				parm_d	  => 1,
				stat_d0	  => 1,
				stat_d1	  => 1,
				stat_d2	  => 1,
				stat_d	  => 1,
				var_d0	  => 1,
				var_d1	  => 1,
				var_d2	  => 1,
				var_d	  => 1,
				fast_d0	  => 0,
				fast_d1	  => 0,
				fast_d2	  => 0,
				fast_d	  => 0,
				persist_d0 => 0,
				persist_d1 => 0,
				persist_d2 => 0,
				persist_d => 0,
				shared_d0  => 0,
				shared_d1  => 0,
				shared_d2  => 0,
				shared_d  => 0,
				temp_d0	  => 0,
				temp_d1	  => 0,
				temp_d2	  => 0,
				temp_d	  => 0,
				const_d0	  => 0,
				const_d1	  => 0,
				const_d2	  => 0,
				const_d	  => 0,
				debug_d0	  => 0,
				debug_d1	  => 0,
				debug_d2	  => 0,
				debug_d	  => 0,
				local_d0	  => 0,
				local_d1	  => 0,
				local_d2	  => 0,
				local_d	  => 0,
				coef_d0	  => 0,
				coef_d1	  => 0,
				coef_d2	  => 0,
				coef_d	  => 0,
				large_d0	  => 0,
				large_d1	  => 0,
				large_d2	  => 0,
				large_d	  => 0,
			   );

$valid_list = qr"
				parm0|
				parm1|
				parm2|
				parm|
				const0|
				const1|
				const2|
				const|
				shared0|
				shared1|
				shared2|
				shared|
				local0|
				local1|
				local2|
				local|
				parms0|
				parms1|
				parms2|
				parms|
				stats0|
				stats1|
				stats2|
				stats|
				temp0|
				temp1|
				temp2|
				temp|
				vars0|
				vars1|
				vars2|
				vars|
				persist0|
				persist1|
				persist2|
				persist|
				fast0|
				fast1|
				fast2|
				fast|
				debug0|
				debug1|
				debug2|
				debug|
				coef0|
				coef1|
				coef2|
				coef|
				large0|
				large1|
				large2|
				large|
				global|mdm|csc|dte|response|state|monitor|dteif|support|v24|csp|omc|struct"x;

$dtype =   qr"
				PARM_D0|
				PARM_D1|
				PARM_D2|
				PARM_D|
				STAT_D0|
				STAT_D1|
				STAT_D2|
				STAT_D|
				VAR_D0|
				VAR_D1|
				VAR_D2|
				VAR_D|
				FAST_D0|
				FAST_D1|
				FAST_D2|
				FAST_D|
				PERSIST_D0|
				PERSIST_D1|
				PERSIST_D2|
				PERSIST_D|
				SHARED_D0|
				SHARED_D1|
				SHARED_D2|
				SHARED_D|
				TEMP_D0|
				TEMP_D1|
				TEMP_D2|
				TEMP_D|
				CONST_D0|
				CONST_D1|
				CONST_D2|
				CONST_D|
				DEBUG_D0|
				DEBUG_D1|
				DEBUG_D2|
				DEBUG_D|
				LOCAL_D0|
				LOCAL_D1|
				LOCAL_D2|
				LOCAL_D|
				COEF_D0|
				COEF_D1|
				COEF_D2|
				COEF_D|
				LARGE_D0|
				LARGE_D1|
				LARGE_D2|
				LARGE_D
				"x;



# package must return 1
return (1);



## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##

## ######################################################################### ##
##
 #	Entry Routine: import
 #
 #	This routine import routine.
 #
 #	Parameters:
 #		pkg is the package name.
 #
 #	Returns:
 #		None.
 #
 #

sub import
{
	my $pkg = shift;
	my $callpkg = caller;
	&print_debug (1, "\n---$pkg---$callpkg---\n\n");

	# export these routines:
    foreach $sym (
				  "process_args",
				  "file_rd",
				  "file_wr",

				  "set_print_debug_level",
				  "print_debug",
				  "set_print_std_level",
				  "print_std",

				  "create_vocal_file_header",
				  "process_source_code",

				  "makeopt__change_cfg",

				  "strip",
				  "strip_options",
			  "load_options_file",
				  "load_options_file_ii",
				  "load_options",
				  "load_reconfigs",
				  "load_options_ii",
				  "clear_options",
				  "set_options",
			  "get_option",
				  "get_options",
				  "is_defined",

				  "reformat",
				  "rmcommnt",
				  "chgprint",
				  "rmblank",
				 )
	{
		*{"$callpkg\::$sym"} = \&{"$pkg\::$sym"};
    }
}

## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##

## ######################################################################### ##
##
 #	Entry Routine: process_args
 #
 #	This routine processes arguments.
 #
 #	Parameters:
 #		List of arguments to process.
 #
 #	Returns:
 #		None.
 #
 #	Globals Affected:
 #		"%options"		(in main) is set based on parameters.
 #		"%options_lc"	(in main) is set based on parameters.
 #		"@args"			(in main) is set based on parameters.
 #

sub process_args
{
	my ($arg);

	undef (%main::options);
	undef (%main::options_lc);
	undef (@main::args);
	foreach $arg (@_) {
		if ($arg =~ m/^([\+\-])(\S+)/) {
			$main::options {$2} = $1;
			$main::options_lc {lc ($2)} = $1;
		}
		else {
			push (@main::args, $arg);
		}
	}
}

## ######################################################################### ##
##
 #	Entry Routine: file_rd
 #	Entry Routine: file_wr
 #
 #	This routine reads/writes an entire file to/from a variable.
 #
 #	Parameters:
 #		"file" is the name of the file to read/write.
 #		"var" is the variable to read/write the file to/from.
 #
 #	Returns:
 #		1 for success, 0 for failure.
 #

sub file_rd
{
	my ($file) = shift;
	local ($/);

	undef $/;			# Slurp the entire file
	if (open (FILE, $file)) {
		$_ [0] = <FILE>;
		close (FILE);
		return 1;
	}
	else {
		return 0;
	}
}

sub file_wr
{
	my ($file) = shift;

	if (open (FILE, sprintf (">%s", $file))) {
		print FILE $_ [0];
		close (FILE);
		return 1;
	}
	else {
		return 0;
	}
}

## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##

## ######################################################################### ##
##
 #	Entry Routine: set_print_debug_level
 #	Entry Routine: print_debug
 #	Entry Routine: set_print_std_level
 #	Entry Routine: print_std
 #
 #	This routine print based on debug print levels.
 #
 #	Parameters:
 #		level is the debug level.
 #
 #	Returns:
 #		None.
 #

sub set_print_debug_level
{
	my($level) = @_;
#	our ($print_debug_level)

	$print_debug_level = $level;
}

sub print_debug
{
	my($level) = shift (@_);
#	our ($print_debug_level)

	if ($level <= $print_debug_level) {
		printf STDERR (@_);
	}
}

sub set_print_std_level
{
	my($level) = @_;
#	our ($print_std_level)

	$print_std_level = $level;
}

sub print_std
{
	my($level) = shift (@_);
#	our ($print_std_level)

	if ($level <= $print_std_level) {
		printf STDOUT (@_);
	}
}


## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##

## ######################################################################### ##
##
 #	Entry Routine: create_vocal_file_header
 #
 #	This routine creates a standard VOCAL file header.
 #
 #	Parameters:
 #		"filename"	is the name of the file for which the header is being made.
 #		"year"		is the copyright year.
 #		"product"	is the product name.
 #		"module"	is the module.
 #		"desc"		is the description.
 #
 #	Returns:
 #		None.
 #

sub create_vocal_file_header
{
	my ($filename, $year, $product, $module, $desc) = @_;
#	our ($file_header_template);

	$file_header_template ||= <<PRT__C_HEADER;
/* ************************************************************************* */
/*
 *	%s
 *
 *	(C) 1994 - %04u VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	%s
 *
 *	Module:		%s
 *
 *	%s
 *
 *	Revision Number:	\$Revision\$
 *	Revision Status:	\$State\$
 *	Last Modified:		\$Date\$
 *	Identification:		\$Id\$
 *
 *	Revision History:	\$Log\$
 *
 */
/* ************************************************************************* */
PRT__C_HEADER

   return (sprintf ($file_header_template,
					$filename, $year, $product, $module, $desc));
}

## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##

## ######################################################################### ##
##
 #	Entry Routine: process_source_code
 #
 #	This routine processes source, removing or maintaining specified sections.
 #
 #	Parameters:
 #		Variable containing source code.
 #		Flags indicating what to remove and what to keep.
 #
 #	Returns:
 #		Exit status.
 #

sub process_source_code
{
	my($regex, $type);
#	our (@sc_regex_array);

	&init_source_code_parser (@_ [1..$#_]);	# Initializes %sc_operation_hash
	$regex = join ("|", @sc_regex_array);
	&print_debug (1, "\n\n process_source_code REGEX[%s]\n\n", $regex);
	$_ [0] =~ s/(${regex})/&sc_proc ($1)/ge;

}

## ######################################################################### ##
##
 #	Local Routine: sc_proc
 #
 #	Decides what to do with a string.
 #
 #	Parameters:
 #		string is a string to process.
 #
 #	Returns:
 #		processed string.
 #

sub sc_proc
{
	my ($string) = @_;
	my ($regex, $op, $type, $blank_lines);
#	our (%sc_regex_hash);
#	our (%sc_operation_hash);

	&print_debug (2, "[%s]\n", $string);
	foreach $type (keys (%sc_operation_hash)) {
		$regex = $sc_regex_hash {$type};
		if ($string =~ m/^${regex}$/) {
			$op = $sc_operation_hash {$type};
			if    ($op == 0) {
				return ("");
			}
			elsif ($op == 1) {
				return ($string);
			}
			elsif ($op == 2) {
				$blank_lines = $string;
				$blank_lines =~ s{/[^\n]}{};
				return ($blank_lines);
			}
		}
	}
	return $string;
}
## ######################################################################### ##
##
 #	Entry Routine: strip_xlate
 #
 #	This routine is the matrix line translate subroutine.
 #
 #	Parameters:
 #		Line info.
 #
 #	Returns:
 #		Translated line.
 #

sub strip_xlate
{
	my($prev, $sym, $fill, $opt_line) = @_;
	my(@opt_array, $opt, $def, $option);

	# Split up matrix entries
	@Xopt_array = split (/ /, $opt_line);
	# Find entry to set config to

	$option = $define_state {$sym} || "i";

#	$option =~ s/^i$/u/ if $uu_flag;		# (i => u)
#	$option =~ s/^([ud])i$/$1/ if $ii_flag; # (ui => u, di => d)
#	$option =~ s/^i$/u/;					# (i => u)
	$option =~ s/^([ud])i$/$1/;				# (ui => u, di => d)

#	if ($line =~ m/^\#define\s+_\w+_H\b/) {
#	# ignore "#define _INCLUDE_OPTIONS_H" or similar

	if ($sym eq "_INCLUDE_OPTIONS_H" || $sym eq "_INCLUDE_RECONFIG_H") {
		$def = "#define ";
	} else {
		$def = ($option eq "d") ? "#define " :
			   ($option eq "u") ? "#undef  " : "#error  ";
	}



	if ($reconfig_state{$sym}) {
#		print "reconfig state of $sym is $reconfig_state{$sym}\n";
	}


	#FIXME this will not deal with lowercase, do not strip options
#	$opt = "Y";
#	if ($def ne "#define ") {
#		$opt = "N";
#	}

	# Split up matrix entries
	@opt_array = split (/ /, $opt_line);
	# Set the current config column to match, (only if it changed)
#	$tmpdef = $def;
#	$tmpdef =~ s/ //g;
#	if ($prev ne $tmpdef && $prev ne "//keep") {
#	print "changing  $sym $opt ($prev ne $tmpdef)\n";
#		$opt_array [1] = $opt;
#	}

	if ($reconfig_state{$sym}) {
#		print "reconfiguring state of $sym is $reconfig_state{$sym}\n";
		$opt_array [1] = $reconfig_state{$sym};
	}

	# Rejoin up matrix entries
	$opt_line = join (" ", @opt_array);

	return sprintf ("%s%s%s/*|%s */", $def, $sym, $fill, $opt_line);
#	return sprintf ("%s%s%s", $def, $sym, $fill);
}

## ######################################################################### ##
##
 #	Local Routine: init_source_code_parser
 #
 #	Initializes source code parsing hashes.
 #
 #	Parameters:
 #		string is a string to process.
 #
 #	Returns:
 #		processed string.
 #

sub init_source_code_parser
{
	my(@flags) = @_;
	my($flag, $flag_type, $flag_operation);
#	our (%sc_regex_hash);
#	our (%sc_operation_hash);
#	our (@sc_regex_array);

	if (!defined (%sc_regex_hash)) {
		%sc_regex_hash =
		(
			# Various comment styles
			"/* */"		=> qr{/\*[\s\S]*?\*/},
			"{ }"		=> qr{\{[\s\S]*?\}},
			"// EOL"	=> qr{//[^\n]*},
			"! EOL"		=> qr{\![^\n]*},
			"# EOL"		=> qr{\#[^\n]*},
			"; EOL"		=> qr{;[^\n]*},
			# Quotes
			"q"			=> qr{'(?:\\.|\\\n|[^\n\'\\])*?'},
			"qq"		=> qr{"(?:\\.|\\\n|[^\n\"\\])*?"},
			# Braces
#			"{}"		=> qr{\{(?:(?>[^\{\}])|(??{$sc_regex_hash {"{}"}}))+\}},
#			"()"		=> qr{\((?:(?>[^\(\)])|(??{$sc_regex_hash {"()"}}))+\)},
		);
	}

	undef (%sc_operation_hash);
	foreach $flag (@flags) {
		if ($flag =~ m/(\+|\-|\*)(.*)/) {
			$flag_operation = ($1 eq "-") ? 0 :
							  ($1 eq "+") ? 1 :
							  ($1 eq "*") ? 2 :
							  1; # default
			$flag_type = $2;
			if (defined ($sc_regex_hash {$flag_type})) {
				push (@sc_regex_array, $sc_regex_hash {$flag_type});
				$sc_operation_hash {$flag_type} = $flag_operation;
				next;
			}
		}
		&print_debug (0, "Warning from [init_source_code_parser]: Unknown flag [%s]", $flag);
	}
}

## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##
## ######################################################################### ##

## ######################################################################### ##
##
 #	Entry Routine: makeopt__change_cfg
 #
 #	This routine changes the configuration of a makeopt matrix.
 #
 #	Parameters:
 #		Variable containing a makeopt matrix.
 #		Flags indicating what to remove and what to keep.
 #
 #	Returns:
 #		Reconfigured makeopt matrix.
 #

sub makeopt__change_cfg
{
	my ($optfile__contents, $arg__cfg, $arg__mode, @flags) = @_;
	my (@cfg_lines, @letters, @config_names);
	my ($flag, $line, $cfg, $regex1, $cfg_line);
	# These must be readable in mo_xlate:
	local ($prev_cfg, $prev_was_vocal);
	local ($opt__force, $opt__vocal, $opt__strip);
	local ($cfg_idx, $curnt_idx, $prev_idx);

	# Process arguments
	$opt__force   = 0;
	$opt__vocal   = 0;						# Default to customer configuration
	$opt__strip   = 0;						# Default to no strip

	foreach $flag (@flags) {
		if (0) {}

		elsif ($flag eq "force") { $opt__force =  1; }
		elsif ($flag eq "vocal") { $opt__vocal =  1; }
		elsif ($flag eq "strip") { $opt__strip =  1; }

		else {
			print STDERR "Unrecognized flag\n\n";
		}
	}


	# Process matrix
	$optfile__contents =~ m|\/\*\s*Configuration:\s*(\w+)\s*\((\w+)\)\*\/|;
	$prev_cfg = $1;
	$prev_was_vocal = (($2 =~ m/vocal/i) ? 1 : 0);
	@cfg_lines = ($optfile__contents =~ m/\/\*\+\*\/.*?\/\*\|(.+?)\*\//g);

	foreach $line (@cfg_lines) {
		&print_debug (1, "\n===>${line}");
		@letters = ($line =~ m/(.) /g);
		for ($i = 0; $i < @letters; $i++) {
			$config_names [$i] .= $letters [$i];
			&print_debug (1, "\nConfig Name:".$config_names [$i]);
		}
	}

	for ($i = 0; $i < @config_names; $i++) {
		$cfg = $config_names [$i];
		$cfg =~ s/ +$//; #remove trailing spaces
		if ($cfg eq $arg__cfg) {
			$cfg_idx = $i;
			&print_debug (1, "\nFound config index = ${i}");
		}
		if ($cfg eq "CURNT") {
			$curnt_idx = $i;
			&print_debug (1, "\nFound CURNT index = ${i}");
		}
		if ($cfg eq $prev_cfg) {
			$prev_idx = $i;
			&print_debug (1, "\nFound previous index = ${i}");
		}
	}

	&print_debug (1, "\n-----\n%s\n-----\n", $regex1);
	&print_debug (2, "\n-----\n%s\n-----\n", $optfile__contents);

	# Modify options file based on matrix
	$optfile__contents =~ s/(#undef|#define|#error|\/\/keep)\s*\b(\w+)\b(.*?)\/\*\|(.*?)\*\//&mo_xlate ($1, $2, $3, $4)/ge;

	if ($opt__strip) {
		# Strip out matrix
		$optfile__contents =~ s|\n\/\*\s*Configuration:\s*.*?\*\/\n|\n|;
		$optfile__contents =~ s|(?<=\n)\/\*\+\*\/.*\n||g;
	}
	else {
		# Change config line
		$cfg_line = sprintf ("/*\tConfiguration:\t%s (%s)*/", $arg__cfg,
							 ($opt__vocal) ? "VOCAL" : "Customer");
		$optfile__contents =~ s|^\/\*\s*Configuration:\s*.*?\*\/|$cfg_line|m;
	}

	&print_debug (2, "\n-----\n%s\n-----\n", $optfile__contents);
	$_ [0] = $optfile__contents; # return by reference
}

## ######################################################################### ##
##
 #	Entry Routine: mo_xlate
 #
 #	This routine is the matrix line translate subroutine.
 #
 #	Parameters:
 #		Line info.
 #
 #	Returns:
 #		Translated line.
 #

sub mo_xlate
{
	my($prev, $sym, $fill, $opt_line) = @_;
	my(@opt_array, $opt, $ignore_flag, $def, $prev_opt);

	# Split up matrix entries
	@opt_array = split (/ /, $opt_line);
	# Find entry to set config to
	$opt = $opt_array [$curnt_idx] = $opt_array [$cfg_idx];
	# Rejoin up matrix entries
	$opt_line = join (" ", @opt_array);

	# Check if IGNORE would be needed for stripped options file
	$ignore_flag = (($opt =~ m/^[a-z]$/) ? 1 : 0);

	if (!$opt__force) {
		# Check if previous configuration was changed
		$prev_opt = uc($opt_array [$prev_idx]);
		&print_debug (1, "\np=$prev, pd=$prev_def, po=$prev_opt, pi=$prev_idx, pc=$prev_cfg\n");
		if ($prev_was_vocal){ $prev_opt =~ tr/VC/YN/; }
		else				{ $prev_opt =~ tr/CV/YN/; }
		$prev =~ s/\s+$//;
		$prev_def = ($prev_opt eq "Y") ? "#define" :
					($prev_opt eq "N") ? "#undef" :
					($prev_opt eq "K") ? "\/\/keep" : "#error";
		if ($prev ne $prev_def) {
			&print_debug (1, "\np=$prev, pd=$prev_def, po=$prev_opt, pi=$prev_idx, pc=$prev_cfg\n");
			die "Error: Symbol ${sym} does not match current configuration\n";
		}
	} else {
		# Check if previous configuration was changed
		$prev_opt = uc($opt_array [$prev_idx]);
		&print_debug (1, "\np=$prev, pd=$prev_def, po=$prev_opt, pi=$prev_idx, pc=$prev_cfg\n");
		if ($prev_was_vocal){ $prev_opt =~ tr/VC/YN/; }
		else				{ $prev_opt =~ tr/CV/YN/; }
		$prev =~ s/\s+$//;
		$prev_def = ($prev_opt eq "Y") ? "#define" :
					($prev_opt eq "N") ? "#undef" :
					($prev_opt eq "K") ? "\/\/keep" : "#error";
		if ($prev ne $prev_def) {
			&print_debug (1, "\np=$prev, pd=$prev_def, po=$prev_opt, pi=$prev_idx, pc=$prev_cfg\n");
			print "WARNING: Symbol ${sym} does not match current configuration\n";
		}
	}

	# Translate for comparison
	$opt = uc($opt);
	if ($opt__vocal)	{ $opt =~ tr/VC/YN/; }
	else				{ $opt =~ tr/CV/YN/; }

	$def = ($opt eq "Y") ? "#define " :
		   ($opt eq "N") ? "#undef  " :
		   ($opt eq "K") ? "//keep  " : "#error  ";

	if ($opt__strip) {
		if ($ignore_flag) {
			$fill .= " /* IGNORE */";	# Add IGNORE comment for stripper
		}
		else {
#			$fill =~ s/\s+$//;			# Strip off trailing whitespace
		}
		return sprintf ("%s%s%s", $def, $sym, $fill);
	}
	else {
		return sprintf ("%s%s%s/*|%s */", $def, $sym, $fill, $opt_line);
	}
}

## ######################################################################### ##
##
 #	Entry Routine: strip_options
 #
 #	This routine completes the option file stripping.
 #
 #	Parameters:
 #		Line info.
 #
 #	Returns:
 #		Translated line.
 #

sub strip_options
{
	my($optfile__contents) = @_;

	# Modify options file based on stored settings
	$optfile__contents =~ s/(#undef|#define|#error|\/\/keep)\s*\b(\w+)\b(.*?)\/\*\|(.*?)\*\//&strip_xlate ($1, $2, $3, $4)/ge;
#	$optfile__contents =~ s/(#undef|#define|#error|\/\/keep)\s*\b(\w+)\b(.*\n)/&strip_xlate ($1, $2, $3)/ge;

	$_ [0] = $optfile__contents; # return by reference
}


## ######################################################################### ##
##
 #	Entry Routine: strip
 #
 #	This routine strips C-pre processor #if/#else/#endif's based on options
 #	set by load_options or set_options.
 #
 #	Parameters:
 #		Source code to be modified.
 #
 #	Returns:
 #		Number of changes.
 #
 #	Notes:
 #		defined_states:
 #			u	=	undef
 #			d	=	define
 #			ui	=	ignore, undef
 #			di	=	ignore, define
 #			i	=	ignore, unknown
 #			ni	=	ignore, unknown from ifndef
 #			anything else is treated as "i"
 #
 #		flags:
 #			ii	=	ignore ignore's (ui => u, di => d) (does not affect i)
 #			uu	=	undef unknown's	(i => u) (does not affect ui or di)
 #

sub clear_options
{
#	our (%define_state);

	undef %define_state;
	undef %reconfig_state;
}

sub set_options
{
	my ($arg, $val);
#	our (%define_state);

	while (($arg, $val) = splice (@_, 0, 2)) {
		if ($val =~ m/^([ud]i?|n?i)$/) {
			# Only accept "u", "d", "ui", "di", or "i"
			$define_state {$arg} = $val;
		}
		else {
			$define_state {$arg} = "i";
			&print_debug (0, "Warning, set_options: unrecognized value\n");
		}
	}
}

sub get_option
{
	my ($arg) = (@_);
#	our (%define_state);

	if (defined ($define_state {$arg})) {
		return ($define_state {$arg});
	}
	else {
		return ("i");
	}
}

sub is_defined
{
	my ($arg) = (@_);

	if ($define_state{$arg} =~ m/d/) {
		return (1);
	}
	else {
		return (0);
	}
}

sub get_options
{
	my (@args) = (@_);
	my (@retval);
#	our (%define_state);

	@retval = map ($_ ||= "i", @define_state {@args});
	return (@retval);
}

sub load_options_file
{
	my ($optfile) = @_;
	my ($contents, $save_fs);
	local ($/);

	if (!open (OPTIONS, "${optfile}")) {
		return 0;
	}

	undef $/;
	$contents = <OPTIONS>;
	close (OPTIONS);

	&load_options ($contents);
}

sub load_options
{
	my ($def, $option, $comments, $line);
#	our (%define_state);

	foreach $line (split (/\n/, $_[0])) {
#		if ($line =~ m/^\s*\#\s*(define|undef)\s+(\w+)\b/)
		if ($line =~ m/^\#(define|undef)\s+([^_]\w+)\b(.*)$/)
		{
			$def = ($1 eq "define") ? 1 : 0;
			$option = $2;
			$comments = $3;
			if ($line =~ m/^\#define\s+_\w+_H\b/) {
				# ignore "#define _INCLUDE_OPTIONS_H" or similar
				$define_state {$option} = "i";
			}
			elsif ($def) {
				$define_state {$option} = "d";
			}
			else {
				$define_state {$option} = "u";
			}

			# Append "i" for ignore'd options
			# (if IGNORE on line or lowercase char in CURNT column)
			if ($comments =~ m/\bIGNORE\b|\/\*\|[A-Za-z] ([a-z]) /) {
				$define_state {$option} .= "i";
			}
		}
	}
}

sub load_reconfigs
{
	my ($def, $option, $current, $comments, $line);

	foreach $line (split (/\n/, $_[0])) {
		if ($line =~ m/(#undef|#define|#error|\/\/keep)\s*\b(\w+)\b(.*?)\/\*\|[a-zA-Z] ([a-zA-Z])/)
		{
			$def = ($1 eq "define") ? 1 : 0;
			$option = $2;
			$comments = $3;
			$current = $4;
			if ($current ne "K") {
				$reconfig_state{$option} = $current;
#				print ("rc state of $option is $current\n");
			}
		}
	}
}



sub load_options_file_ii
{
	my ($optfile) = @_;
	my ($contents, $save_fs);
	local ($/);

	if (!open (OPTIONS, "${optfile}")) {
		return 0;
	}

	undef $/;
	$contents = <OPTIONS>;
	close (OPTIONS);

	&load_options_ii ($contents);
}

sub load_options_ii
{
	my ($def, $option, $comments, $line);
#	our (%define_state);

	foreach $line (split (/\n/, $_[0])) {
#		if ($line =~ m/^\s*\#\s*(define|undef)\s+(\w+)\b/)
		if ($line =~ m/^\#(define|undef)\s+([^_]\w+)\b(.*)$/)
		{
			$def = ($1 eq "define") ? 1 : 0;
			$option = $2;
			$comments = $3;
			if ($line =~ m/^\#define\s+_\w+_H\b/) {
				# ignore "#define _INCLUDE_OPTIONS_H" or similar
				$define_state {$option} = "i";
			}
			elsif ($def) {
				$define_state {$option} = "d";
			}
			else {
				$define_state {$option} = "u";
			}

		}
	}
}

sub process_defined
{
	my ($line, @flags) = @_;
	my ($nh_flag, $ii_flag, $uu_flag, $retval);
	my (%stored_idx, @name, @test_val, @sections);
	my (@not, @same_as, $all_true, $all_false);
	my ($new_line, $orig_line, $prog, $num_unknowns, $parenthesis_cnt);
	my ($flag, $i, $j, $s, $option);
	my ($this_idx, $this_name, $this_test_val, $this_result);
#	our (%define_state);

	$ii_flag = 0;
	$uu_flag = 0;
	foreach $flag (@flags) {
		if ($flag eq "n#") { # used for ifdefs w/o #'s (for makefile's)
			$nh_flag = 1;
		}
		elsif ($flag eq "ii") {
			# ignore "IGNORE"s
			$ii_flag = 1;
		}
		elsif ($flag eq "uu") {
			# undef unknown's
			$uu_flag = 1;
		}
		else {
			&print_debug (1, "Warning in process_defined: unrecognized option: ${flag}\n");
		}
	}

	&print_debug (1, $line);

	$orig_line = $line;
	return $orig_line unless $line =~ s/^(\s*#\s*if\s+)//;
	$new_line = $1;
	$line =~ s/\/\*.*?\*\///g; # remove comments
	$line =~ s/\/\/.*//g; # remove comments
	return $orig_line if $line =~ m/\=\=|\!\=|\+|\-/;
	return $orig_line if $line =~ m/^\s*\D\w*\s*$/;

	@sections = split (/(defined\s*\(\s*\w+\s*\)|1|0|\(|\)|\&\&|\|\||\!)/, $line);
	$i = 0;
	$parenthesis_cnt = 0;
	$prog = "";
	$prev = "start";
	foreach $s (@sections) {
		&print_debug (1, "{$s}");
		if ($s =~ m/defined\s*\(\s*(\w+)\s*\)/) {
			$this_name = $1;
			$option = $define_state {$this_name} || "i";

			$option =~ s/^i$/u/ if $uu_flag;		# (i => u)
			$option =~ s/^([ud])i$/$1/ if $ii_flag; # (ui => u, di => d)

			if ($option eq "d") {
				$prog .= "1";
				$new_line .= " 1 ";
			}
			elsif ($option eq "u") {
				$prog .= "0";
				$new_line .= " 0 ";
			}
			else {
				if (defined ($stored_idx {$this_name})) {
					$this_idx = $stored_idx {$this_name};
				}
				else {
					$name [$i] = $this_name;
					$stored_idx {$this_name} = $i;
					$this_idx = $i;
					$i++;
				}
				$prog .= "(\$test_val [$this_idx])";
				$new_line .= $s;
			}
			$prev = "val";
		}
		elsif (($s eq "0") || ($s eq "1")) {
			return $orig_line if $prev eq "val";
			$prev = "val";

			$prog .= $s;
			$new_line .= $s;
		}
		elsif ($s eq "(") {
			return $orig_line if $prev eq ")";
			$prev = "(";
			$parenthesis_cnt++;

			$prog .= $s;
			$new_line .= $s;
		}
		elsif ($s eq ")") {
			return $orig_line if $prev eq "(";
			$prev = ")";
			$parenthesis_cnt--;

			$prog .= $s;
			$new_line .= $s;
		}
		elsif ($s =~ m/^\&\&$/) {
			return $orig_line if $prev =~ m/binary|unary|start/;
			$prev = "binary";

			$prog .= $s;
			$new_line .= $s;
		}
		elsif ($s =~ m/^\|\|$/) {
			return $orig_line if $prev =~ m/binary|unary|start/;
			$prev = "binary";

			$prog .= $s;
			$new_line .= $s;
		}
		elsif ($s =~ m/^\!$/) {
			return $orig_line if $prev eq "val";
			$prev = "unary";

			$prog .= $s;
			$new_line .= $s;
		}
		else {
			if ($s =~ m/\S/) {
				&print_debug (1, "\nreturning origline because of [${s}]");
				return $orig_line;
			}
			$new_line .= $s;
		}
	}
	$num_unknowns = $i;

	if (($parenthesis_cnt != 0) ||
		(($prev ne "val") && ($prev ne ")"))
	   )
	{
		&print_debug (1, "\nreturning origline because of BBB");
		return $orig_line;
	}

	&print_debug (1, "\n$prog\n");

	for ($i = 0; $i < $num_unknowns; $i++) {
		$same_as [$i] = 1;
		$not [$i] = 1;
	}

	$all_true = 1;
	$all_false = 1;

	for ($j = 0; $j < (1 << $num_unknowns); $j++) {
		for ($i = 0; $i < $num_unknowns; $i++) {
			$this_test_val = (($j & (1 << $i)) != 0) ? 1 : 0;
			$test_val [$i] = $this_test_val;
			&print_debug (1, "\n$j:$i:$this_test_val\n");
		}
		$this_result = eval ($prog) ? 1 : 0;
		&print_debug (1, "\n\t$j:$this_result\n");
#		print @test_val;


		if ($this_result) {
			$all_false = 0;
		}
		else {
			$all_true = 0;
		}

		for ($i = 0; $i < $num_unknowns; $i++) {
			if ($test_val [$i] == $this_result) {
				$not [$i] = 0;
			}
			else {
				$same_as [$i] = 0;
			}

		}
	}

	if ($all_false) {
		&print_debug (1, "(undef'd)\n");
		return 0;
	}

	if ($all_true) {
		&print_debug (1, "(define'd)\n");
		return 1;
	}

	for ($i = 0; $i < $num_unknowns; $i++) {
		if ($same_as [$i]) {
			$retval = sprintf ("#ifdef %s", $name [$i]);
			&print_debug (1, "$retval\n");
			return $retval;
		}
		elsif ($not [$i]) {
			$retval = sprintf ("#ifndef %s", $name [$i]);
			&print_debug (1, "$retval\n");
			return $retval;
		}
	}

	$new_line =~ s/\s+$//;;
	&print_debug (1, "$new_line\n");
	while (1) {
		next if ($new_line =~ s/\s*\|\|(\s*0\s*\|\|)+\s*/ \|\| /g);	# "|| 0 ||" => "||"
		next if ($new_line =~ s/^(\s*\#if\s+)0\s*\|\|\s*/${1} /);	# "(at start) 0 ||" => ""
		next if ($new_line =~ s/\s*\|\|\s*0\s*$//);					# "|| 0 (at end)" => ""
		next if ($new_line =~ s/\s*\&\&(\s*1\s*\&\&)+\s*/ \&\& /g);	# "&& 1 &&" => "&&"
		next if ($new_line =~ s/^(\s*\#if\s+)1\s*\&\&\s*/${1} /);	# "(at start) 1 &&" => ""
		next if ($new_line =~ s/\s*\&\&\s*1\s*$//);					# "&& 1 (at end)" => ""
		last;
	}
	continue {
		&print_debug (2, "$new_line\n");
	}

	&print_debug (1, "[$new_line]\n");
	return $new_line;
}

sub strip
{
	my (@flags) = @_ [1..$#_];
	my (@lines, @write_stack);
	my ($new_contents, $write_state, $prev_state, $option, $line, $temp, $i, $flag);
	my ($regexp1, $regexp1a, $regexp1b, $regexp1c, $regexp2, $regexp3);
	my ($modified, $save_line) = 0;
	my ($nh_flag, $uu_flag, $ii_flag) = (0, 0, 0);
#	our (%define_state);

	# Process arguments
	foreach $flag (@flags) {
		if ($flag eq "n#") { # used for ifdefs w/o #'s (for makefile's)
			$nh_flag = 1;
		}
		elsif ($flag eq "ii") {
			# ignore "IGNORE"s
			$ii_flag = 1;
		}
		elsif ($flag eq "uu") {
			# undef unknown's
			$uu_flag = 1;
		}
		else {
			&print_debug (0, "Warning in strip: unrecognized option: ${flag}\n");
		}
	}

	$temp = $nh_flag ? qr"^" : qr"^\s*\#\s*";

	if ($nh_flag) {
		$regexp1 =	qr"${temp}(ifdef|ifndef|if|ifeq|ifneq)\s";
#		$regexp1 =	qr"^(ifdef|ifndef|if)\s";
	}
	else {
		$regexp1 =	qr"${temp}(ifdef|ifndef|if)\s";
	}
	$regexp1a =	qr"${temp}ifdef\s+(\w+)\b";
	$regexp1b =	qr"${temp}ifndef\s+(\w+)\b";
	$regexp1c =	qr"${temp}if\s+(.+)$";
	$regexp2 =	qr"${temp}else\b";
	$regexp3 =	qr"${temp}endif\b";

	@lines = split (/\n/, $_[0]);
	$new_contents = "";
	$write_state = "d";
	push (@write_stack, $write_state);
	foreach $line (@lines) {
		$save_line = $line;
		if ($line =~ m/${regexp1}/) {
			$temp = $1;
			if ($temp eq "ifeq") {
				$line =~ m/${regexp1a}/;
				$option = "i";
				&print_debug (1, "(1a,$option)");
			}
			if ($temp eq "ifdef") {
				$line =~ m/${regexp1a}/;
				$option = $define_state {$1} || "i";
				&print_debug (1, "(1a,$option)");
			}
			elsif ($temp eq "ifndef") {
				$line =~ m/${regexp1b}/;
				$option = $define_state {$1} || "ni";
				$option =~ tr/ud/du/;	# (u => d, d => u, ui => di, di => ui)
				&print_debug (1, "(1b,$option)");
			}
			elsif ($temp eq "if") {
				$line =~ m/${regexp1c}/;
				$temp = &process_defined ($line, @flags);
				if ($temp =~ m/#/) {
					$option = "xi";
					$line = $temp;
				}
				elsif ($temp == 0) {
					$option = "u";
				}
				elsif ($temp == 1) {
					$option = "d";
				}
				&print_debug (1, "(1c,$option,$temp)");
			}
			else {
				# should not be able to get here
			}
			push (@write_stack, $write_state);

			$option =~ s/^i$/u/ if $uu_flag;		# (i => u)
			$option =~ s/^ni$/d/ if $uu_flag;		# (ni => d)
			$option =~ s/^([ud])i$/\1/ if $ii_flag; # (ui => u, di => d)

			&print_debug (1,"(1d,$option,$ii_flag)");

			if (($write_state ne "u") || ($option eq "u")) {
				$write_state = $option;
				$write_state =~ s/^([xnud])i$/i/; # (xi => i, ni => i, ui => i, di => i)
			}
			if ($option =~ m/i/) { # option is "i", "ni", "ui", or "di"
				$prev_state = pop (@write_stack);
				if ($prev_state ne "u") {
					$new_contents .= "$line\n";
				}
				push (@write_stack, $prev_state);
			}
			else {
				$modified++;
			}
			if ($line ne $save_line) {
				$modified++;
			}
		}
		elsif ($line =~ m/${regexp2}/) {
			&print_debug (1, "(2,$write_state)");
			if ($write_state eq "i") {
				$new_contents .= "$line\n";
			}
			else {
				$prev_state = pop (@write_stack);
				if (($write_state eq "u") && ($prev_state ne "u")) {
					$write_state = "d";
				}
				elsif ($write_state eq "d") {
					$write_state = "u";
				}
				push (@write_stack, $prev_state);
			}
		}
		elsif ($line =~ m/${regexp3}/) {
			&print_debug (1, "(3,$write_state)");
			if ($write_state eq "i") {
				$new_contents .= "$line\n";
			}
			if ($#write_stack > 0) {
				$write_state = pop (@write_stack);

			}
			else {
				print "\nendif without ifdef in $main::arg\n";
				return 0;
			}
		}
		else {
			if ($write_state ne "u") {
				$new_contents .= "$line\n";
				&print_debug (1, "+");
			}
			else {
				&print_debug (1, "-");
			}
		}
	}
	if ($#write_stack != 0) {
		print "\nExit with unmatched ifdef in $main::arg\n";
		return 0;
	}
	if ($modified > 0) {
		$_[0] = $new_contents;
	}
	return $modified;
}

## ######################################################################### ##
##
 #	Entry Routine: reformat
 #
 #	This routine enforces certain formating rules.
 #
 #	Parameters:
 #		Source code to be modified.
 #
 #	Returns:
 #		Number of changes.
 #

sub reformat
{
	my ($section, $modified);
	my (@sections);

	# Replace lines containing "/*", 50 asterisks, and "*/"
	# with the VOCAL standard comment line.
	$_[0] =~ s!^([ \t]*/\*[ \t]*\*{50,}[ \t]*\*/[ \t]*)$!&reformat_vocal_comment_line ($1,$modified)!gme;

	# Correct improperly capitalized "VOCAL"s
	$modified += ($_[0] =~ s/Vo[cC]al/VOCAL/g);
	# Should use "Routine:" insteade of "Function:"
	$modified += ($_[0] =~ s/Function:/Routine:/g);

	# Put spaces in front of ('s and ['s
#	@sections = split (/(\n|\".*?\"|\'.*?\')/, $_[0]);
	@sections = split (/(\n|\".*?\"|\'.*?\'|\/\*[\s\S]*?\*\/)/, $_[0]);
	$_[0] = "";
	foreach $section (@sections) {
		if ($section =~ m/DM|#|DEF_DATA|DEF_FAR_DATA/) {
		}
		elsif ($section =~ m!^(\"|\'|/\*|\n)!) {
		}
		elsif ($section =~ s/([^\(\)\[\*\!\t ])([\(\[])/$1 $2/g) { #]])
			$modified++;
		}
		$_[0] .= $section;
	}
	if ($_[0] !~ m/\n$/) {
		$modified++;
		$_[0] .= "\n";
	}
	return $modified;
}

sub reformat_vocal_comment_line
{
	my ($prev_comment_line) = @_;
	my ($leading_ws, $ws_length, $length, $new_comment_line);

	$prev_comment_line =~ m!^([ \t]*)/\*!;
	$leading_ws = $1;
	$leading_ws =~ s/(^|(?<=\t)) {4}/\t/g;			# tabify
	$leading_ws =~ s/(^|(?<=\t)) {1,3}(?=\t)//g;	# tabify
	$ws_length = ($leading_ws =~ tr/\t/\t/) * 4 + ($leading_ws =~ tr/ / /) * 1;
	&print_debug (1, "[${ws_length}]");
	$new_comment_line = $leading_ws . "/* ". "*" x (73 - $ws_length) . " */";

	if ($new_comment_line ne $prev_comment_line) {
		&print_debug (1, "+");
		$_[1]++; # modified++
	}
	return ($new_comment_line);
}

## ######################################################################### ##
##
 #	Entry Routine: rmcommnt
 #
 #	This routine removes private comments.
 #
 #	Parameters:
 #		Source code to be modified.
 #
 #	Returns:
 #		Number of changes.
 #

sub rmcommnt
{
	my ($modified) = 0;

	# Remove "//" private comments: (unless -*/ after it on same line)
	$modified += ($_[0] =~ s!^[ \t\*]*//([^\*\n]|\*[^/\n])*\n!!gm);
	$modified += ($_[0] =~ s!//([^\*\n]|\*[^/\n])*\n!\n!g);

	# Remove single line "/*- -*/" private comments:
	# Deletes lines which become whitespace only
#	$modified += ($_[0] =~ s!^[ \t]*/\*\-[^\n]*?\*/[ \t]*\n!!gm);
	$modified += ($_[0] =~ s!^[ \t]*/\*\-[^\n]*?\*/\n!!gm);
	$modified += ($_[0] =~ s!^[ \t]*\*[ \t]*/\*\-[\s\S]*?\*[ \t]*/\n!!gm); ##???
	$modified += ($_[0] =~ s!/\*\-([^\*\n]|\*[^/\n])*\*/!!g);

	# Remove all "/*- -*/" private comments:
	$modified += ($_[0] =~ s!/\*-[\s\S]*?\*/!\n!g);
	# Remove all "//" private comments:
	$modified += ($_[0] =~ s!^[ \t]*//.*?\n!!gm);
	$modified += ($_[0] =~ s!//.*?\n!\n!g);

	# Remove all L#: labels:
	# "L###:" with only whitespace - delete entire line
	$modified += ($_[0] =~ s!\nL[0-9]{1,3}[a-zA-Z]?:[ \t]*\n!\n!g);
	# delete "L#:"
	$modified += ($_[0] =~ s!\nL[0-9]:!\n!g);
	# replace "L###:" with tab
	$modified += ($_[0] =~ s!\nL[0-9]{1,3}[a-zA-Z]?:!\n\t!g);

	return $modified;
}

## ######################################################################### ##
##
 #	Entry Routine: chgprint
 #
 #	This routine removes print_debug's and printf's.
 #
 #	Parameters:
 #		Source code to be modified.
 #
 #	Returns:
 #		Number of changes.
 #

sub chgprint
{
	# Remove print_debug_on, print_debug_off, printf lines:
#	return ($_[0] =~ s!^(([ \t]*[^#\n][ \t]*.*?\b)?(print_debug_off|print_debug_on|printf)\b[\s\S]+?;.*?\n)!#ifdef DO_REMOVE\n$1#endif /* DO_REMOVE */\n!gm);
	return ($_[0] =~ s!^(([ \t]*[^#\n][ \t]*.*?\b)?(print_debug_off|print_debug_on|printf)\b[\s\S]+?;.*?\n)!!gm);
}

## ######################################################################### ##
##
 #	Entry Routine: rmblank
 #
 #	This routine reformats whitespace.
 #
 #	Parameters:
 #		Source code to be modified.
 #
 #	Returns:
 #		Number of changes.
 #

sub rmblank
{
	my ($modified) = 0;

	# Remove end of line whitespace:
	$modified += ($_[0] =~ s/[ \t]+\n/\n/g);
	# Remove multiple blank lines:
	$modified += ($_[0] =~ s/\n\n\n+/\n\n/g);
	# Remove extra blank lines at start of file:
	$modified += ($_[0] =~ s/^\n\n+/\n/g);
	# Remove extra blank lines at end of file:
	$modified += ($_[0] =~ s/\n\n+$/\n/g);

	return $modified;
}

## ######################################################################### ##
