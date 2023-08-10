package vocalmdm;

use vocal;

1; # package must return 1

sub import
{
	my $pkg = shift;
	my $callpkg = caller;
#	print STDERR "\n---$pkg---$callpkg---\n\n";
	# export these routines:
    foreach $sym ("mdm_build_depend",
				  "mdm_build_depend_reset",
				  "copy_include_files")
	{
		*{"$callpkg\::$sym"} = \&{"$pkg\::$sym"};
    }
}

## ######################################################################### ##
 #       mdm_build_depend
## ######################################################################### ##

sub mdm_build_depend_reset
{
	undef %global__mbd__depend_history;
	undef %global__mbd__recall_flag;
	undef %global__mbd__recall_list;
	undef %global__mbd__depend_retval_history;
}

sub mdm_build_depend
{
	# First argument is path to root directory of MDM code
	# Second argument is file path from root directory of MDM code
	my ($dir, $file) = @_;

	recursive_mdm_build_depend ($dir, $file, 0);
}

sub copy_include_files
{
	# First argument is path to root directory of MDM code
	# Second argument is file path from root directory of MDM code
	my ($sdir, $ddir, $file, @flags) = @_;

	recursive_mdm_build_depend ($sdir, $file, 0, "copyto:$ddir", @flags);
}

sub recursive_mdm_build_depend
{
	my ($sourcepath, $thisfile, $level, @flags) = @_;
	my ($file, $retval, $contents, $copyflag, $destpath, $stripflag, $temp);
	my (@include_file_list);
	my ($save_fs) = $/;
	undef $/;

	$copyflag = 0;
	$stripflag = 0;
	foreach $flag (@flags) {
		if ($flag =~ m/copyto:(.*)$/) {
			# ignore IGNORE's
			$copyflag = 1;
			$destpath = $1;

		}
		elsif ($flag eq "strip") {
			$stripflag = 1;
		}
		else {
			&print_debug (0, "Warning, recursive_mdm_build_depend: unrecognized option: $flag\n");
		}
	}

	$stripflag = 1;
	if ($level == 0) {
		undef %global__mbd__depend_history;
		&print_debug (0, "PROCESSING $thisfile\n");
	}
	else {
		&print_debug (1, "\tIncluding " . ("  " x $level) . "../${thisfile}");
	}

	if ($global__mbd__recall_flag {$thisfile}) {
		&print_debug (1, " (Recalling)");
		@include_file_list = split (/,/, $global__mbd__recall_list {$thisfile});

#		print "---- [{$thisfile} -> ${global__mbd__recall_list {$thisfile}} ]\n";

	}
	else {
#		print "---- [XXX{$thisfile} ]\n";

		&print_debug (1, " (Reading File)");
		if (open (MBD_FILE, "${sourcepath}/${thisfile}")) {
			$contents = <MBD_FILE>;
			close (MBD_FILE);

			@dirs = split (/[\/\\]/, $thisfile);
			$dest_filedir = "";
			while ($dir = shift (@dirs)) {
				last if @dirs == 0;
				$dest_filedir .= "/${dir}";
				if ($copyflag) {
					if (!-d "${destpath}/${dest_filedir}") {
						&print_debug (0, "md ${destpath}/${dest_filedir}\n");
						mkdir ("${destpath}/${dest_filedir}", 0);
					}
				}
			}

			if ($stripflag) {
#	$contents =~ s!\/\*- MKHEADER Begin -\*\/[^\n]*!\/\* MKHEADER Begin \*\/\n!sgo;
#	$contents =~ s!\/\*- MKHEADER End -\*\/!\/\* MKHEADER End \*\/\n!sgo;
#	$contents =~ s!\/\*- AUTOGEN Begin -\*\/[^\n]*!\/\* AUTOGEN Begin \*\/\n!sgo;
#	$contents =~ s!\/\*- AUTOGEN End -\*\/!\/\* AUTOGEN End \*\/\n!sgo;
	$contents =~ s!\/\*- (AUTOGEN|MKHEADER|MAKEMC) Begin -\*\/[^\n]*!\/\* $1 Begin \*\/\n!sgo;
	$contents =~ s!\/\*- (AUTOGEN|MKHEADER|MAKEMC) End -\*\/!\/\* $1 End \*\/\n!sgo;
				&strip ($contents);
				&rmcommnt ($contents);
				&rmblank ($contents);
#	$contents =~ s!\/\* MKHEADER Begin \*\/\n!\/\*- MKHEADER Begin -\*\/\n!sgo;
#	$contents =~ s!\/\* MKHEADER End \*\/!\/\*- MKHEADER End -\*\/\n!sgo;
#	$contents =~ s!\/\* AUTOGEN Begin \*\/\n!\/\*- AUTOGEN Begin -\*\/\n!sgo;
#	$contents =~ s!\/\* AUTOGEN End \*\/!\/\*- AUTOGEN End -\*\/\n!sgo;
	$contents =~ s!\/\* ((AUTOGEN|MKHEADER|MAKEMC)) Begin \*\/\n!\/\*- $1 Begin -\*\/\n!sgo;
	$contents =~ s!\/\* ((AUTOGEN|MKHEADER|MAKEMC)) End \*\/!\/\*- $1 End -\*\/\n!sgo;
			}

			if ($copyflag) {
				if (open (MBD_FILE, ">${destpath}/${thisfile}")) {
					print MBD_FILE $contents;
					close (MBD_FILE);
				}
				else {
					&print_debug (0, "Warning: Could not create file ${destpath}/${thisfile} (Skipping)\n");
				}
			}

			@include_file_list = ($contents =~ m!\n\#include\s*\"(.+?[/\\].+?)\"!g);

			$global__mbd__recall_flag {$thisfile} = 1;
			$global__mbd__recall_list {$thisfile} = "";
			foreach $file (@include_file_list) {
				&print_debug (1, " {$file} \n");
				$file =~ s|\\|/|;
				$global__mbd__recall_list {$thisfile} .= "${file},";
			}
		}
		else {
			&print_debug (0, "Warning: Cannot open ${sourcepath}/${thisfile} (Skipping)\n");
		}
	}
	&print_debug (1, "\n");

	$retval = "";
	foreach $file (@include_file_list) {
		next if $file eq "";
			$sub_retval = "";

		if (!-f "${sourcepath}/${file}") {
			&print_debug (0, "Warning: ${sourcepath}/${file} does not exist (Skipping)\n");
			next;
		}
		if (defined ($global__mbd__depend_history {$file}) &&
			($global__mbd__depend_history {$file} == 1)) {
			&print_debug (1, "\tFile already included: $file\n");
		}
		else {
			# here we need to deal with data/*/*.h

			if ("${sourcepath}/${file}" =~ m/\.\/data\/[a-zA-Z0-9_]+\/[a-zA-Z0-9_]+\.h/ ) {
				$global__mbd__depend_history {$file} = 1;
#				$retval .= &recursive_mdm_build_depend ($sourcepath, $file, $level + 1, @flags);
			} else
			{
				if($global__mbd__depend_retval_history {$file}) {
					$global__mbd__depend_history {$file} = 1;
					$retval .= " \\\n\t\t\t\t" . "   " x $level . "../$file";

					$retval .= 	$global__mbd__depend_retval_history {$file};
#					print "attached list for $file\n";
					next;
				}

				$global__mbd__depend_history {$file} = 1;
				$retval .= " \\\n\t\t\t\t" . "   " x $level . "../$file";
	#			$retval .= "\t\t\t\t\t  " . "  " x $level . "\$(DIRLVL)\\${file} \\\n";

#				$retval .= &recursive_mdm_build_depend ($sourcepath, $file, $level + 1, @flags);


				$sub_retval .= &recursive_mdm_build_depend ($sourcepath, $file, $level + 1, @flags);
				$global__mbd__depend_retval_history {$file} = $sub_retval;
				$retval .= $sub_retval;


			}
		}
	}

	@retlist = split ("\n", $retval);

	$count = 0;
	foreach $val (@retlist) {
		$count++;
		for $i ($count ... $#retlist) {

#				print "A:A $val\n";
#				print "A:B $retlist[$i]\n";

			if ($val eq $retlist[$i]) {
				$retlist[$i] = "\n";
#				print "found a DUP - $val\n";
			}

		}

	}

	$retval = join "\n", @retlist;
	$retval =~ s/\n\s*\n/\n/g;

	$/ = $save_fs;
	return ($retval);
}
