<?php

function test_connect($addr)
{
  $start = microtime(true);

  $con = mysql_connect($addr,"root","mysqllungta99");
  if (!$con)
    die('Could not connect: ' . mysql_error());

  $time = microtime(true) - $start;
  echo "Connection time to $addr: $time seconds\n";

  mysql_close($con);
}


test_connect("localhost");
test_connect("127.0.0.1");
test_connect("::1");
?>
