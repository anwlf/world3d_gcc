<?
    header('Content-type: image/png');
    $ret;
    //echo system("./world3d",$ret);
    $im = imagecreatefrompng(system("./world3d base1.txt",$ret));
    imagepng($im);
    imagedestroy($im);
?>