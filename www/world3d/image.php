<?
    header('Content-type: image/png\n\n');
    //echo system("./world3d",$ret);
    $command = "./world3d";
    if (isset($_REQUEST['base'])) {
	$command .=" ".$_REQUEST['base'];
	if (isset($_REQUEST['key'])) {
	    $command .=" ".$_REQUEST['key'];
	}
    }
    if ($command == "./world3d") $command .= " -1";
    //$im = imagecreatefrompng(system("./world3d $base $key",$ret));
    //$im = imagecreatefrompng(passthru("./world3d ".escapeshellarg($base).' '.escapeshellarg($key),$ret));
    //$command = "./world3d 1 11";
    //return;
    //$im = imagecreatefrompng(system($command,$ret));
    //$im = imagecreatefrompng($command);
    //imagepng($im);
    //imagedestroy($im);
    passthru($command);
?>