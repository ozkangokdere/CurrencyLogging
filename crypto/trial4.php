<?php
require '../vendor/autoload.php';

$ticker = $api->prices();
$keys = array_keys($ticker);

$start = 57;

while(true) {
    $flag = true;
    $prev = -1;
    $count = 0;
    foreach($keys as $key) {
        if(strpos($key, "BTC") == false) {
            continue;
        }

        if ($count >= $start) {
            if ($flag) {
                $ticks = $api->candlesticks($key, "1m");
                end($ticks);
                $tick =  prev($ticks);
                $now = intval($tick["openTime"]);
                if ($now != $prev) {
                    if($prev != -1)
                        $flag = false;
                }
            $prev = $now;
            echo $key."\t".$tick["open"]."\t".$tick["volume"]."\t".$tick["openTime"].PHP_EOL;
        }
            
        }
        $count = $count + 1;
    }

    
}


?>
